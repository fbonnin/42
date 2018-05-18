import mysql.connector

class DATABASE :

	connection = None
	cursor = None

	def Connect(self, host, database, user, password) :
		self.connection = mysql.connector.connect(host = host, database = database, user = user, password = password)
		self.cursor = self.connection.cursor(buffered=True)

database = DATABASE()
database.Connect("167.114.239.198", "fbonnin", "fbonnin", "q3p@ssFB!!")

file = open("merge.csv", "w")

for i in range(1, 7) :
	query = "SELECT * FROM live" + str(i) + "_tmp;"
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
