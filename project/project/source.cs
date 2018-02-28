using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class SOURCE
    {
        string login;
        string password;

        public SOURCE(string login, string password)
        {
            this.login = login;
            this.password = password;
        }

        public abstract Object[][] Request1(string[] fields, string ticker, DateTime start_date, DateTime end_date);
    }
}
