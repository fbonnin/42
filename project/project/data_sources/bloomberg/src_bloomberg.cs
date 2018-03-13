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
        public override Dictionary<string, object>[] Rq_historical(string[] securities, string[] fields, REQUEST_PARAM[] request_params)
        {
            BLOOM_RQ_HISTORICAL request = new BLOOM_RQ_HISTORICAL(this, securities, fields, request_params);
            return request.Make_request();
        }
    }
}
