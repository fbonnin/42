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

    class OPERATION1 : OPERATION
    {
        string[] fields;
        string tickers_file;
        DateTime start_date;
        DateTime end_date;
        SOURCE source;
        DATABASE database;
        string table;
        string[] columns;

        public OPERATION1(string[] fields, string tickers_file, DateTime start_date, DateTime end_date, SOURCE source, DATABASE database, string table, string[] columns)
        {
            this.fields = fields;
            this.tickers_file = tickers_file;
            this.start_date = start_date;
            this.end_date = end_date;
            this.source = source;
            this.database = database;
            this.table = table;
            this.columns = columns;
        }
        public override void Do_operation()
        {
            string[] tickers = System.IO.File.ReadAllLines(tickers_file);
            foreach (string ticker in tickers)
            {
                Object[][] request_result = source.Request1(fields, ticker, start_date, end_date);
                foreach (Object[] row in request_result)
                    database.Insert(table, columns, row);
            }
        }
    }
}
