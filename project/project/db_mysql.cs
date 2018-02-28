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

        public DB_MYSQL(string host, string name, string user, string password) : base(host, name, user, password)
        {
        }

        public override void Connect()
        {
            connection = new MySqlConnection("host=" + host + ";database=" + name + ";user=" + user + ";password=" + password + ";");
            connection.Open();
        }
        public override void Disconnect()
        {
            connection.Close();
        }

        protected override void Execute(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
    }
}
