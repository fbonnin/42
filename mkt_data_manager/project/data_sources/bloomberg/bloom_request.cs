using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    partial class SRC_BLOOMBERG
    {
        class BLOOM_REQUEST
        {
            SRC_BLOOMBERG source;
            string[] securities;
            string[] fields;
            REQUEST_PARAM[] request_params;
            string type;
            Request request;

            public BLOOM_REQUEST(SRC_BLOOMBERG source, string[] securities, string[] fields, REQUEST_PARAM[] request_params, string type)
            {
                this.source = source;
                this.securities = securities;
                this.fields = fields;
                this.request_params = request_params;
                this.type = type;
                Prepare_request();
            }
            void Prepare_request()
            {
                request = source.service.CreateRequest(type + "DataRequest");
                foreach (string security in securities)
                    request.Append("securities", security);
                foreach (string field in fields)
                {
                    request.Append("fields", field);
                }
                foreach (REQUEST_PARAM request_param in request_params)
                {
                    if (request_param.value == "true")
                        request.Set(request_param.name, true);
                    else if (request_param.value == "false")
                        request.Set(request_param.name, false);
                    else
                    {
                        request.Set(request_param.name, request_param.value);
                    }
                }
            }
            public Dictionary<string, object>[] Make_request()
            {
                List<Dictionary<string, object>> result = new List<Dictionary<string, object>>();
                if (securities.Length == 0)
                    return result.ToArray();
                source.session.SendRequest(request, null);
                int y = 0;
                while (true)
                {
                    Event event_bloom = source.session.NextEvent();
                    foreach (Message message in event_bloom)
                    {
                        if (message.MessageType.ToString() != type + "DataResponse")
                            continue;
                        if (type == "Reference")
                        {
                            Element security_data_array = message.GetElement("securityData");
                            for (int i = 0; i < security_data_array.NumValues; i++)
                            {
                                Element security_data = security_data_array.GetValueAsElement(i);
                                Get_security_data(result, security_data);
                            }
                        }
                        else if (type == "Historical")
                        {
                            Element security_data = message.GetElement("securityData");
                            Get_security_data(result, security_data);
                        }
                    }
                    if (event_bloom.Type == Event.EventType.RESPONSE)
                        break;
                }
                return result.ToArray();
            }
            private void Get_security_data(List<Dictionary<string, object>> request_result, Element security_data)
            {
                Element field_data_array = security_data.GetElement(3);
                for (int i = 0; i < field_data_array.NumValues; i++)
                {
                    Dictionary<string, object> values = new Dictionary<string, object>();
                    Element field_data = null;
                    if (type == "Reference")
                        field_data = field_data_array;
                    else if (type == "Historical")
                        field_data = field_data_array.GetValueAsElement(i);
                    foreach (string field in fields)
                    {
                        Element element = null;
                        if (field == "security")
                            element = security_data.GetElement("security");
                        else if (field_data.HasElement(field))
                            element = field_data.GetElement(field);
                        else
                        {
                            values.Add(field, "null");
                            continue;
                        }
                        object value;
                        switch (element.Datatype)
                        {
                            case Schema.Datatype.DATE:
                            case Schema.Datatype.DATETIME:
                            case Schema.Datatype.TIME:
                                value = element.GetValueAsDatetime().ToSystemDateTime();
                                break;
                            default:
                                value = element.GetValueAsString();
                                break;
                        }
                        values.Add(field, value);
                    }
                    request_result.Add(values);
                }
            }
        }
    }
}
