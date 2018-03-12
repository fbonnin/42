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
        RQ_HISTO_INFO[] rq_histo_infos;

        public OP_HISTORICAL(SOURCE source, DATABASE database, string table, RQ_HISTO_INFO[] rq_histo_infos)
        {
            this.source = source;
            this.database = database;
            this.table = table;
            this.rq_histo_infos = rq_histo_infos;
        }
        public override void Do_operation()
        {
            foreach (RQ_HISTO_INFO rq_histo_info in rq_histo_infos)
            {
                string[] fields = Get_fields(rq_histo_info.fields);
                string[] columns = Get_columns(rq_histo_info.fields);
                Dictionary<string, object>[] request_result = source.Rq_historical(rq_histo_info.securities, fields, rq_histo_info.request_params);
                string query = Get_query(rq_histo_info.fields, request_result);
                database.Execute(query);
            }
        }
        protected virtual string Get_query(FIELD[] fields, Dictionary<string, object>[] request_result)
        {
            List<object[]> rows = new List<object[]>();
            for (int i = 0; i < request_result.Length; i++)
            {
                object[] row = new object[fields.Length];
                for (int j = 0; j < fields.Length; j++)
                {
                    row[j] = request_result[i][fields[j].name];
                }
                rows.Add(row);
            }
            string[] columns = Get_columns(fields);
            return database.Get_query_insert(table, columns, rows.ToArray());
        }
        private string[] Get_fields(FIELD[] fields)
        {
            string[] result = new string[fields.Length];
            for (int i = 0; i < fields.Length; i++)
                result[i] = fields[i].name;
            return result;
        }
        private string[] Get_columns(FIELD[] fields)
        {
            string[] result = new string[fields.Length];
            for (int i = 0; i < fields.Length; i++)
                result[i] = fields[i].column;
            return result;
        }
    }
    class RQ_HISTO_INFO
    {
        public string[] securities;
        public FIELD[] fields;
        public REQUEST_PARAM[] request_params;

        public RQ_HISTO_INFO(string[] securities, FIELD[] fields, REQUEST_PARAM[] request_params)
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

        public FIELD(string name, string column)
        {
            this.name = name;
            this.column = column;
        }
    }
}
