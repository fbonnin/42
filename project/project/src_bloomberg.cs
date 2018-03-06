using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class SRC_BLOOMBERG : SOURCE
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
        public Request Create_request(string type)
        {
            return service.CreateRequest(type);
        }
        public void Send_request(Request request)
        {
            session.SendRequest(request, null);
        }
        public Event Next_event()
        {
            return session.NextEvent();
        }
        public override Object[][] Request1(string[] fields, string ticker, DateTime start_date, DateTime end_date)
        {
            BLOOM_REQUEST1 request1 = new BLOOM_REQUEST1(this, fields, ticker, start_date, end_date);
            return request1.Make_request();
        }
    }
}
