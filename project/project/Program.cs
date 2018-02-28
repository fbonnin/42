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
            DB_MYSQL db_mysql = new DB_MYSQL("localhost", "test", "root", "");
            string[] columns = new string[1];
            columns[0] = "age";
            Object[] values = new Object[1];
            values[0] = "15";
            db_mysql.Insert("table_test", columns, values);
        }
    }
}
