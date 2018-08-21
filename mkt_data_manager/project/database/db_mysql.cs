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
            if (query == "")
                return;
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
        public override void Execute0(string[] queries)
        {
            int group_size = queries.Length;
            while (group_size >= 1)
            {
                try
                {
                    for (int i = 0; i < queries.Length; i += group_size)
                    {
                        string query = "";
                        for (int j = 0; j < group_size && i + j < queries.Length; j++)
                            query += queries[i + j] + ";";
                        Execute0(query);
                    }
                }
                catch (Exception)
                {
                    group_size /= 2;
                    continue;
                }
                break;
            }
        }
        public override object Execute1(string query)
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            return command.ExecuteScalar();
        }
    }
}
