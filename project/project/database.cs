using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class DATABASE
    {
        protected string host;
        protected string name;
        protected string user;
        protected string password;

        public DATABASE(string host, string name, string user, string password)
        {
            this.host = host;
            this.name = name;
            this.user = user;
            this.password = password;
            Connect();
        }
        ~DATABASE()
        {
            Disconnect();
        }

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
        public void Insert(string table, List<string> columns, List<string> values)
        {
            Execute(Get_query_insert(table, columns, values));
        }

        private string Get_query_clear(string table)
        {
            return "DELETE FROM " + table;
        }
        public void Clear(string table)
        {
            Execute(Get_query_clear(table));
        }

        protected abstract void Execute(string query);
    }
}
