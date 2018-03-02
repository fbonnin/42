﻿using System;
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

        public Dictionary<string, SOURCE> Get_sources()
        {
            Dictionary<string, SOURCE> result = new Dictionary<string, SOURCE>();
            XmlElement sources = (XmlElement)e_configuration.GetElementsByTagName("sources")[0];
            XmlNodeList source_list = sources.GetElementsByTagName("source");
            for (int i = 0; i < source_list.Count; i++)
            {
                XmlElement source = (XmlElement)source_list[i];
                string name = ((XmlElement)source.GetElementsByTagName("name")[0]).InnerText;
                string type = ((XmlElement)source.GetElementsByTagName("type")[0]).InnerText;
                string login = ((XmlElement)source.GetElementsByTagName("login")[0]).InnerText;
                string password = ((XmlElement)source.GetElementsByTagName("password")[0]).InnerText;
                SOURCE src = null;
                switch (type)
                {
                    case "bloomberg":
                        src = new SRC_BLOOM();
                        break;
                }
                result.Add(name, src);
            }
            return result;
        }

        public Dictionary<string, DATABASE> Get_databases()
        {
            Dictionary<string, DATABASE> result = new Dictionary<string, DATABASE>();
            XmlElement databases = (XmlElement)e_configuration.GetElementsByTagName("databases")[0];
            XmlNodeList database_list = databases.GetElementsByTagName("database");
            for (int i = 0; i < database_list.Count; i++)
            {
                XmlElement database = (XmlElement)database_list[i];
                string name = ((XmlElement)database.GetElementsByTagName("name")[0]).InnerText;
                string type = ((XmlElement)database.GetElementsByTagName("type")[0]).InnerText;
                string host = ((XmlElement)database.GetElementsByTagName("host")[0]).InnerText;
                string db_name = ((XmlElement)database.GetElementsByTagName("db_name")[0]).InnerText;
                string user = ((XmlElement)database.GetElementsByTagName("user")[0]).InnerText;
                string password = ((XmlElement)database.GetElementsByTagName("password")[0]).InnerText;
                DATABASE db = null;
                switch (type)
                {
                    case "mysql":
                        db = new DB_MYSQL(host, db_name, user, password);
                        break;
                }
                result.Add(name, db);
            }
            return result;
        }

        public List<OPERATION> Get_operations(Dictionary<string, SOURCE> sources, Dictionary<string, DATABASE> databases)
        {
            List<OPERATION> result = new List<OPERATION>();
            XmlElement e_operations = (XmlElement)e_configuration.GetElementsByTagName("operations")[0];
            XmlNodeList operation_list = e_operations.GetElementsByTagName("operation");
            for (int i = 0; i < operation_list.Count; i++)
            {
                XmlElement e_operation = (XmlElement)operation_list[i];
                string type = ((XmlElement)e_operation.GetElementsByTagName("type")[0]).InnerText;
                OPERATION op = null;
                switch (type)
                {
                    case "operation1":
                        XmlNodeList field_list = ((XmlElement)e_operation.GetElementsByTagName("fields")[0]).GetElementsByTagName("field");
                        string[] fields = new string[field_list.Count];
                        for (int j = 0; j < field_list.Count; j++)
                            fields[j] = ((XmlElement)field_list[j]).InnerText;
                        string tickers_file = ((XmlElement)e_operation.GetElementsByTagName("tickers_file")[0]).InnerText;
                        XmlElement e_start = (XmlElement)e_operation.GetElementsByTagName("start_date")[0];
                        int start_year = Int32.Parse(((XmlElement)e_start.GetElementsByTagName("year")[0]).InnerText);
                        int start_month = Int32.Parse(((XmlElement)e_start.GetElementsByTagName("month")[0]).InnerText);
                        int start_day = Int32.Parse(((XmlElement)e_start.GetElementsByTagName("day")[0]).InnerText);
                        DateTime start_date = new DateTime(start_year, start_month, start_day);
                        XmlElement e_end = (XmlElement)e_operation.GetElementsByTagName("end_date")[0];
                        int end_year = Int32.Parse(((XmlElement)e_end.GetElementsByTagName("year")[0]).InnerText);
                        int end_month = Int32.Parse(((XmlElement)e_end.GetElementsByTagName("month")[0]).InnerText);
                        int end_day = Int32.Parse(((XmlElement)e_end.GetElementsByTagName("day")[0]).InnerText);
                        DateTime end_date = new DateTime(end_year, end_month, end_day);
                        string source = ((XmlElement)e_operation.GetElementsByTagName("source")[0]).InnerText;
                        string database = ((XmlElement)e_operation.GetElementsByTagName("database")[0]).InnerText;
                        string table = ((XmlElement)e_operation.GetElementsByTagName("table")[0]).InnerText;
                        XmlNodeList column_list = ((XmlElement)e_operation.GetElementsByTagName("columns")[0]).GetElementsByTagName("column");
                        string[] columns = new string[column_list.Count];
                        for (int j = 0; j < column_list.Count; j++)
                            columns[j] = ((XmlElement)column_list[j]).InnerText;
                        op = new OPERATION1(fields, tickers_file, start_date, end_date, sources[source], databases[database], table, columns);
                        break;
                }
            }
            return result;
        }
    }
}
