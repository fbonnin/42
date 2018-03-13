using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_HISTO_1 : OP_HISTORICAL
    {
        public OP_HISTO_1(SOURCE source, DATABASE database, string table, RQ_HISTO_INFO[] rq_histo_infos) : base(source, database, table, rq_histo_infos)
        {
        }
        protected override string Get_query(FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            string result = "";
            foreach (Dictionary<string, object> values in request_result)
            {
                if (values.ContainsKey("CHG_PCT_1D"))
                    values["CHG_PCT_1D"] = Get_chg(values["CHG_PCT_1D"].ToString());
                string query = "INSERT INTO " + table + " (ID, ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += fields[i].column;
                    if (i < fields.Length - 1)
                        query += ", ";
                }
                query += ") VALUES (" + "'" + values["security"].ToString() + values["date"].ToString() + "'" + ", ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += "'" + values[fields[i].name].ToString() + "'";
                    if (i < fields.Length - 1)
                        query += ", ";
                }
                query += ") ON DUPLICATE KEY UPDATE ";
                for (int i = 0; i < fields.Length; i++)
                {
                    query += fields[i].column + " = " + "'" + values[fields[i].name].ToString() + "'";
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
            double nb = double.Parse(value, System.Globalization.CultureInfo.InvariantCulture);
            nb /= 100;
            return nb.ToString(System.Globalization.CultureInfo.InvariantCulture);
        }
    }
}
