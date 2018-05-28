import scrapy
from scrapy import signals
from scrapy.xlib.pydispatch import dispatcher

import mysql.connector

import datetime

import time

import os

mode = 1

class DATABASE :

	connection = None
	cursor = None

	def Connect(self, host, database, user, password) :
		self.connection = mysql.connector.connect(host = host, database = database, user = user, password = password)
		self.cursor = self.connection.cursor(buffered=True)

	def Execute(self, query) :
		try :
			print("query :: " + query)
			self.cursor.execute(query)
			self.connection.commit()
			for (last,) in self.cursor :
				print("lasttttt = " + str(last))
				return last
		except Exception as e :
			print(e)
			input()

	def Get_query_insert(self, table, columns, values) :
		separator1 = ", "
		separator2 = "', '"
		for i in range(len(values)) :
			values[i] = values[i].replace("'", "''").replace("\\", "\\\\")
		return "INSERT INTO " + table + " (" + separator1.join(columns) + ") VALUES ('" + separator2.join(values) + "') ON DUPLICATE KEY UPDATE ID = VALUES(ID);"

	def Insert(self, table, columns, values) :
		query = self.Get_query_insert(table, columns, values)
		try :
			self.Execute(query)
		except Exception as e :
			print("QUERY=" + query)
			print(e)
			input()

