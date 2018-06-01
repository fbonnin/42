import mysql.connector

import ftplib

import datetime

database_server = "167.114.239.198"
database_name = "fbonnin"
database_user = "fbonnin"
database_password = "q3p@ssFB!!"

# ftp server
ftp_host = 'ftp.q3-technology.com'
ftp_user = 'qtechnol-vic0914'
ftp_password = 'SMu45pRt8'

class DATABASE :

	connection = None
	cursor = None

	def Connect(self, host, database, user, password) :
		self.connection = mysql.connector.connect(host = host, database = database, user = user, password = password)
		self.cursor = self.connection.cursor(buffered=True)

database = DATABASE()
database.Connect(database_server, database_name, database_user, database_password)

#today = datetime.datetime.now()

#yesterday = today - datetime.timedelta(days=1)
#yesterday = yesterday.replace(hour=11, minute=0, second=0)

################################

france = datetime.datetime.now() + datetime.timedelta(hours = 2)
france_yesterday = france - datetime.timedelta(days = 1)
us = france - datetime.timedelta(hours = 6)
us_yesterday = us - datetime.timedelta(days = 1)
us_yesterday_14 = us_yesterday.replace(hour = 14, minute = 0, second = 0, microsecond = 0)

begin = us_yesterday_14

filename = "Insiders/" + str(france) + ".csv"
filename = filename.replace(':', '-')

file = open(filename, "w")

columns = ["accepted", "date_extract"]

for i in range(len(columns)) :
	file.write("\"")
	file.write(columns[i])
	file.write("\"")
	if i < len(columns) - 1 :
		file.write(";")
	file.write("\n")

for i in range(1, 7) :
	query = "SELECT " + ", ".join(columns) + " FROM live" + str(i) + "_tmp WHERE accepted >= '" + str(begin) + "';"
	database.cursor.execute(query)
	database.connection.commit()
	for row in database.cursor :
		for i in range(len(row)) :
			value = str(row[i])
			if value == "None" :
				file.write("NULL")
			else :
				file.write("\"" + value + "\"")
			if i < len(row) - 1 :
				file.write(";")
		file.write("\n")

file.close()

session = ftplib.FTP(ftp_host, ftp_user, ftp_password)

file = open(filename, 'rb')

session.storbinary('STOR ' + filename, file)

file.close()

session.quit()

print("merge, export, upload - DONE")
