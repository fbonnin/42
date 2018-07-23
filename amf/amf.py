import scrapy
from scrapy import signals
from scrapy.xlib.pydispatch import dispatcher
import PyPDF2

first_page = 4000
last_page = 4001

class AMFspider(scrapy.Spider) :

	name = "AMF spider"

	custom_settings = {
		'DOWNLOAD_DELAY' : 0.1,
		'RANDOMIZE_DOWNLOAD_DELAY' : True
	}

	nb_documents = 0
	missing_pages = []

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

		#print(response.body)

		print("PAGE = " + str(response.meta["page"]))

		filename = "amf/" + str(response.meta["ID"]) + ".pdf"

		"""f = open(filename, "wb")
		f.write(response.body)
		f.close()"""
		text = ""
		reader = PyPDF2.PdfFileReader(filename, "rb")
		for i in range(reader.getNumPages()) :
			text += reader.getPage(i).extractText()
		print(text)
		i_text = 0
		part = read_until(text, i_text, "NOM")
		i_text += len(part)
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until(text, i_text, "NOTIFICATION")
		i_text += len(part)
		dirigeant = part
		print("dirigeant = " + dirigeant)
		part = read_until(text, i_text, "COORDONNEES")
		i_text += len(part)
		type_notification = part
		print("type_notification = " + type_notification)
		part = read_until(text, i_text, "NOM")
		i_text += len(part)
		part = read_until(text, i_text, ":")
		i_text += len(part)
		i_text += 1
		part = read_until_2(text, i_text, "LEI", "DETAIL")
		i_text += len(part)
		emetteur = part
		print("emetteur = " + emetteur)

	def spider_closed(self, spider) :

		print("missing pages :")
		for i in range(len(self.missing_pages)) :
			print(self.missing_pages[i])

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
