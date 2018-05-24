import mysql.connector

import ftplib

import datetime

class DATABASE :

	connection = None
	cursor = None

	def Connect(self, host, database, user, password) :
		self.connection = mysql.connector.connect(host = host, database = database, user = user, password = password)
		self.cursor = self.connection.cursor(buffered=True)

database = DATABASE()
database.Connect("167.114.239.198", "fbonnin", "fbonnin", "q3p@ssFB!!")

today = datetime.datetime.now()

yesterday = today - datetime.timedelta(days=1)

filename = "Insiders/" + str(today) + ".csv"
print(filename)
print(str(yesterday))

file = open(filename, "w")

for i in range(1, 7) :
	query = "SELECT * FROM live" + str(i) + "_tmp WHERE accepted >= '" + str(yesterday) + "';"
	print(query)
	database.cursor.execute(query)
	database.connection.commit()
	for row in database.cursor :
		for i in range(len(row)) :
			value = str(row[i])
			print(value)
			if value == "None" :
				file.write("NULL")
			else :
				file.write("\"" + value + "\"")
			if i < len(row) - 1 :
				file.write(";")
		file.write("\n")

	query = "DELETE FROM live" + str(i) + "_tmp;"
	#database.cursor.execute(query)

file.close()

session = ftplib.FTP('ftp.q3-technology.com', 'qtechnol-vic0914', 'SMu45pRt8')

file = open(filename, 'rb')

session.storbinary('STOR ' + filename, file)

file.close()

session.quit()

print("merge, export, upload - DONE")
