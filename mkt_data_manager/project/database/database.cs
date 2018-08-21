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
        public abstract void Execute0(string[] queries);
        public abstract object Execute1(string query);

        static public string Value_to_string(object value)
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
                result = value.ToString().Replace(',', '.');
            return result;
        }
        static string Date_to_string(DateTime date)
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
        public string[] Get_queries_insert(string table, string[] columns, object[][] rows)
        {
            string[] result = new string[rows.Length];
            for (int i = 0; i < rows.Length; i++)
                result[i] = Get_query_insert(table, columns, rows[i]);
            return result;
        }
        public string Get_query_insert_update(string table, string[] columns, object[][] rows)
        {
            string[] s_rows = new string[rows.Length];
            for (int i = 0; i < rows.Length; i++)
            {
                string[] s_values = new string[rows[i].Length];
                for (int j = 0; j < rows[i].Length; j++)
                    s_values[j] = "'" + Value_to_string(rows[i][j]) + "'";
                s_rows[i] = "(" + string.Join(", ", s_values, 0, s_values.Length) + ")";
            }
            string[] s_updates = new string[columns.Length];
            for (int i = 0; i < columns.Length; i++)
                s_updates[i] = columns[i] + " = VALUES (" + columns[i] + ")";
            return "INSERT INTO " + table + " (" + string.Join(", ", columns, 0, columns.Length) + ") VALUES " + string.Join(", ", s_rows, 0, s_rows.Length) +
            " ON DUPLICATE KEY UPDATE " + string.Join(", ", s_updates);
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
        /*
        Cette fonction tente d'insérer toutes les données en une seule requête.
        Si elle échoue (si la requête est trop longue), elle partage les données en deux groupes et fait deux requêtes.
        Si elle échoue elle fait 4 groupes, etc...
        */
        public void Insert_update_split(string table, string[] columns, object[][] rows)
        {
            int group_size = rows.Length;
            while (group_size >= 1)
            {
                Console.WriteLine("block size = " + group_size);
                try
                {
                    for (int i = 0; i < rows.Length; i += group_size)
                    {
                        int true_size = Math.Min(group_size, rows.Length - i);
                        object[][] group = new object[true_size][];
                        for (int j = 0; j < true_size; j++)
                            group[j] = rows[i + j];
                        string query = Get_query_insert_update(table, columns, group);
                        Console.WriteLine(query);
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
        public void Clear(string table)
        {
            Execute0(Get_query_clear(table));
        }
    }
}
