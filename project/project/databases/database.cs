using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Globalization;

namespace project
{
    abstract class DATABASE
    {
        public abstract void Execute0(string query);
        public abstract object Execute1(string query);

        private string Value_to_string(object value)
        {
            NumberFormatInfo nfi = new NumberFormatInfo
            {
                NumberDecimalSeparator = "."
            };
            string result;
            if (value.GetType() == typeof(float) || value.GetType() == typeof(double))
                result = ((double)value).ToString(nfi);
            else if (value.GetType() == typeof(DateTime))
                result = Date_to_string((DateTime)value);
            else
                result = value.ToString();
            return result;
        }
        private string Date_to_string(DateTime date)
        {
            string result = date.Year.ToString();
            if (date.Month < 10)
                result += "0";
            result += date.Month.ToString();
            if (date.Day < 10)
                result += "0";
            result += date.Day.ToString();
            return result;
        }

        public string Get_query_insert(string table, string[] columns, object[] values)
        {
            string result = "INSERT INTO " + table + "(";
            for (int i = 0; i < columns.Length; i++)
            {
                result += columns[i];
                if (i < columns.Length - 1)
                    result += ", ";
            }
            result += ") VALUES (";
            for (int i = 0; i < values.Length; i++)
            {
                result += "'" + Value_to_string(values[i]) + "'";
                if (i < values.Length - 1)
                    result += ", ";
            }
            result += ");";
            return result;
        }
        public string Get_query_insert(string table, string[] columns, object[][] rows)
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
                object[] values = rows[i];
                result += "(";
                for (int j = 0; j < values.Length; j++)
                {
                    result += "'" + Value_to_string(values[j]) + "'";
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
        public string Get_query_clear(string table)
        {
            return "DELETE FROM " + table + ";";
        }

        public void Insert(string table, string[] columns, object[] values)
        {
            Execute0(Get_query_insert(table, columns, values));
        }
        public void Insert(string table, string[] columns, object[][] rows)
        {
            Execute0(Get_query_insert(table, columns, rows));
        }
        public void Clear(string table)
        {
            Execute0(Get_query_clear(table));
        }
    }
}
