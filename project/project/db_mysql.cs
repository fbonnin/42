using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using MySql.Data;
using MySql.Data.MySqlClient;

namespace project
{
    class DB_MYSQL : DATABASE
    {
        MySqlConnection connection;

        public DB_MYSQL(string host, string name, string user, string password)
        {
            connection = new MySqlConnection("host=" + host + ";database=" + name + ";user=" + user + ";password=" + password + ";");
            connection.Open();
        }
        ~DB_MYSQL()
        {
            connection.Close();
        }
        private string Get_query_insert(string table, string[] columns, Object[] values)
        {
            string result = "INSERT INTO " + table + " (";
            for (int i = 0; i < columns.Length; i++)
            {
                result += columns[i];
                if (i < columns.Length - 1)
                    result += ", ";
            }
            result += ") VALUES (";
            for (int i = 0; i < values.Length; i++)
            {
                result += "'" + values[i].ToString() + "'";
                if (i < values.Length - 1)
                    result += ", ";
            }
            result += ");";
            return result;
        }
        private string Get_query_clear(string table)
        {
            return "DELETE FROM " + table + ";";
        }
        private void Execute(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
        public override void Insert(string table, string[] columns, Object[] values)
        {
            Execute(Get_query_insert(table, columns, values));
        }
        public override void Clear(string table)
        {
            Execute(Get_query_clear(table));
        }
    }
}
