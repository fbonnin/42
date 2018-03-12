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
        public override void Execute(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
        private string Get_query_clear(string table)
        {
            return "DELETE FROM " + table + ";";
        }
        public override void Insert(string table, string[] columns, Object[] values)
        {
            Execute(Get_query_insert(table, columns, values));
        }
        public void Insert(string table, string[] columns, Object[][] rows)
        {
            Execute(Get_query_insert(table, columns, rows));
        }
        public override void Clear(string table)
        {
            Execute(Get_query_clear(table));
        }
    }
}
