using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class DATABASE
    {
        string host;
        string name;
        string user;
        string password;


        public abstract void Connect();
        public abstract void Disconnect();

        private string Get_insert_query(string table, List<string> columns, List<string> values)
        {
            string result = "INSERT INTO " + table + " (";
            for (int i = 0; i < columns.Count; i++)
            {
                result += columns[i];
                if (i < columns.Count - 1)
                    result += ", ";
            }
            result += ") VALUES (";
            for (int i = 0; i < values.Count; i++)
            {
                result += values[i];
                if (i < values.Count - 1)
                    result += ", ";
            }
            result += ");";
            return result;
        }
        abstract protected string Exec_insert_query(string query);
        public void Insert(string table, List<string> columns, List<string> values)
        {
            Exec_insert_query(Get_insert_query(table, columns, values));
        }
    }
}
