import scrapy
from scrapy import signals
from scrapy.xlib.pydispatch import dispatcher
import os
import mysql.connector

first_page = 0
last_page = 10

database_server = "localhost"
database_name = "fbonnin"
user = "fbonnin"
password = "q3p@ssFB!!"
table = "amf"

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
			if values[i] == None :
				values[i] = "NULL"
			values[i] = values[i].replace("'", "''").replace("\\", "\\\\").replace("\n", "\\n")
		return "INSERT INTO " + table + " (" + separator1.join(columns) + ") VALUES ('" + separator2.join(values) + "');"

	def Insert(self, table, columns, values) :
		query = self.Get_query_insert(table, columns, values)
		try :
			self.Execute(query)
		except Exception as e :
			print("QUERY=" + query)
			print(e)
			input()

class AMFspider(scrapy.Spider) :

	name = "AMF spider"

	custom_settings = {
		'DOWNLOAD_DELAY' : 0.1,
		'RANDOMIZE_DOWNLOAD_DELAY' : True
	}

	nb_documents = 0
	missing_pages = []
	database = DATABASE()

	def __init__(self) :

		self.database.Connect(database_server, database_name, user, password)

	def start_requests(self) :

		dispatcher.connect(self.spider_closed, signals.spider_closed)
		url_part1 = "http://www.amf-france.org/Resultat-de-recherche-BDIF?PAGE_NUMBER="
		url_part2 = "&formId=BDIF&LANGUAGE=fr&BDIF_NOM_PERSONNE=&valid_form=Lancer+la+recherche&DATE_OBSOLESCENCE=&BDIF_TYPE_INFORMATION=BDIF_TYPE_INFORMATION_DECLARATION_DIRIGEANT&bdifJetonSociete=&subFormId=dd&DOC_TYPE=BDIF&BDIF_RAISON_SOCIALE=&isSearch=true&REFERENCE=&DATE_PUBLICATION="
		i = first_page + 1
		while i <= last_page :
			yield scrapy.Request(url = url_part1 + str(i) + url_part2, callback = self.parse_results, meta = {"page" : i})
			i += 1

	def parse_results(self, response) :

		#print(response.text)

		results = response.xpath("descendant::li[@class=\"resultat\"]/descendant::a/@href").extract()
		print("len(results) = " + str(len(results)))
		if len(results) == 0 :
			self.missing_pages.append(response.meta["page"])
		for i in range(len(results)) :
		#for i in range(1) :
			print()
			print("results[" + str(i) + "] = " + results[i])
			yield response.follow(results[i], self.parse_result, meta = {"page" : response.meta["page"], "i_result" : i})

	def parse_result(self, response) :

		#print(response.text)

		ID_text = response.xpath("descendant::span[@class=\"docBDIF\"]/text()").extract_first()
		ID = ID_text[16:28]
		result = response.xpath("descendant::p[@class=\"source\"]/descendant::a/@href").extract_first()
		self.nb_documents += 1
		yield response.follow(result, self.parse_pdf, meta = {"nb_documents" : self.nb_documents, "page" : response.meta["page"], "i_result" : response.meta["i_result"], "ID" : ID})

	def parse_pdf(self, response) :

		print("PAGE = " + str(response.meta["page"]))

		filename = "amf/" + str(response.meta["ID"])

		f = open(filename + ".pdf", "wb")
		f.write(response.body)
		f.close()
		os.system("pdftotext " + filename + ".pdf " + filename + ".txt")
		f = open(filename + ".txt", "r")
		text = f.read()
		f.close()
		parse1(response.url, text, self.database)

	def spider_closed(self, spider) :

		print("missing pages :")
		for i in range(len(self.missing_pages)) :
			print(self.missing_pages[i])

def parse1(url, text, database) :

	#print(text)
	i_text = 0
	n = Notification()
	n.lien = url
	part = read_until(text, i_text, "NOM")
	i_text += len(part)
	part = read_until(text, i_text, ":")
	i_text += len(part)
	i_text += 1
	part = read_until(text, i_text, "NOTIFICATION")
	i_text += len(part)
	n.dirigeant = part
	part = read_until(text, i_text, ":")
	i_text += len(part)
	i_text += 1
	part = read_until(text, i_text, "COORDONNEES")
	i_text += len(part)
	n.type_notification = part
	part = read_until(text, i_text, "NOM")
	i_text += len(part)
	part = read_until(text, i_text, ":")
	i_text += len(part)
	i_text += 1
	part = read_until_2(text, i_text, "LEI", "DETAIL")
	i_text += len(part)
	n.emetteur = part
	part = read_until(text, i_text, "DETAIL")
	i_text += len(part)
	while text[i_text : i_text + 6] == "DETAIL" :
		t = Transaction()
		part = read_until(text, i_text, "DATE")
		i_text += len(part)
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "LIEU")
		i_text += len(part)
		t.date = part
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "NATURE")
		i_text += len(part)
		t.lieu = part
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "DESCRIPTION")
		i_text += len(part)
		t.nature = part
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until_2(text, i_text, "CODE", "INFORMATION")
		i_text += len(part)
		t.instrument = part
		part = read_until(text, i_text, "AGREGEES")
		i_text += len(part)
		part = read_until(text, i_text, "PRIX")
		i_text += len(part)
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "VOLUME")
		i_text += len(part)
		t.prix = part
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "TRANSACTION")
		i_text += len(part)
		t.volume = part
		part = read_until(text, i_text, "LIE")
		i_text += len(part)
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until_2(text, i_text, "DETAIL", "DATE")
		i_text += len(part)
		t.lie = part
		n.transactions.append(t)

		print(t.date)
		print(t.lieu)
		print(t.nature)
		print(t.instrument)
		print(t.prix)
		print(t.volume)
		print(t.lie)

	part = read_until(text, i_text, ":")
	i_text += len(part)
	i_text += 1
	part = read_until(text, i_text, "COMMENTAIRE")
	i_text += len(part)
	n.date = part
	part = read_until(text, i_text, ":")
	i_text += len(part)
	i_text += 1
	part = read_until(text, i_text, "\"")
	i_text += len(part)
	n.commentaires = part

	print(n.lien)
	print(n.dirigeant)
	print(n.type_notification)
	print(n.emetteur)
	print(n.date)
	print(n.commentaires)

	columns = ["lien", "dirigeant", "type", "emetteur", "date_transaction", "lieu", "nature", "instrument", "prix", "volume", "lie", "date_notification", "commentaires"]
	for i in range(len(n.transactions)) :
		t = n.transactions[i]
		values = [n.lien, n.dirigeant, n.type_notification, n.emetteur, t.date, t.lieu, t.nature, t.instrument, t.prix, t.volume, t.lie, n.date, n.commentaires]
		database.Insert(table, columns, values)

class Transaction() :

	date = ""
	lieu = ""
	nature = ""
	instrument = ""
	prix = ""
	volume = ""
	lie = ""

class Notification() :

	lien = ""
	dirigeant = ""
	type_notification = ""
	emetteur = ""
	transactions = []
	date = ""
	commentaires = ""

	def __init__(self) : 
		self.transactions = []

def read_until(text, i_text, end) :

	result = ""
	while i_text < len(text) and text[i_text : i_text + len(end)] != end :
		result += text[i_text]
		i_text += 1
	return result

def read_until_2(text, i_text, end1, end2) :

	result = ""
	while i_text < len(text) and text[i_text : i_text + len(end1)] != end1 and text[i_text : i_text + len(end2)] != end2 :
		result += text[i_text]
		i_text += 1
	return result
