using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml;

namespace project
{
    class CONFIGURATION
    {
        XmlElement e_configuration;

        public CONFIGURATION(string file)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(file);
            e_configuration = doc.DocumentElement;
        }
        private XmlElement[] Get_children(XmlNode node, string children_name)
        {
            XmlNodeList node_list = node.SelectNodes(children_name);
            XmlElement[] result = new XmlElement[node_list.Count];
            for (int i = 0; i < node_list.Count; i++)
                result[i] = (XmlElement)node_list[i];
            return result;
        }
        private XmlElement[] Get_children(XmlNode node, string children_name, string error)
        {
            XmlElement[] result = Get_children(node, children_name);
            if (result.Length == 0)
                throw new XML_ELEMENT_MISSING(error);
            return result;
        }
        private XmlElement Get_child(XmlNode node, string child_name)
        {
            XmlElement[] children = Get_children(node, child_name);
            if (children.Length == 0)
                return null;
            return children[0];
        }
        private XmlElement Get_child(XmlNode node, string child_name, string error)
        {
            XmlElement result = Get_child(node, child_name);
            if (result == null)
                throw new XML_ELEMENT_MISSING(error);
            return result;
        }
        public Dictionary<string, SOURCE> Get_sources()
        {
            Dictionary<string, SOURCE> result = new Dictionary<string, SOURCE>();
            XmlElement e_sources = Get_child(e_configuration, "sources");
            XmlElement[] source_list = Get_children(e_sources, "source");
            foreach (XmlElement e_source in source_list)
            {
                string name = Get_child(e_source, "name").InnerText;
                string type = Get_child(e_source, "type").InnerText;
                SOURCE source = null;
                switch (type)
                {
                    case "bloomberg":
                        source = new SRC_BLOOMBERG();
                        break;
                }
                result.Add(name, source);
            }
            return result;
        }
        public Dictionary<string, DATABASE> Get_databases()
        {
            Dictionary<string, DATABASE> result = new Dictionary<string, DATABASE>();
            XmlElement e_databases = Get_child(e_configuration, "databases");
            XmlElement[] database_list = Get_children(e_databases, "database");
            foreach (XmlElement e_database in database_list)
            {
                string name = Get_child(e_database, "name").InnerText;
                string type = Get_child(e_database, "type").InnerText;
                DATABASE database = null;
                switch (type)
                {
                    case "mysql":
                        string host = Get_child(e_database, "host").InnerText;
                        string real_name = Get_child(e_database, "real_name").InnerText;
                        string user = Get_child(e_database, "user").InnerText;
                        string password = Get_child(e_database, "password").InnerText;
                        database = new DB_MYSQL(host, real_name, user, password);
                        break;
                }
                result.Add(name, database);
            }
            return result;
        }
        public OPERATION[] Get_operations(Dictionary<string, SOURCE> sources, Dictionary<string, DATABASE> databases)
        {
            XmlElement e_operations = Get_child(e_configuration, "operations", "operations");
            XmlElement[] el_operation = Get_children(e_operations, "operation");
            OPERATION[] result = new OPERATION[el_operation.Length];
            for (int i = 0; i < result.Length; i++)
            {
                XmlElement e_operation = el_operation[i];
                string type = Get_child(e_operation, "type", "operation/type").InnerText;
                switch (type)
                {
                    case "reference":
                    case "histo":
                    case "histo1":
                        result[i] = Get_op_request(sources, databases, e_operation, type);
                        break;
                    default:
                        throw new CONFIGURATION_ERROR("unknown operation: " + type);
                }
            }
            return result;
        }
        private OP_REQUEST Get_op_request(Dictionary<string, SOURCE> sources, Dictionary<string, DATABASE> databases, XmlElement e_operation, string type)
        {
            string source = Get_child(e_operation, "source", "operation/source").InnerText;
            if (!sources.ContainsKey(source))
                throw new CONFIGURATION_ERROR("unknown source: " + source);
            string database = Get_child(e_operation, "database", "operation/database").InnerText;
            if (!databases.ContainsKey(database))
                throw new CONFIGURATION_ERROR("unknown database: " + database);
            string table = Get_child(e_operation, "table", "table").InnerText;
            bool update = (Get_child(e_operation, "update") != null);
            XmlElement e_requests = Get_child(e_operation, "requests", "requests");
            XmlElement[] el_request = Get_children(e_requests, "request", "request");
            RQ_INFO[] rq_infos = new RQ_INFO[el_request.Length];
            for (int i = 0; i < el_request.Length; i++)
            {
                XmlElement e_request = el_request[i];
                string securities_file = Get_child(e_request, "securities_file", "securities_file").InnerText;
                string[] securities;
                try
                {
                    securities = System.IO.File.ReadAllLines(securities_file);
                }
                catch (Exception)
                {
                    throw new CONFIGURATION_ERROR("could not read file: " + securities_file);
                }
                XmlElement e_fields = Get_child(e_request, "fields", "fields");
                XmlElement[] el_field = Get_children(e_fields, "field", "field");
                FIELD[] fields = new FIELD[el_field.Length];
                for (int j = 0; j < fields.Length; j++)
                    fields[j] = new FIELD();
                for (int j = 0; j < fields.Length; j++)
                {
                    fields[j].name = Get_child(el_field[j], "name", "field/name").InnerText;
                    fields[j].column = Get_child(el_field[j], "column", "column").InnerText;
                }
                List<REQUEST_PARAM> request_params = new List<REQUEST_PARAM>();
                XmlElement e_start = Get_child(e_request, "start_date");
                if (e_start != null)
                    request_params.Add(new REQUEST_PARAM("startDate", e_start.InnerText));
                XmlElement e_end = Get_child(e_request, "end_date");
                if (e_end != null)
                    request_params.Add(new REQUEST_PARAM("endDate", e_end.InnerText));
                XmlElement e_periodicity = Get_child(e_request, "periodicity");
                if (e_periodicity != null)
                    request_params.Add(new REQUEST_PARAM("periodicitySelection", e_periodicity.InnerText));
                XmlElement e_options = Get_child(e_request, "options");
                if (e_options != null)
                {
                    XmlElement[] el_option = Get_children(e_options, "option");
                    foreach (XmlElement e_option in el_option)
                    {
                        string name = Get_child(e_option, "name", "option/name").InnerText;
                        string value = Get_child(e_option, "value", "option/value").InnerText;
                        request_params.Add(new REQUEST_PARAM(name, value));
                    }
                }
                rq_infos[i] = new RQ_INFO(securities, fields, request_params.ToArray());
            }
            if (type == "histo1")
                return new OP_HISTO1(type, sources[source], databases[database], table, rq_infos, update);
            else
                return new OP_REQUEST(type, sources[source], databases[database], table, rq_infos, update);
        }
    }
    class CONFIGURATION_ERROR : Exception
    {
        string error;

        public CONFIGURATION_ERROR(string error)
        {
            this.error = error;
        }
        public override string ToString()
        {
            return "Configuration error: " + error;
        }
    }
    class XML_ELEMENT_MISSING : Exception
    {
        string error;

        public XML_ELEMENT_MISSING(string error)
        {
            this.error = error;
        }
        public override string ToString()
        {
            return "XML element missing: " + error;
        }
    }
}
