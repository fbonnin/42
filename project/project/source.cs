﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project
{
    abstract class SOURCE
    {
        public abstract Object[][] Request1(string[] fields, string[] tickers, DateTime start_date, DateTime end_date, OPTION[] options);
    }
}
