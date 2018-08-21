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
            /*int[][] tab = new int[15][];
            for (int i = 0; i < 15; i++)
            {
                tab[i] = new int[30];
                for (int j = 0; j < 30; j++)
                {
                    tab[i][j] = i + j;
                    Console.WriteLine(tab[i][j]);
                }
            }*/


            /*untestDB_MYSQL db_mysql = new DB_MYSQL("localhost", "database_test", "root", "");
            string table = "table_test";
            string[] columns = { "ticker", "low", "high" };
            object[][] rows = new object[10000000][];
            for (int i = 0; i < rows.Length; i++)
            {
                rows[i] = new object[3];
                rows[i][0] = "tttest";
                rows[i][1] = "14";
                rows[i][2] = "3,145";
            }

            db_mysql.Insert_update_split(table, columns, rows);*/

            /*REAL MAIN*/
            CONFIGURATION configuration = new CONFIGURATION("config.xml");
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
            }
            Console.WriteLine("\n\nDONE");
            Console.ReadLine();

            /*TEST DB
            DB_MYSQL db_mysql = new DB_MYSQL("localhost", "database_test", "root", "");
            string[] columns = { "ticker", "low", "high" };
            Object[] values = { "ticker_test", -15, 23 };
            db_mysql.Insert("table_test", columns, values);*/

            /*TEST BLOOM
            SRC_BLOOMBERG src_bloom = new SRC_BLOOMBERG();
            string[] securities = { "NOV US Equity" };
            Console.WriteLine("hihss");
            string[] fields = { "PX_LAST", "PX_VOLUME", "SHORT_INT" };
            Console.WriteLine("rrr");
            REQUEST_PARAM[] request_params = new REQUEST_PARAM[1];
            request_params[0] = new REQUEST_PARAM("startDate", "20180601");
            string a;
            a = "aa";
            Dictionary<string, object>[] result = src_bloom.Request("histo", securities, fields, request_params);
            foreach (Dictionary<string, object> values in result)
            {
                Console.WriteLine(values["SHORT_INT"]);
            }
            //Console.WriteLine("Number of rows : {0}", result.Length);
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
        }
    }
}
