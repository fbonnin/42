 using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class BLOOM_RQ_HISTORICAL
    {
        SRC_BLOOMBERG source;
        string[] securities;
        string[] fields;
        REQUEST_PARAM[] request_params;
        Request request;

        public BLOOM_RQ_HISTORICAL(SRC_BLOOMBERG source, string[] securities, string[] fields, REQUEST_PARAM[] request_params)
        {
            this.source = source;
            this.securities = securities;
            this.fields = fields;
            this.request_params = request_params;
            Prepare_request();
        }
        /*private string Get_date(DateTime date)
        {
            string result = date.Year.ToString();
            if (date.Month < 10)
                result += "0";
            result += date.Month.ToString();
            if (date.Day < 10)
                result += "0";
            result += date.Day.ToString();
            return result;
        }*/
        void Prepare_request()
        {
            request = source.Create_request("HistoricalDataRequest");
            foreach (string security in securities)
                request.Append("securities", security);
            foreach (string field in fields)
                request.Append("fields", field);
            foreach (REQUEST_PARAM request_param in request_params)
                request.Set(request_param.name, request_param.value);
        }
        public Dictionary<string, object>[] Make_request()
        {
            List<Dictionary<string, object>> result = new List<Dictionary<string, object>>();
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
                        Dictionary<string, object> values = new Dictionary<string, object>();
                        Element field_data = field_data_array.GetValueAsElement(i);
                        for (int j = 0; j < fields.Length; j++)
                        {
                            object value;
                            switch (fields[j])
                            {
                                case "security":
                                    value = security_data.GetElementAsString("security");
                                    break;
                                /*case "date":
                                    value = field_data.GetElementAsDatetime(fields[j]);
                                    break;
                                case "PX_LAST":
                                case "PX_LOW":
                                case "PX_HIGH":
                                    NumberFormatInfo nfi = new NumberFormatInfo();
                                    nfi.NumberDecimalSeparator = ".";
                                    double n = field_data.GetElementAsFloat64(fields[j]);
                                    value = n.ToString(nfi);
                                    break;*/
                                default:
                                    value = field_data.GetElementAsString(fields[j]);
                                    break;
                            }
                            values.Add(fields[j], value);

                        }
                        result.Add(values);
                    }
                }
                if (event_bloom.Type == Event.EventType.RESPONSE)
                    break;
            }
            return result.ToArray();
        }
    }
}
