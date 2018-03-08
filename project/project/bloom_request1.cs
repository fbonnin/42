using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class BLOOM_REQUEST1
    {
        SRC_BLOOMBERG source;
        REQUEST_PARAM[] request_params;
        List<string> fields;
        Request request;

        public BLOOM_REQUEST1(SRC_BLOOMBERG source, REQUEST_PARAM[] request_params)
        {
            this.source = source;
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
            for (int i = 0; i < request_params.Length; i++)
            {
                REQUEST_PARAM request_param = request_params[i];
                if (request_param.type == "securities" || request_param.type == "fields")
                {
                    request.Append(request_param.type, request_param.value);
                    if (request_param.type == "fields")
                        fields.Add(request_param.value);
                }
                else
                    request.Set(request_param.type, request_param.value);
            }
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
                        Object[] values = new Object[fields.Count];
                        Element field_data = field_data_array.GetValueAsElement(i);
                        for (int j = 0; j < fields.Count; j++)
                        {
                            Object value;
                            switch (fields[j])
                            {
                                case "ticker":
                                    value = security_data.GetElementAsString("security");
                                    break;
                                case "date":
                                    value = field_data.GetElementAsDatetime(fields[j]);
                                    break;
                                case "PX_LAST":
                                case "PX_LOW":
                                case "PX_HIGH":
                                    NumberFormatInfo nfi = new NumberFormatInfo();
                                    nfi.NumberDecimalSeparator = ".";
                                    double n = field_data.GetElementAsFloat64(fields[j]);
                                    Console.WriteLine("value = {0}", n.ToString(nfi));
                                    value = n.ToString(nfi);
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
    }
}
