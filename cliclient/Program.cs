using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace CliClient
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            if (!GlobalMgr.Init())
            {
                return;
            }

            Application.Run(GlobalMgr.s_formMain);
        }
    }
}
