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

        private string Get_query_insert(string table, List<string> columns, List<string> values)
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
        protected abstract void Exec_query_insert(string query);
        public void Insert(string table, List<string> columns, List<string> values)
        {
            Exec_query_insert(Get_query_insert(table, columns, values));
        }

        private string Get_query_clear(string table)
        {
            return "DELETE FROM " + table;
        }
        protected abstract void Exec_query_clear(string query);
        public void Clear(string table)
        {
            Exec_query_clear(Get_query_clear(table));
        }
    }
}
