using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class OPERATION
    {
        protected SOURCE source;
        protected string ticker;
        DATABASE database;
        string table;

        public OPERATION(SOURCE source, string ticker, DATABASE database, string table)
        {
            this.source = source;
            this.ticker = ticker;
            this.database = database;
            this.table = table;
        }
    }
}