class InsidersSpider(scrapy.Spider) :

	name = "quotes"

	custom_settings = {
		'DOWNLOAD_DELAY' : 0.2,
		'RANDOMIZE_DOWNLOAD_DELAY' : False
	}

	database = DATABASE()
	table = "live1"
	listname = "live1.csv"
	dict_cik_ticker = {}

	# Informations communes à toutes les transactions
	columns0 = [
	"ID",
	"cik",
	"filing_date",
	"accepted",
	"period_of_report",
	"owner_cik",
	"url",
	"date_extract",
	"issuerCik",
	"issuerName",
	"issuerTradingSymbol",
	"name1",
	"name2",
	"rptOwnerName",
	"isDirector",
	"isTenPercentOwner",
	"isOfficer",
	"isOther",
	"officerTitle",
	"rptOwnerStreet1",
	"rptOwnerCity",
	"rptOwnerState",
	"rptOwnerZipCode",
	"derivative",
	"ticker2"
	]

	# Informations pour une non derivative transaction
	columns1 = [
	"securityTitle",
	"transactionDate",
	"transactionCode",
	"transactionAcquiredDisposedCode",
	"transactionShares",
	"transactionPricePerShare",
	"sharesOwnedFollowingTransaction",
	"directOrIndirectOwnership",
	"natureOfOwnership"
	]

	# Informations pour une derivative transaction
	columns2 = [
	"securityTitle",
	"conversionOrExercisePrice",
	"transactionDate",
	"deemedExecutionDate",
	"transactionCode",
	"transactionShares",
	"exerciseDate",
	"expirationDate",
	"underlyingSecurityTitle",
	"underlyingSecurityShares",
	"transactionPricePerShare",
	"sharesOwnedFollowingTransaction",
	"directOrIndirectOwnership",
	"natureOfOwnership"
	]

	i = 0
	nb_lines_read = 0

	nb_requests = 0

	# Boucle sur la liste de tickers
	def start_requests(self):	

		dispatcher.connect(self.spider_closed, signals.spider_closed)

		self.database.Connect("167.114.239.198", "fbonnin", "fbonnin", "q3p@ssFB!!")

		self.load_dict()

		print("\n\n\nHI\n\n\n")
		file = open(self.listname, "r")
		text = file.read()
		lines = text.split('\n')
		for line in lines:
			infos = line.split(";")
			url = "https://www.sec.gov/Archives/edgar/data/" + infos[1]
			print("URL ===== " + url)
			yield scrapy.Request(url=url, callback=self.parse, meta = {"ticker" : infos[0], "cik" : infos[1], "name1" : infos[2], "name2" : infos[3]})
			self.nb_lines_read += 1
			print("\n\n\n\n\nnb_lines_read = " + str(self.nb_lines_read))
			file = open("progress.txt", "w")
			file.write(str(self.nb_lines_read))
		print("--- %s seconds ---" % (time.time() - start_time))

	# Prépare un dictionnaire qui associe à chaque cik le ticker correspondant
	def load_dict(self) :
		file = open(self.listname, "r")
		text = file.read()
		lines = text.split('\n')
		for line in lines :
			infos = line.split(";")
			self.dict_cik_ticker[infos[1]] = infos[0]

	# Analyse une page comme : https://www.sec.gov/Archives/edgar/data/51143
	def parse(self, response) :
		print("PARSE : " + response.request.url)
		self.nb_requests += 1
		print("nb_requests = " + str(self.nb_requests))
		doc_ids = response.xpath("descendant::td/a/text()")
		if mode == 1 :
			# Récupère l'id et la date du dernier document téléchargé pendant l'update précédente
			last = self.Get_last(response.meta["cik"])
			last_date = self.Get_last_date(response.meta["cik"])
		DATES = response.xpath("descendant::td/a/text()/../../following-sibling::td[position()=2]/text()")
		for i in range(len(doc_ids)) :
			doc_id = doc_ids[i]
			n = str(doc_id.extract())
			DATE = DATES[i].extract()
			if mode == 1 :
				if DATE < "2018-04" :
					break
				if n == last :
					break
				if DATE < last_date :
					break
			if i == 0 :
				self.Save_last(response.meta["cik"], n, DATE)
			next_url = response.request.url + "/" + n
			yield response.follow(next_url, self.parse_1, meta = {"ticker" : response.meta["ticker"], "cik" : response.meta["cik"], "name1" : response.meta["name1"], "name2" : response.meta["name2"]})

	def Save_last(self, cik, last, date) :
		query = "INSERT INTO last (cik, last, date) VALUES ('" + cik + "', '" + last + "', '" + date + "') ON DUPLICATE KEY UPDATE last = VALUES(last), date = VALUES(date);"
		self.database.Execute(query)

	def Get_last(self, cik) :
		query = "SELECT last FROM last WHERE cik = '" + cik + "';"
		last = str(self.database.Execute(query))
		return last

	def Get_last_date(self, cik) :
		query = "SELECT date FROM last WHERE cik = '" + cik + "';"
		last_date = str(self.database.Execute(query))
		return last_date

	# Analyse une page comme : https://www.sec.gov/Archives/edgar/data/51143/000156218018002434
	def parse_1(self, response) :
		print("PARSE_1 : " + response.request.url)
		self.nb_requests += 1
		print("nb_requests = " + str(self.nb_requests))
		for a in response.xpath("descendant::a") :
			text = str(a.xpath("text()").extract_first())
			next_url = str(a.xpath("@href").extract_first())
			if text[-11:] == "-index.html" :
				yield response.follow(next_url, self.parse_2, meta = {"ticker" : response.meta["ticker"], "cik" : response.meta["cik"], "name1" : response.meta["name1"], "name2" : response.meta["name2"], "url" : response.request.url})

	# Analyse une page comme : https://www.sec.gov/Archives/edgar/data/51143/000156218018002434/0001562180-18-002434-index.html
	def parse_2(self, response) :

		print("PARSE_2 : " + response.request.url)
		self.nb_requests += 1
		print("nb_requests = " + str(self.nb_requests))

		# Récupère Filing Date, Accepted, Period of Report
		for div in response.xpath("descendant::div") :
			text1 = div.xpath("text()").extract_first()
			text2 = div.xpath("following-sibling::div[position()=1]/text()").extract_first()
			if text1 == "Filing Date" :
				filing_date = text2
			elif text1 == "Accepted" :
				accepted = text2
			elif text1 == "Period of Report" :
				period_of_report = text2

		# Récupère owner_cik
		for a in response.xpath("descendant::a") :
			text = a.xpath("text()").extract_first()
			if text == "Reporting" :
				a2 = a.xpath("following-sibling::a")
				info = a2.xpath("text()").extract_first()
				owner_cik = info.split(" ")[0]

		# Cherche les documents xml de type 4
		for td in response.xpath("descendant::td") :
			text = td.xpath("text()").extract_first()
			if text == "4" :
				a  = td.xpath("preceding-sibling::td[position()=1]/a")
				text = str(a.xpath("text()").extract_first())
				if text[-4:] == ".xml" :
					next_url = a.xpath("@href").extract_first()
					yield response.follow(next_url, self.parse_3, meta = {"ticker" : response.meta["ticker"], "cik" : response.meta["cik"], "name1" : response.meta["name1"], "name2" : response.meta["name2"], "url" : response.meta["url"], "filing_date" : filing_date, "accepted" : accepted, "period_of_report" : period_of_report, "owner_cik" : owner_cik})

	# Analyse un fichier xml comme : https://www.sec.gov/Archives/edgar/data/51143/000156218018002434/primarydocument.xml
	def parse_3(self, response) :

		self.nb_requests += 1
		print("nb_requests = " + str(self.nb_requests))

		print("PARSE_3 : " + response.request.url)
		data0 = {} 
		data0["cik"] = response.meta["cik"]
		parts = response.request.url.split("/")
		data0["filing_date"] = response.meta["filing_date"]
		data0["accepted"] = response.meta["accepted"]
		data0["period_of_report"] = response.meta["period_of_report"]
		data0["owner_cik"] = response.meta["owner_cik"]
		data0["url"] = response.meta["url"]
		data0["date_extract"] = str(datetime.datetime.now())
		e_issuer = response.xpath("issuer")
		data0["issuerCik"] = e_issuer.xpath("issuerCik/text()").extract_first()
		data0["issuerName"] = e_issuer.xpath("issuerName/text()").extract_first()
		#data0["issuerTradingSymbol"] = e_issuer.xpath("issuerTradingSymbol/text()").extract_first()
		#plutot
		data0["issuerTradingSymbol"] = response.meta["ticker"]
		data0["name1"] = response.meta["name1"]
		data0["name2"] = response.meta["name2"]
		e_reportingOwner = response.xpath("reportingOwner")
		e_reportingOwnerId = e_reportingOwner.xpath("reportingOwnerId")
		data0["rptOwnerName"] = e_reportingOwnerId.xpath("rptOwnerName/text()").extract_first()
		e_reportingOwnerRelationship = e_reportingOwner.xpath("reportingOwnerRelationship")
		data0["isDirector"] = e_reportingOwnerRelationship.xpath("isDirector/text()").extract_first()
		data0["isTenPercentOwner"] = e_reportingOwnerRelationship.xpath("isTenPercentOwner/text()").extract_first()
		data0["isOfficer"] = e_reportingOwnerRelationship.xpath("isOfficer/text()").extract_first()
		data0["isOther"] = e_reportingOwnerRelationship.xpath("isOther/text()").extract_first()
		data0["officerTitle"] = e_reportingOwnerRelationship.xpath("officerTitle/text()").extract_first()
		e_reportingOwnerAddress = e_reportingOwner.xpath("reportingOwnerAddress")
		data0["rptOwnerStreet1"] = e_reportingOwnerAddress.xpath("rptOwnerStreet1/text()").extract_first()
		data0["rptOwnerCity"] = e_reportingOwnerAddress.xpath("rptOwnerCity/text()").extract_first()
		state = e_reportingOwnerAddress.xpath("rptOwnerState/text()").extract_first()
		data0["rptOwnerState"] = e_reportingOwnerAddress.xpath("rptOwnerState/text()").extract_first()
		data0["rptOwnerZipCode"] = e_reportingOwnerAddress.xpath("rptOwnerZipCode/text()").extract_first()
		data0["ticker2"] = self.dict_cik_ticker[data0["issuerCik"]]

		file_path = "files/"
		directory = os.path.dirname(file_path)
		if not os.path.exists(directory):
			os.makedirs(directory)
		file_path = "files/" + data0["issuerCik"] + "/"
		directory = os.path.dirname(file_path)
		if not os.path.exists(directory):
			os.makedirs(directory)
		parts = response.url.split("/")
		file = open("files/" + data0["issuerCik"] + "/" + parts[len(parts) - 2] + ".xml", "wb")
		file.write(response.body)

		i_transaction = 0

		e_nonDerivativeTable = response.xpath("nonDerivativeTable")
		el_nonDerivativeTransaction = e_nonDerivativeTable.xpath("nonDerivativeTransaction")
		for e_nonDerivativeTransaction in el_nonDerivativeTransaction :

			data1 = {}
			data2 = {}

			data0["ID"] = parts[len(parts) - 3] + "-" + parts[len(parts) - 2] + "-" + str(i_transaction)
			i_transaction += 1

			data0["derivative"] = "0"
			data1["securityTitle"] = e_nonDerivativeTransaction.xpath("securityTitle/value/text()").extract_first()
			data1["transactionDate"] = e_nonDerivativeTransaction.xpath("transactionDate/value/text()").extract_first()
			e_transactionCoding = e_nonDerivativeTransaction.xpath("transactionCoding")
			data1["transactionCode"] = e_transactionCoding.xpath("transactionCode/text()").extract_first()
			e_transaction_amounts = e_nonDerivativeTransaction.xpath("transactionAmounts")
			data1["transactionAcquiredDisposedCode"] = e_transaction_amounts.xpath("transactionAcquiredDisposedCode/value/text()").extract_first()
			data1["transactionShares"] = e_transaction_amounts.xpath("transactionShares/value/text()").extract_first()
			data1["transactionPricePerShare"] = e_transaction_amounts.xpath("transactionPricePerShare/value/text()").extract_first()
			data1["sharesOwnedFollowingTransaction"] = e_nonDerivativeTransaction.xpath("postTransactionAmounts/sharesOwnedFollowingTransaction/value/text()").extract_first()
			e_ownershipNature = e_nonDerivativeTransaction.xpath("ownershipNature")
			data1["directOrIndirectOwnership"] = e_ownershipNature.xpath("directOrIndirectOwnership/value/text()").extract_first()
			data1["natureOfOwnership"] = e_ownershipNature.xpath("natureOfOwnership/value/text()").extract_first()
			print()
			self.Print_data(data0, data1, data2)
			self.Insert_non_derivative(data0, data1)
			print()


		el_derivativeTransaction = response.xpath("derivativeTable/derivativeTransaction")
		for e_derivativeTransaction in el_derivativeTransaction :

			data1 = {}
			data2 = {}

			data0["ID"] = parts[len(parts) - 3] + "-" + parts[len(parts) - 2] + "-" + str(i_transaction)
			i_transaction += 1

			data0["derivative"] = "1"
			data2["securityTitle"] = e_derivativeTransaction.xpath("securityTitle/value/text()").extract_first()
			data2["conversionOrExercisePrice"] = e_derivativeTransaction.xpath("conversionOrExercisePrice/value/text()").extract_first()
			data2["transactionDate"] = e_derivativeTransaction.xpath("transactionDate/value/text()").extract_first()
			data2["deemedExecutionDate"] = e_derivativeTransaction.xpath("deemedExecutionDate/value/text()").extract_first()
			data2["transactionCode"] = e_derivativeTransaction.xpath("transactionCoding/transactionCode/text()").extract_first()
			e_transactionAmounts = e_derivativeTransaction.xpath("transactionAmounts")
			data2["transactionShares"] = e_transactionAmounts.xpath("transactionShares/value/text()").extract_first()
			data2["transactionPricePerShare"] = e_transactionAmounts.xpath("transactionPricePerShare/value/text()").extract_first()
			data2["transactionAcquiredDisposedCode"] = e_transactionAmounts.xpath("transactionAcquiredDisposedCode/value/text()").extract_first()
			data2["exerciseDate"] = e_derivativeTransaction.xpath("exerciseDate/value/text()").extract_first()
			data2["expirationDate"] = e_derivativeTransaction.xpath("expirationDate/value/text()").extract_first()
			e_underlyingSecurity = e_derivativeTransaction.xpath("underlyingSecurity")
			data2["underlyingSecurityTitle"] = e_underlyingSecurity.xpath("underlyingSecurityTitle/value/text()").extract_first()
			data2["underlyingSecurityShares"] = e_underlyingSecurity.xpath("underlyingSecurityShares/value/text()").extract_first()
			#PRICE TODO
			data2["sharesOwnedFollowingTransaction"] = e_derivativeTransaction.xpath("postTransactionAmounts/sharesOwnedFollowingTransaction/value/text()").extract_first()
			e_ownershipNature = e_derivativeTransaction.xpath("ownershipNature")
			print(e_ownershipNature.extract())
			data2["directOrIndirectOwnership"] = e_ownershipNature.xpath("directOrIndirectOwnership/value/text()").extract_first()
			print("LA!" + e_ownershipNature.xpath("directOrIndirectOwnership/value/text()").extract_first())
			data2["natureOfOwnership"] = e_ownershipNature.xpath("natureOfOwnership/value/text()").extract_first()
			print()
			self.Print_data(data0, data1, data2)
			self.Insert_derivative(data0, data2)
			print()

		self.i += 1
		print("i = " + str(self.i))

	def Print_data(self, data0, data1, data2) :

		for column in self.columns0 :
			print(self.Get_value(data0, column))

		for column in self.columns1 :
			print(self.Get_value(data1, column))

		for column in self.columns2 :
			print(self.Get_value(data2, column))

	def Insert_non_derivative(self, data0, data1) :

		values = []
		for column in self.columns0 :
			values.append(data0[column])
		for column in self.columns1 :
			values.append(data1[column])
		for i in range(len(values)) :
			if values[i] == None :
				values[i] = ""
		self.database.Insert(self.table, self.columns0 + self.columns1, values)

	def Insert_derivative(self, data0, data2) :

		values = []
		for column in self.columns0 :
			values.append(data0[column])
		for column in self.columns2 :
			values.append(data2[column])
		for i in range(len(values)) :
			if values[i] == None :
				values[i] = ""
		self.database.Insert(self.table, self.columns0 + self.columns2, values)

	def Get_value(self, dictionary, key) :

		if key in dictionary :
			return dictionary[key]
		return "null"

	def spider_closed(self, spider, reason) :
		#query = "INSERT INTO " + self.table_all + " SELECT * FROM " + self.table + ";"
		#self.database.Execute(query)
		#query = "INSERT INTO tmp SELECT " + self.table + ".*, liste1.cik FROM " + self.table + " LEFT JOIN liste1 ON "+ self.table + ".issuerTradingSymbol = liste1.ticker;"
		#self.database.Execute(query)
		print()
