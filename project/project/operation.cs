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
        DATABASE database;
        string table;

        public OPERATION(SOURCE source, DATABASE database, string table)
        {
            this.source = source;
            this.database = database;
            this.table = table;
        }
    }
}
