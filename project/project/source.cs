using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class SOURCE
    {
        public abstract Object[][] Request1(REQUEST_PARAM[] request_params);
    }
    class REQUEST_PARAM
    {
        public string type;
        public string value;

        public REQUEST_PARAM(string type, string value)
        {
            this.type = type;
            this.value = value;
        }
    }
}
