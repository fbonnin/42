using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class OP_BLOOMBERG : OPERATION
    {
        public void Make_request()
        {
            session.SendRequest(request, null);
            bool done = false;
            while (!done)
            {
                Event bloomberg_event = session.NextEvent();
                if (bloomberg_event == Event.EventType.RESPONSE)
                {

                }
            }
        }
    }

    class BLOOM_HISTORICAL_DATA_REQUEST : OPERATION
    {
        Request request;
        string[] fields;
        string[] tickers;
        string start_date;
        string end_date;

        public BLOOM_HISTORICAL_DATA_REQUEST(SOURCE source, DATABASE database, string table, string[] fields, string[] tickers, string start_date, string end_date) : base(source, database, table)
        {
            this.fields = fields;
            this.tickers = tickers;
            this.start_date = start_date;
            this.end_date = end_date;
        }

        private void Make_request()
        {
            request = source.service.CreateRequest("Historical Data Request");
            foreach (string field in fields)
                request.Append("fields", field);
            foreach (string ticker in tickers)
                request.Append("securities", ticker);
            request.Set("startDate", start_date);
            request.Set("endDate", end_date);
        }
    }

    class BLOOM_REQUEST1
    {
        SRC_BLOOM source;
        string[] fields;
        string ticker;
        DateTime start_date;
        DateTime end_date;

        public BLOOM_REQUEST1(SRC_BLOOMBERG source, string[] fields, string ticker, string start_date, string end_date)
        {
            this.source = source;
            this.fields = fields;
            this.ticker = ticker;
            this.start_date = start_date;
            this.end_date = end_date;
        }

        private Request Make_request()
        {
            request = source.service.CreateRequest("Historical Data Request");
            foreach (string field in fields)
                request.Append("fields", field);
            request.Append("securities", ticker);
            request.Set("startDate", start_date);
            request.Set("endDate", end_date);
        }
    }
}
