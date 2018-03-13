 using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    partial class SRC_BLOOMBERG
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
            void Prepare_request()
            {
                request = source.service.CreateRequest("HistoricalDataRequest");
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
                source.session.SendRequest(request, null);
                while (true)
                {
                    Event event_bloom = source.session.NextEvent();
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
                            foreach (string field in fields)
                            {
                                Element element;
                                if (field == "security")
                                    element = security_data.GetElement("security");
                                else
                                    element = field_data.GetElement(field);
                                object value;
                                switch (element.Datatype)
                                {
                                    case Schema.Datatype.DATE:
                                    case Schema.Datatype.DATETIME:
                                    case Schema.Datatype.TIME:
                                        value = element.GetValueAsDatetime().ToSystemDateTime();
                                        break;
                                    default:
                                        value = element.GetValue();
                                        break;
                                }
                                values.Add(field, value);
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
}
