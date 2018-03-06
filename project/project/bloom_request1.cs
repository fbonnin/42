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
        SRC_BLOOMBERG source;
        string[] fields;
        string ticker;
        DateTime start_date;
        DateTime end_date;
        Request request;

        public BLOOM_REQUEST1(SRC_BLOOMBERG source, string[] fields, string ticker, DateTime start_date, DateTime end_date)
        {
            this.source = source;
            this.fields = fields;
            this.ticker = ticker;
            this.start_date = start_date;
            this.end_date = end_date;
            Prepare_request();
        }
        private string Get_date(DateTime date)
        {
            string result = date.Year.ToString();
            if (date.Month < 10)
                result += "0";
            result += date.Month.ToString();
            if (date.Day < 10)
                result += "0";
            result += date.Day.ToString();
            return result;
        }
        void Prepare_request()
        {
            request = source.Create_request("HistoricalDataRequest");
            foreach (string field in fields)
                request.Append("fields", field);
            request.Append("securities", ticker);
            request.Set("startDate", Get_date(start_date));
            request.Set("endDate", Get_date(end_date));
        }
        public Object[][] Make_request()
        {
            List<Object[]> result = new List<Object[]>();
            source.Send_request(request);
            while (true)
            {
                Event event_bloom = source.Next_event();
                foreach (Message message in event_bloom)
                {
                    if (message.MessageType.ToString() != "HistoricalDataResponse")
                        continue;
                    Element security_data = message.GetElement("securityData");
                    Element field_data_array = security_data.GetElement(3);
                    for (int i = 0; i < field_data_array.NumValues; i++)
                    {
                        Object[] values = new Object[fields.Length];
                        Element field_data = field_data_array.GetValueAsElement(i);
                        for (int j = 0; j < fields.Length; j++)
                        {
                            Object value;
                            switch (fields[j])
                            {
                                case "ticker":
                                    value = String.Copy(ticker);
                                    break;
                                case "date":
                                    value = field_data.GetElementAsDatetime("date");
                                    break;
                                default:
                                    value = field_data.GetElementAsString(fields[j]);
                                    break;
                            }
                            values[j] = value;
                        }
                        result.Add(values);
                    }
                }
                if (event_bloom.Type == Event.EventType.RESPONSE)
                    break;
            }
            return result.ToArray();
        }
        /*old version
        public Object[][] Make_request()
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
                    Element field_data_array = security_data.GetElement(3);
                    for (int i = 0; i < field_data_array.NumValues; i++)
                    {
                        result.Add(new Object[fields.Length]);
                        Element field_data = field_data_array.GetValueAsElement(i);
                        for (int j = 0; j < fields.Length; j++)
                        {
                            Object value;
                            if (fields[j] == "ticker")
                                value = String.Copy(ticker);
                            else
                                value = field_data.GetElementAsString(fields[j]);
                            result.Last()[j] = value;
                        }
                    }
                }
                if (event_bloom.Type == Event.EventType.RESPONSE)
                    break;
            }
            return result.ToArray();
        }*/
    }
}
