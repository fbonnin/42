using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class Program
    {
        static void Main(string[] args)
        {
            /* TEST DB 
            DB_MYSQL db_mysql = new DB_MYSQL("localhost", "test", "root", "");
            string[] columns = new string[1];
            columns[0] = "age";
            Object[] values = new Object[1];
            values[0] = "15";
            db_mysql.Insert("table_test", columns, values);*/

            SRC_BLOOM src_bloom = new SRC_BLOOM();
            string[] fields = new string[1];
            fields[0] = "PX_LAST";

            Object[][] request_result = src_bloom.Request1(fields, "IBM US Equity", new DateTime(2017, 1, 1), new DateTime(2018, 1, 1));
        }
    }
}
