using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_REQUEST : OPERATION
    {
        string type;
        SOURCE source;
        DATABASE database;
        protected string table;
        RQ_INFO[] rq_infos;
        bool update;
        string column_security;

        public OP_REQUEST(string type, SOURCE source, DATABASE database, string table, RQ_INFO[] rq_infos, bool update)
        {
            this.type = type;
            this.source = source;
            this.database = database;
            this.table = table;
            this.rq_infos = rq_infos;
            this.update = update;
            foreach (RQ_INFO rq_info in rq_infos)
                foreach (FIELD field in rq_info.fields)
                    if (field.name == "security")
                        column_security = field.column;
        }
        public override void Do_operation()
        {
            if (update)
            {
                Remove_up_to_date_securities(rq_infos);
                Replace_start_by_min(rq_infos);
            }
            else
            	Delete();

            foreach (RQ_INFO rq_info in rq_infos)
            {
                string[] fields = Get_fields(rq_info.fields);
                fields = Add_mandatory_fields(fields);
                Dictionary<string, object>[] request_result = source.Request(type, rq_info.securities, fields, rq_info.request_params);
                object[][] rows = Process_request_result(ref rq_info.fields, request_result);
                database.Insert_update_split(table, Get_columns(rq_info.fields), rows);
                if (update)
                    Save_last_update(rq_info.securities);
            }
        }
        protected virtual string[] Add_mandatory_fields(string[] fields)
        {
            return fields;
        }
        protected virtual object[][] Process_request_result(ref FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            object[][] result = new object[request_result.Length][];
            for (int i = 0; i < request_result.Length; i++)
            {
                if (request_result[i].ContainsKey("security"))
                    request_result[i]["security"] = Get_short_ticker((string)request_result[i]["security"]);
                result[i] = new object[fields.Length];
                for (int j = 0; j < fields.Length; j++)
                    result[i][j] = request_result[i][fields[j].name];
            }
            return result;
        }
        protected string[] Get_fields(FIELD[] fields)
        {
            string[] result = new string[fields.Length];
            for (int i = 0; i < fields.Length; i++)
                result[i] = fields[i].name;
            return result;
        }
        protected string[] Get_columns(FIELD[] fields)
        {
            string[] result = new string[fields.Length];
            for (int i = 0; i < fields.Length; i++)
                result[i] = fields[i].column;
            return result;
        }
        protected string Get_short_ticker(string ticker)
        {
            string result = "";
            for (int i = 0; i < ticker.Length && ticker[i] != ' '; i++)
                result += ticker[i];
            return result;
        }
        private void Remove_up_to_date_securities(RQ_INFO[] rq_infos)
        {
            foreach (RQ_INFO rq_info in rq_infos)
            {
                List<string> securities_to_update = new List<string>();
                foreach (string security in rq_info.securities)
                {
                    object last_update = database.Execute1("SELECT date FROM " + table + "_update WHERE " + column_security + " = " + "'" + Get_short_ticker(security) + "'" + ";");
                    object current_date = database.Execute1("SELECT CURDATE();");
                    if (last_update == null || last_update.ToString() != current_date.ToString())
                        securities_to_update.Add(security);
                }
                rq_info.securities = securities_to_update.ToArray();
            }
        }
        // Récupère la date de dernière mise à jour de chaque security et prend la date minimale. Remplace startDate par cette date.
       	private void Replace_start_by_min(RQ_INFO[] rq_infos)
       	{
       		foreach (RQ_INFO rq_info in rq_infos)
       		{
                string min_date = "99999999";
       			foreach (string security in rq_info.securities)
       			{
                    object last_update = database.Execute1("SELECT date FROM " + table + "_update WHERE " + column_security + " = " + "'" + Get_short_ticker(security) + "'" + ";");
                    if (last_update == null)
                    {
                        continue;
                    }
                    last_update = last_update.ToString().Replace("-", "");
                    if (String.Compare(last_update.ToString(), min_date) < 0)
                    {
                        min_date = last_update.ToString();
                    }
                }
                if (min_date == "99999999")
       				min_date = "00000000";
       			foreach (REQUEST_PARAM request_param in rq_info.request_params)
       			{
                    if (request_param.name == "startDate")
                    {
                        if (String.Compare(min_date, request_param.value) > 0)
                        {
                            request_param.value = min_date;
                        }
                    }
       			}
       		}
       	}
        private void Delete()
        {
            string query = "";
            foreach (RQ_INFO rq_info in rq_infos)
                foreach (string security in rq_info.securities)
                    query += "DELETE FROM " + table + " WHERE " + column_security + " = " + "'" + Get_short_ticker(security) + "'" + ";";
            if (query != "")
                database.Execute0(query);
        }
        private void Save_last_update(string[] securities)
        {
            string query = "";
            foreach (string security in securities)
                query += "INSERT INTO " + table + "_update (" + column_security + ", date) VALUES (" + "'" + Get_short_ticker(security) + "'" + ", DATE_ADD(CURDATE(), INTERVAL -2 DAY)) ON DUPLICATE KEY UPDATE date = DATE_ADD(CURDATE(), INTERVAL -2 DAY);";
            if (query != "")
                database.Execute0(query);
        }
    }
    class RQ_INFO
    {
        public string[] securities;
        public FIELD[] fields;
        public REQUEST_PARAM[] request_params;

        public RQ_INFO(string[] securities, FIELD[] fields, REQUEST_PARAM[] request_params)
        {
            this.securities = securities;
            this.fields = fields;
            this.request_params = request_params;
        }
    }
    class FIELD
    {
        public string name;
        public string column;
    }
}
