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
            
            /* TEST BLOOM
            SRC_BLOOM src_bloom = new SRC_BLOOM("", "");
            string[] fields = new string[4];
            fields[0] = "PX_LAST";
            fields[1] = "PX_HIGH";
            fields[2] = "ticker";
            fields[3] = "date";
            Object[][] request_result = src_bloom.Request1(fields, "IBM US Equity", new DateTime(2017, 1, 1), new DateTime(2018, 1, 1));
            Console.WriteLine("Number of rows : {0}", request_result.Length);
            foreach (Object[] row in request_result)
            {
                for (int j = 0; j < row.Length; j++)
                {
                    Console.Write("{0}:{1}  ", fields[j], row[j]);
                }
                Console.WriteLine();
            }*/

            CONFIGURATION configuration = new CONFIGURATION("configuration.xml");
            Dictionary<string, DATABASE> databases = configuration.Get_databases();
            Console.WriteLine(databases.Count);
            string[] columns = new string[1];
            columns[0] = "name";
            Object[] values = new object[1];
            values[0] = "autrrett";
            databases["db1"].Insert("table_test", columns, values);
        }
    }
}
