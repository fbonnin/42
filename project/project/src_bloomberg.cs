using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bloomberglp.Blpapi;

namespace project
{
    class BLOOMBERG_ERROR : System.Exception
    {
    }

    class SRC_BLOOMBERG : SOURCE
    {
        Session session;
        Service service;

        public SRC_BLOOMBERG()
        {
            session = new Session();
            if (!session.Start() ||
                !session.OpenService("//blp/refdata") ||
                (service = session.GetService("//blp/refdata")) == null)
            {
                throw new BLOOMBERG_ERROR();
            }
        }
        ~SRC_BLOOMBERG()
        {
            session.Stop();
        }
    }
}
