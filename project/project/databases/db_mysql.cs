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
        public override void Execute0(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
        public override object Execute1(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            return command.ExecuteNonQuery();
        }
    }
}
