from selenium import webdriver
from selenium.webdriver.common.keys import Keys

import mysql.connector

import datetime
import time
from dateutil import parser

first_page = 0
last_page = 792

database_server = "167.114.239.198"
database_name = "fbonnin"
user = "fbonnin"
password = "q3p@ssFB!!"
table = "zHealthcare"

server = 0

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
			values[i] = values[i].replace("'", "''").replace("\\", "\\\\")
		return "INSERT INTO " + table + " (" + separator1.join(columns) + ") VALUES ('" + separator2.join(values) + "');"

	def Insert(self, table, columns, values) :
		query = self.Get_query_insert(table, columns, values)
		try :
			self.Execute(query)
		except Exception as e :
			print("QUERY=" + query)
			print(e)
			input()


driver = webdriver.Firefox()

"""driver.get("http://www.python.org")
input()
assert "Python" in driver.title
elem = driver.find_element_by_name("q")
elem.clear()
elem.send_keys("pycon")
print("ICI")
elem.send_keys(Keys.RETURN)
assert "No results found." not in driver.page_source"""

database = DATABASE()
database.Connect(database_server, database_name, user, password)

url = "https://seekingalpha.com/market-news/healthcare?page="
page = first_page + 1

missing_pages = []

while page <= last_page :

	driver.get(url + str(page))

	try :
		mcs = driver.find_elements_by_xpath("descendant::li[@class=\"mc\"]")
		print("len(mcs) = " + str(len(mcs)))
	except :
		missing_pages.append(page)
		time.sleep(60 * 2)
		page = page + 1
		continue

	mybool = True

	for i in range(len(mcs)) :

		try :

			print("i = " + str(i))

			print("t")
			date_titles = mcs[i].find_elements_by_xpath("preceding-sibling::li[@class=\"date-title\"]")
			print("u")
			print("len(date_titles) = " + str(len(date_titles)))

			print("m")
			day = date_titles[len(date_titles) - 1].text
			print("n")
			if day[0:5] == "Today" :
				print("o")
				day = day[8:len(day)]
			print("p")
			print("day = " + day)

			try :
				print("q")
				ticker = mcs[i].find_element_by_xpath("div[@class=\"media-left\"]/a").text
			except :
				print("r")
				ticker = ""
			print("s")
			print("ticker = " + ticker)

			print("a")
			body = mcs[i].find_element_by_xpath("div[@class=\"media-body\"]")

			print("b")
			title_a = body.find_element_by_xpath("div[@class=\"title\"]/a")

			print("c")
			title_text = title_a.text
			print("d")
			print("title_text = " + title_text)

			print("e")
			title_href = title_a.get_attribute("href")
			print("f")
			print("title_href = " + title_href)

			print("g")
			contents = body.find_element_by_xpath("div[@class=\"bullets\"]").text
			print("h")
			print("contents = " + contents)

			print("i")
			hour = body.find_element_by_xpath("div[@class=\"mc-share-info\"]/span[@class=\"item-date\"]").text
			print("j")
			print("hour = " + hour)

			print("k")
			date = str(parser.parse(day + " " + hour))
			print("l")
			print("date = " + date)

			print("v")
			columns = ["date", "ticker", "title", "url", "contents", "server", "date_extract"]
			print("w")
			values = [date, ticker, title_text, title_href, contents, str(server), str(datetime.datetime.now())]
			print("x")
			database.Insert(table, columns, values)

		except :

			print("STALE :: " + str(i))
			mybool = False
			#input()
			break

	try :
		print("y")
		if mybool :
			driver.find_element_by_xpath("descendant::li[@class=\"next\"]")
		else :
			continue
	except :
		print("z")
		break

	page += 1

print("MISSING PAGES")
for missing_page in missing_pages :
	print(missing_page)
input()
driver.close()
