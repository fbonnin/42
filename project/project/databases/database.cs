using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class DATABASE
    {
        /*private string Get_date(DateTime date)
            {
                string result = date.Year.ToString();
                if (date.Month < 10)
                    result += "0";
                result += date.Month.ToString();
                if (date.Day < 10)
                    result += "0";
                result += date.Day.ToString();
                return result;
            }*/
        public string Get_query_insert(string table, string[] columns, Object[] values)
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
        private string Get_query_insert(string table, string[] columns, Object[][] rows)
        {
            string result = "INSERT INTO " + table + " (";
            for (int i = 0; i < columns.Length; i++)
            {
                result += columns[i];
                if (i < columns.Length - 1)
                    result += ", ";
            }
            result += ") VALUES ";
            for (int i = 0; i < rows.Length; i++)
            {
                Object[] values = rows[i];
                result += "(";
                for (int j = 0; j < values.Length; j++)
                {
                    result += "'" + values[j].ToString() + "'";
                    if (j < values.Length - 1)
                        result += ", ";
                }
                result += ")";
                if (i < rows.Length - 1)
                    result += ", ";
            }
            result += ";";
            return result;
        }
        public abstract void Execute(string query);
        public abstract object Execute2(string query);
        public abstract void Insert(string table, string[] columns, Object[] values);
        public abstract void Clear(string table);
    }
}
