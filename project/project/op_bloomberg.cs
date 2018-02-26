using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    class OP_BLOOMBERG : OPERATION
    {
        string[] fields;
        string start_date;
        string end_date;

        OP_BLOOMBERG(SOURCE source, string ticker, DATABASE database, string table, string[] fields, string start_date, string end_date) : base(source, ticker, database, table)
        {
            this.fields = fields;
            this.start_date = start_date;
            this.end_date = end_date;
        }

        Operation_synchronous()
        {
            Request request = source.service.CreateRequest("Historical Data Request");
            request.Append("securities", ticker);
            foreach (string field in fields)
                request.Append("securities", field);
            request.Set("startDate", start_date);
            request.Set("endDate", end_date);
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
}
