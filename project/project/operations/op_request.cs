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

        public OP_REQUEST(string type, SOURCE source, DATABASE database, string table, RQ_INFO[] rq_infos, bool update)
        {
            this.type = type;
            this.source = source;
            this.database = database;
            this.table = table;
            this.rq_infos = rq_infos;
        }
        public override void Do_operation()
        {
            if (update)
                Remove_up_to_date_securities(rq_infos);
            else
                database.Clear(table);
            foreach (RQ_INFO rq_info in rq_infos)
            {
                string[] fields = Get_fields(rq_info.fields);
                Dictionary<string, object>[] request_result = source.Request(type, rq_info.securities, fields, rq_info.request_params);
                string query = Get_query(rq_info.fields, request_result);
                database.Execute0(query);
                Save_last_update(rq_info.securities);
            }
        }
        protected virtual string Get_query(FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            List<object[]> rows = new List<object[]>();
            for (int i = 0; i < request_result.Length; i++)
            {
                if (request_result[i].ContainsKey("security"))
                    request_result[i]["security"] = Get_short_ticker((string)request_result[i]["security"]);
                object[] values = new object[fields.Length];
                for (int j = 0; j < fields.Length; j++)
                    values[j] = request_result[i][fields[j].name];
                rows.Add(values);
            }
            string[] columns = Get_columns(fields);
            return database.Get_query_insert(table, columns, rows.ToArray());
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
                    object last_update = database.Execute1("SELECT date FROM " + table + "_update WHERE ticker = " + "'" + security + "'" + ";");
                    object current_date = database.Execute1("SELECT CURDATE();");
                    if (last_update == null || last_update.ToString() != current_date.ToString())
                        securities_to_update.Add(security);
                }
                rq_info.securities = securities_to_update.ToArray();
            }
        }
        private void Save_last_update(string[] securities)
        {
            string query = "";
            foreach (string security in securities)
                query += "INSERT INTO " + table + "_update (ticker, date) VALUES (" + "'" + security + "'" + ", CURDATE()) ON DUPLICATE KEY UPDATE date = CURDATE();";
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
