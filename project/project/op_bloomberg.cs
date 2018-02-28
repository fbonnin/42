using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class BLOOM_REQUEST1
    {
        SRC_BLOOM source;
        string[] fields;
        string ticker;
        DateTime start_date;
        DateTime end_date;
        Request request;

        public BLOOM_REQUEST1(SRC_BLOOM source, string[] fields, string ticker, DateTime start_date, DateTime end_date)
        {
            this.source = source;
            this.fields = fields;
            this.ticker = ticker;
            this.start_date = start_date;
            this.end_date = end_date;
        }

        private Request Prepare_request()
        {
            request = source.Create_request("Historical Data Request");
            foreach (string field in fields)
                request.Append("fields", field);
            request.Append("securities", ticker);
            request.Set("startDate", start_date);
            request.Set("endDate", end_date);
            return request;
        }

        private Object[][] Make_request()
        {
            List<Object[]> result = new List<Object[]>();

            source.Send_request(request);
            while (true)
            {
                Event event_bloom = source.Next_event();
                foreach (Message message in event_bloom)
                {
                    if (event_bloom.Type != Event.EventType.RESPONSE &&
                        event_bloom.Type != Event.EventType.PARTIAL_RESPONSE)
                        continue;
                    Element security_data = message.GetElement("securityData");
                    Element field_datas = security_data.GetElement("fieldData[]");
                    for (int i = 0; i < field_datas.NumValues; i++)
                    {
                        result.Add(new Object[fields.Length]);
                        Element field_data = field_datas.GetValueAsElement(i);
                        for (int j = 0; j < fields.Length; j++)
                        {
                            result.Last()[j] = field_data.GetElementAsString(fields[j]);
                            Object value;
                            if (fields[j] == "ticker")
                                value = String.Copy(ticker);
                            else
                                value = field_data.GetElementAsString(fields[j]);
                        }
                    }
                }
                if (event_bloom.Type == Event.EventType.RESPONSE)
                    break;
            }
        }
    }
}
