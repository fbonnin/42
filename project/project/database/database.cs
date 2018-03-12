using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class DATABASE
    {
        public abstract void Insert(string table, string[] columns, Object[] values);
        public abstract void Clear(string table);
    }
}
