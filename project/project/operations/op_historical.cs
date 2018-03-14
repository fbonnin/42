using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_HISTORICAL : OPERATION
    {
        SOURCE source;
        DATABASE database;
        protected string table;
        HISTO_RQ_INFO[] histo_rq_infos;

        public OP_HISTORICAL(SOURCE source, DATABASE database, string table, HISTO_RQ_INFO[] histo_rq_infos)
        {
            this.source = source;
            this.database = database;
            this.table = table;
            this.histo_rq_infos = histo_rq_infos;
        }
        public override void Do_operation()
        {
            database.Clear(table);
            foreach (HISTO_RQ_INFO histo_rq_info in histo_rq_infos)
            {
                string[] fields = Get_fields(histo_rq_info.fields);
                Dictionary<string, object>[] request_result = source.Rq_historical(histo_rq_info.securities, fields, histo_rq_info.request_params);
                string query = Get_query(histo_rq_info.fields, request_result);
                database.Execute0(query);
                Update(histo_rq_info.securities);
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
        string[] Get_fields(FIELD[] fields)
        {
            string[] result = new string[fields.Length];
            for (int i = 0; i < fields.Length; i++)
                result[i] = fields[i].name;
            return result;
        }
        string[] Get_columns(FIELD[] fields)
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
        private void Update(string[] securities)
        {
            string query = "";
            foreach (string security in securities)
                query += "INSERT INTO " + table + "_update (ticker, date) VALUES (" + "'" + security + "'" + ", CURDATE()) ON DUPLICATE KEY UPDATE date = CURDATE();";
            database.Execute0(query);
        }
    }
    class HISTO_RQ_INFO
    {
        public string[] securities;
        public FIELD[] fields;
        public REQUEST_PARAM[] request_params;

        public HISTO_RQ_INFO(string[] securities, FIELD[] fields, REQUEST_PARAM[] request_params)
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
