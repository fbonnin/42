using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_HISTO1 : OP_REQUEST
    {
        public OP_HISTO1(string type, SOURCE source, DATABASE database, string table, RQ_INFO[] rq_infos, bool update) : base(type, source, database, table, rq_infos, update)
        {
        }
        protected override string[] Add_mandatory_fields(string[] fields)
        {
            List<string> result = fields.ToList();
            if (!result.Contains("security"))
                result.Add("security");
            if (!result.Contains("date"))
                result.Add("date");
            return result.ToArray();
        }
        protected override object[][] Process_request_result(ref FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            FIELD[] old_fields = fields;
            fields = new FIELD[old_fields.Length + 1];
            fields[0] = new FIELD();
            fields[0].name = "ID";
            fields[0].column = "ID";
            for (int j = 0; j < old_fields.Length; j++)
                fields[j + 1] = old_fields[j];
            object[][] result = new object[request_result.Length][];
            for (int i = 0; i < request_result.Length; i++)
            {
                Dictionary<string, object> values = request_result[i];
                if (values.ContainsKey("security"))
                    values["security"] = Get_short_ticker((string)values["security"]);
                if (values.ContainsKey("CHG_PCT_1D"))
                    values["CHG_PCT_1D"] = Get_chg((string)values["CHG_PCT_1D"]);
                values.Add("ID", DATABASE.Value_to_string(values["security"]) + DATABASE.Value_to_string(values["date"]));
                result[i] = new object[fields.Length];
                for (int j = 0; j < fields.Length; j++)
                    result[i][j] = DATABASE.Value_to_string(values[fields[j].name]);
            }
            return result;
        }
        private string Get_chg(string value)
        {
            if (value == "null")
                return "null";
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
