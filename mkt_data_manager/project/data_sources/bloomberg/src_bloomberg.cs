using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    partial class SRC_BLOOMBERG : SOURCE
    {
        private Session session;
        private Service service;

        public SRC_BLOOMBERG()
        {
            session = new Session();
            session.Start();
            session.OpenService("//blp/refdata");
            service = session.GetService("//blp/refdata");
        }
        ~SRC_BLOOMBERG()
        {
            session.Stop();
        }
        public override Dictionary<string, object>[] Request(string type, string[] securities, string[] fields, REQUEST_PARAM[] request_params)
        {
            if (type.Substring(0, 5) == "histo")
                type = "Historical";
            else if (type.Substring(0, 9) == "reference")
                type = "Reference";
            else
                return null;
            BLOOM_REQUEST request = new BLOOM_REQUEST(this, securities, fields, request_params, type);
            return request.Make_request();
        }
    }
}
