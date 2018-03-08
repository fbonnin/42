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
                XmlElement e_type = Get_child(e_operation, "type", "operation/type");
                string type = e_type.InnerText;
                switch (type)
                {
                    case "operation1":
                        result[i] = Get_operation1(sources, databases, e_operation);
                        break;
                    default:
                        throw new CONFIGURATION_ERROR("unknown operation: " + type);
                }
            }
            return result;
        }
        private OPERATION1 Get_operation1(Dictionary<string, SOURCE> sources, Dictionary<string, DATABASE> databases, XmlElement e_operation)
        {
            List<REQUEST_PARAM> request_params = new List<REQUEST_PARAM>();
            XmlElement e_securities = Get_child(e_operation, "securities_file");
            string securities_file = e_securities.InnerText;
            string[] securities;
            try
            {
                securities = System.IO.File.ReadAllLines(securities_file);
            }
            catch (Exception)
            {
                throw new CONFIGURATION_ERROR("could not read file: " + securities_file);
            }
            foreach (string security in securities)
                request_params.Add(new REQUEST_PARAM("securities", security));
            XmlElement e_fields = Get_child(e_operation, "fields", "fields");
            XmlElement[] el_field = Get_children(e_fields, "field", "field");
            foreach (XmlElement e_field in el_field)
                request_params.Add(new REQUEST_PARAM("fields", e_field.InnerText));
            XmlElement e_start = Get_child(e_operation, "start_date");
            if (e_start != null)
                request_params.Add(new REQUEST_PARAM("startDate", e_start.InnerText));
            XmlElement e_end = Get_child(e_operation, "endDate");
            if (e_end != null)
                request_params.Add(new REQUEST_PARAM("endDate", e_end.InnerText));
            XmlElement e_periodicity = Get_child(e_operation, "periodicity");
            if (e_periodicity != null)
                request_params.Add(new REQUEST_PARAM("periodicitySelection", e_periodicity.InnerText));
            XmlElement e_options = Get_child(e_operation, "options");
            if (e_options != null)
            {
                XmlElement[] el_option = Get_children(e_options, "option");
                foreach (XmlElement e_option in el_option)
                {
                    XmlElement e_option_type = Get_child(e_option, "type");
                    if (e_option_type == null)
                        throw new XML_ELEMENT_MISSING("option type");
                    string option_type = e_option.InnerText;
                    XmlElement e_value = Get_child(e_option, "value");
                    if (e_value == null)
                        throw new XML_ELEMENT_MISSING("option value");
                    string value = e_value.InnerText;
                    request_params.Add(new REQUEST_PARAM(option_type, value));
                }
            }
            string source = Get_child(e_operation, "source", "operation/source").InnerText;
            if (!sources.ContainsKey(source))
                throw new CONFIGURATION_ERROR("unknown source" + source);
            string database = Get_child(e_operation, "database", "operation/database").InnerText;
            if (!databases.ContainsKey(database))
                throw new CONFIGURATION_ERROR("unknown database: " + database);
            string table = Get_child(e_operation, "table", "table").InnerText;
            XmlElement e_columns = Get_child(e_operation, "columns", "columns");
            XmlElement[] el_column = Get_children(e_columns, "column", "column");
            if (el_column.Length != el_field.Length)
                throw new CONFIGURATION_ERROR("the number of columns does not match the number of fields");
            string[] columns = new string[el_column.Length];
            for (int j = 0; j < columns.Length; j++)
                columns[j] = el_column[j].InnerText;
            return new OPERATION1(request_params.ToArray(), sources[source], databases[database], table, columns);
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
