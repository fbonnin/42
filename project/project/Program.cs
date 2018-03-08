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

            /*TEST BLOOM
            SRC_BLOOMBERG src_bloom = new SRC_BLOOMBERG();
            string[] fields = { "ticker", "date", "PX_LOW", "PX_HIGH", "PX_LAST" };
            Object[][] result = src_bloom.Request1(fields, "IBM US Equity", new DateTime(2017, 1, 1), new DateTime(2018, 1, 1));
            Console.WriteLine("Number of rows : {0}", result.Length);
            foreach (Object[] values in result)
            {
                for (int j = 0; j < values.Length; j++)
                    Console.Write("{0}:{1}  ", fields[j], values[j]);
                Console.WriteLine();
            }*/

            /*TEST GET_DATABASES
            CONFIGURATION configuration = new CONFIGURATION("configuration.xml");
            Dictionary<string, DATABASE> databases = configuration.Get_databases();
            Console.WriteLine(databases.Count);
            string[] columns = { "ticker" };
            object[] values = { "TESTT" };
            databases["database"].Insert("table_test", columns, values);*/

            /*REAL MAIN
            CONFIGURATION configuration = new CONFIGURATION("configuration.xml");
            Dictionary<string, SOURCE> sources = null;
            try
            {
                sources = configuration.Get_sources();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: Get_sources: " + e.ToString());
                return;
            }
            Console.WriteLine("number of sources : {0}", sources.Count);
            Dictionary<string, DATABASE> databases = null;
            try
            {
                databases = configuration.Get_databases();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: Get_databases: " + e.ToString());
                return;
            }
            Console.WriteLine("number of databases : {0}", databases.Count);
            OPERATION[] operations = null;
            try
            {
                operations = configuration.Get_operations(sources, databases);
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: Get_operations: " + e.ToString());
                return;
            }
            Console.WriteLine("number of operations : {0}", operations.Length);
            databases["database"].Clear("table_test");
            for (int i = 0; i < operations.Length; i++)
            {
                try
                {
                    operations[i].Do_operation();
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error: operations[{0}]: " + e.ToString(), i);
                    return;
                }
            }*/
        }
    }
    class OPTION
    {
        public string name;
        public string value;
    }
}
