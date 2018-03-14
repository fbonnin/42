using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_HISTO_1 : OP_HISTORICAL
    {
        public OP_HISTO_1(SOURCE source, DATABASE database, string table, HISTO_RQ_INFO[] histo_rq_infos) : base(source, database, table, histo_rq_infos)
        {
        }
        protected override string Get_query(FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            string result = "";
            foreach (Dictionary<string, object> values in request_result)
            {
                if (values.ContainsKey("security"))
                    values["security"] = Get_short_ticker((string)values["security"]);
                if (values.ContainsKey("CHG_PCT_1D"))
                    values["CHG_PCT_1D"] = Get_chg((string)values["CHG_PCT_1D"]);
                string query = "INSERT INTO " + table + " (ID, ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += fields[i].column;
                    if (i < fields.Length - 1)
                        query += ", ";
                }
                query += ") VALUES (" + "'" + DATABASE.Value_to_string(values["security"]) + DATABASE.Value_to_string(values["date"]) + "'" + ", ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += "'" + DATABASE.Value_to_string(values[fields[i].name]) + "'";
                    if (i < fields.Length - 1)
                        query += ", ";
                }
                query += ") ON DUPLICATE KEY UPDATE ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += fields[i].column + " = " + "'" + DATABASE.Value_to_string(values[fields[i].name]) + "'";
                    if (i < fields.Length - 1)
                        query += ", ";
                }
                query += ";";
                result += query;
            }
            return result;
        }
        private string Get_chg(string value)
        {
            System.Globalization.NumberFormatInfo nfi = new System.Globalization.NumberFormatInfo
            {
                NumberDecimalSeparator = "."
            };
            value = value.Replace(',', '.');
            double nb = double.Parse(value, nfi);
            nb /= 100;
            return nb.ToString(nfi);
        }
    }
}
