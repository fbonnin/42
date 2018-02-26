using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class TICKERS
    {
        string file_name;
        string[] tickers;
        int i_ticker = 0;

        public TICKERS(string file_name)
        {
            this.file_name = file_name;
            tickers = System.IO.File.ReadAllLines(file_name);
        }

        public string Get_ticker()
        {
            if (i_ticker == tickers.Length)
                return null;
            return tickers[i_ticker++];
        }
    }
}
