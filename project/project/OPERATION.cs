using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class OPERATION
    {
        SOURCE source;
        TICKERS tickers;
        DATABASE database;
        string table;

        public OPERATION(SOURCE source, string tickers_file_name, DATABASE database, string table)
        {
            this.source = source;
            this.tickers = new TICKERS(tickers_file_name);
            this.database = database;
            this.table = table;
        }
        protected abstract void Process_ticker(string ticker);
        public void Process_tickers()
        {
            string ticker;
            while ((ticker = tickers.Get_ticker()) != null)
                Process_ticker(ticker);
        }
    }
}
