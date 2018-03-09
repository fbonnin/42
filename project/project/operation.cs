using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class OPERATION
    {
        public abstract void Do_operation();
    }

    class OPERATION_1 : OPERATION
    {
        SOURCE source;
        DATABASE database;
        string table;
        HISTORICAL_REQUEST_INFO[] historical_request_infos;

        public OPERATION_1(SOURCE source, DATABASE database, string table, HISTORICAL_REQUEST_INFO[] historical_request_infos)
        {
            this.source = source;
            this.database = database;
            this.table = table;
            this.historical_request_infos = historical_request_infos;
        }
        private void Get_fields_and_columns(HISTORICAL_REQUEST_INFO historical_request_info, string[] fields, string[] columns)
        {

        }
        /*private void Add_id(string[] fields, object[][] request_result, string[] columns)
        {
            foreach (object[] row in request_result)
            {
                historical

                object[] new_row = new object[row.Length + 1];
                new_row[0] = row[]
                for (int i = 0; i < row.Length; i++)
                    new_row;
                
            }
            string[] new_columns = new string[columns.Length + 1];
            new_columns[0] = "ID";
            for (int i = 0; i < columns.Length; i++)
                new_columns[i + 1] = columns[i];
        }*/
        private string Get_id(string[] fields, object[] values)
        {
            string result = "";
            for (int i = 0; i < fields.Length; i++)
            {
                if (fields[i] == "security")
                {
                    result += values[i];
                    break;
                }
            }
            for (int i = 0; i < fields.Length; i++)
            {
                if (fields[i] == "date")
                {
                    result += values[i];
                    break;
                }
            }
            return result;
        }
        public override void Do_operation()
        {
            string[] fields = null;
            string[] columns = null;
            Get_fields_and_columns(historical_request_infos[0], fields, columns);
            object[][] request_result = source.Historical_request(historical_request_infos[0].securities, fields, historical_request_infos[0].request_params);
            database.Insert(table, columns, request_result);
            for (int i = 1; i < historical_request_infos.Length; i++)
            {
                Get_fields_and_columns(historical_request_infos[i], fields, columns);
                request_result = source.Historical_request(historical_request_infos[0].securities, fields, historical_request_infos[0].request_params);
                database.Update(table, 
            }
        }

    }
    class HISTORICAL_REQUEST_INFO
    {
        public string[] securities;
        public FIELD[] fields;
        public REQUEST_PARAM[] request_params;
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
