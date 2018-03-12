using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class SOURCE
    {
        public abstract Dictionary<string, object>[] Rq_historical(string[] securities, string[] fields, REQUEST_PARAM[] request_params);
    }
    class REQUEST_PARAM
    {
        public string name;
        public string value;

        public REQUEST_PARAM(string name, string value)
        {
            this.name = name;
            this.value = value;
        }
    }
}
