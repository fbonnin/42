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
        private XmlElement Get_child(XmlNode node, string child_name)
        {
            return (XmlElement)node.SelectNodes(child_name)[0];
        }
        private XmlElement[] Get_children(XmlNode node, string children_name)
        {
            XmlNodeList node_list = node.SelectNodes(children_name);
            XmlElement[] elements = new XmlElement[node_list.Count];
            for (int i = 0; i < node_list.Count; i++)
                elements[i] = (XmlElement)node_list[i];
            return elements;
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
            List<OPERATION> result = new List<OPERATION>();
            XmlElement e_operations = Get_child(e_configuration, "operations");
            XmlElement[] operation_list = Get_children(e_operations, "operation");
            foreach (XmlElement e_operation in operation_list)
            {
                string type = Get_child(e_operation, "type").InnerText;
                OPERATION operation = null;
                switch (type)
                {
                    case "operation1":
                        XmlElement e_fields = Get_child(e_operation, "fields");
                        XmlElement[] field_list = Get_children(e_fields, "field");
                        string[] fields = new string[field_list.Length];
                        for (int i = 0; i < fields.Length; i++)
                            fields[i] = field_list[i].InnerText;
                        string tickers_file = Get_child(e_operation, "tickers_file").InnerText;
                        XmlElement e_start = Get_child(e_operation, "start_date");
                        int start_year = Int32.Parse(Get_child(e_start, "year").InnerText);
                        int start_month = Int32.Parse(Get_child(e_start, "month").InnerText);
                        int start_day = Int32.Parse(Get_child(e_start, "day").InnerText);
                        DateTime start_date = new DateTime(start_year, start_month, start_day);
                        XmlElement e_end = Get_child(e_operation, "end_date");
                        int end_year = Int32.Parse(Get_child(e_end, "year").InnerText);
                        int end_month = Int32.Parse(Get_child(e_end, "month").InnerText);
                        int end_day = Int32.Parse(Get_child(e_end, "day").InnerText);
                        DateTime end_date = new DateTime(end_year, end_month, end_day);
                        XmlElement e_options = Get_child(e_operation, "options");
                        XmlElement[] option_list = Get_children(e_options, "option");
                        OPTION[] options = new OPTION[option_list.Length];
                        for (int i = 0; i < options.Length; i++)
                        {
                            options[i].name = Get_child(option_list[i], "name").InnerText;
                            options[i].value = Get_child(option_list[i], "value").InnerText;
                        }
                        string source = Get_child(e_operation, "source").InnerText;
                        string database = Get_child(e_operation, "database").InnerText;
                        string table = Get_child(e_operation, "table").InnerText;
                        XmlElement e_columns = Get_child(e_operation, "columns");
                        XmlElement[] column_list = Get_children(e_columns, "column");
                        string[] columns = new string[column_list.Length];
                        for (int i = 0; i < columns.Length; i++)
                            columns[i] = column_list[i].InnerText;
                        operation = new OPERATION1(fields, tickers_file, start_date, end_date, options, sources[source], databases[database], table, columns);
                        break;
                }
                result.Add(operation);
            }
            return result.ToArray();
        }
    }
}
