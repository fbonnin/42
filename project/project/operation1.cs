using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OPERATION1 : OPERATION
    {
        public OPERATION1(SOURCE source, DATABASE database, string table, string[] fields, string[] tickers, DateTime start_date, DateTime end_date, string[] columns) : base(source, database, table)
        {
            foreach(string ticker in tickers)
            {
                Object[][] request_result = source.Request1(fields, ticker, start_date, end_date);
                foreach (Object[] row in request_result)
                    database.Insert(table, columns, row);
            }
        }
    }
}
