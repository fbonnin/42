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
            /*TEST DB
            DB_MYSQL db_mysql = new DB_MYSQL("localhost", "database_test", "root", "");
            string[] columns = { "ticker", "low", "high" };
            Object[] values = { "ticker_test", -15, 23 };
            db_mysql.Insert("table_test", columns, values);*/

            /*TEST BLOOM*/
            SRC_BLOOMBERG src_bloom = new SRC_BLOOMBERG();
            string[] fields = { "ticker", "date", "PX_LOW", "PX_HIGH", "PX_LAST" };
            Object[][] result = src_bloom.Request1(fields, "IBM US Equity", new DateTime(2017, 1, 1), new DateTime(2018, 1, 1));
            Console.WriteLine("Number of rows : {0}", result.Length);
            foreach (Object[] values in result)
            {
                for (int j = 0; j < values.Length; j++)
                    Console.Write("{0}:{1}  ", fields[j], values[j]);
                Console.WriteLine();
            }

            /*TEST GET_DATABASES
            CONFIGURATION configuration = new CONFIGURATION("configuration.xml");
            Dictionary<string, DATABASE> databases = configuration.Get_databases();
            Console.WriteLine(databases.Count);
            string[] columns = new string[1];
            columns[0] = "ticker";
            Object[] values = new object[1];
            values[0] = "HELLOWORLD";
            databases["database"].Insert("table_test", columns, values);*/
        }
    }
}
