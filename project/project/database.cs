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
        public void Insert(string table, string[] columns, Object[] values)
        {
            Execute(Get_query_insert(table, columns, values));
        }

        private string Get_query_clear(string table)
        {
            return "DELETE FROM " + table + ";";
        }
        public void Clear(string table)
        {
            Execute(Get_query_clear(table));
        }

        protected abstract void Execute(string query);
    }
}
