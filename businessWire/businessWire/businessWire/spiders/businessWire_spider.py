import scrapy
import pytz
import datetime
from dateutil import parser
from businessWire import items
import businessWire.config

first_page = businessWire.config.FIRST_PAGE
last_page = businessWire.config.LAST_PAGE

database_server = "localhost"
database_name = "database_test"
user = "root"
password = ""
table = "articles"

server = 0

class BusinessWireSpider(scrapy.Spider) :

    name = "BusinessWire"

    custom_settings = {
        'DOWNLOAD_DELAY' : 0.1,
        'RANDOMIZE_DOWNLOAD_DELAY' : True
    }

    def start_requests(self) :

        url_part1 = "https://www.businesswire.com/portal/site/home/template.BINARYPORTLET/search/resource.process/?javax.portlet.tpst=92055fbcbec7e639f1f554100d908a0c&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_searchTerm=-rhyhhrstrse&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_resultsPage="
        url_part2 = "&javax.portlet.rst_92055fbcbec7e639f1f554100d908a0c_searchType=news&javax.portlet.rid_92055fbcbec7e639f1f554100d908a0c=searchPaging&javax.portlet.rcl_92055fbcbec7e639f1f554100d908a0c=cacheLevelPage&javax.portlet.begCacheTok=com.vignette.cachetoken&javax.portlet.endCacheTok=com.vignette.cachetoken"
        i = first_page + 1
        while i <= last_page :
            yield scrapy.Request(url = url_part1 + str(i) + url_part2, callback = self.parse_page)
            i += 1
            print(i)

    def parse_page(self, response) :


        titles = response.xpath("descendant::h2")
        for i in range(len(titles)) :
            text = titles[i].xpath("a/text()").extract_first()
            if text == "News" :
                articles = titles[i].xpath("following-sibling::ul[position()=1]/li/h3/a/@href")
                for j in range(len(articles)) :
                    yield response.follow(articles[j], self.parse_article)

    def parse_article(self, response) :

        article = items.BusinesswireItem()

        titles = response.xpath("descendant::h1/descendant::text()")
        title = ""
        for i in range(len(titles)):
            title += titles[i].extract()
        article['title'] = title.replace("'","`")


        date_extract = str(datetime.datetime.now(pytz.timezone('US/Eastern')))[:-5]
        article['xdate'] = date_extract

        date_article = response.xpath("descendant::time/text()").extract_first()
        date_article = str(parser.parse(date_article[:-22]))
        article['pdate'] = date_article


        contents = str(response.xpath("descendant::div[@itemprop=\"articleBody\"]").extract_first())
        article['content'] = contents.replace("'","`")



        hashtags = response.xpath("descendant::a[@class=\"hash-tag\"]/text()")
        strings = []

        for i in range(len(hashtags)) :
            strings.append(hashtags[i].extract()[1:])
        hashtag_string = ", ".join(strings)
        article['hashtag'] = hashtag_string


        cashtags = response.xpath("descendant::a[@class=\"cash-tag\"]/text()")
        strings = []

        for i in range(len(cashtags)) :
            strings.append(cashtags[i].extract()[1:])
        cashtag_string = ", ".join(strings)
        article['cashtag'] = cashtag_string


        contacts = response.xpath("descendant::div[@class=\"bw-release-contact\"]")[0].xpath("p/descendant::text()")
        contacts_string = ""

        for i in range(len(contacts)) :
            contacts_string += contacts[i].extract().replace("'","`")
        article['contact'] = contacts_string

        url = response.url
        article['url'] = url

        ID = url[39:53]
        article['ID'] = ID

        article['company'] = "NULL"
        article['ticker'] = "NULL"

        yield article




