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
        REQUEST_PARAM[] request_params;
        SOURCE source;
        DATABASE database;
        string table;
        string[] columns;

        public OPERATION_1(REQUEST_PARAM[] request_params, SOURCE source, DATABASE database, string table, string[] columns)
        {
            this.source = source;
            this.request_params = request_params;
            this.database = database;
            this.table = table;
            this.columns = columns;
        }
        public override void Do_operation()
        {
            Object[][] request_result = source.Request1(request_params);
            database.Insert(table, columns, request_result);
        }
    }

    class OPERATION_1_1
}
