import scrapy

first_page = 0 # exclu
last_page = 1

class BusinessWireSpider(scrapy.Spider) :

	name = "BusinessWire"

	custom_settings = {
		'DOWNLOAD_DELAY' : 1,
		'RANDOMIZE_DOWNLOAD_DELAY' : False
	}

	def start_requests(self) :

		url_part1 = "https://www.businesswire.com/portal/site/home/template.BINARYPORTLET/search/resource.process/?javax.portlet.tpst=92055fbcbec7e639f1f554100d908a0c&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_searchTerm=-rhyhhrstrse&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_resultsPage="
		url_part2 = "&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_searchType=news&javax.portlet.rid_92055fbcbec7e639f1f554100d908a0c=searchPaging&javax.portlet.rcl_92055fbcbec7e639f1f554100d908a0c=cacheLevelPage&javax.portlet.begCacheTok=com.vignette.cachetoken&javax.portlet.endCacheTok=com.vignette.cachetoken"
		i = first_page + 1
		while i <= last_page :
			yield scrapy.Request(url = url_part1 + str(i) + url_part2, callback = self.parse_page)
			i += 1

	def parse_page(self, response) :

		#print(response.text)

		titles = response.xpath("descendant::h2")
		print("len(titles) = " + str(len(titles)))
		for i in range(len(titles)) :
			text = titles[i].xpath("a/text()").extract_first()
			print(text)
			if text == "News" :
				articles = titles[i].xpath("following-sibling::ul[position()=1]/li/h3/a/@href")
				print("len(articles) = " + str(len(articles)))
				#for j in range(len(articles)) :
				for j in range(1) :
					yield response.follow(articles[j], self.parse_article)

	def parse_article(self, response) :

		print(response.text)
