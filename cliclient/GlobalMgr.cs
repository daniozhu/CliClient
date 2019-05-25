using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using CliApiCS;
using System.Windows.Forms;
using System.IO;
using Newtonsoft;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Net;

namespace CliClient
{
    public class GlobalMgr
    {
        public static bool Init()
        {
            s_formMain = new FormMain();

            String strExePath = System.IO.Directory.GetCurrentDirectory();

            String strDomain = ConfigurationManager.AppSettings["domain"];

            String strIPAddr = GetIP(strDomain);

            UInt16 wPort = UInt16.Parse(ConfigurationManager.AppSettings["port"]);

            CliApi.Init(strIPAddr, wPort);

            CliApi.SetDlgtOnConnected(OnConnected);
            CliApi.SetDlgtOnDisConnected(OnDisConnected);
            CliApi.SetDlgtOnErrorInfo(OnErrorInfo);
            CliApi.SetDlgtOnMsgCallBack(OnMsgCallBack);

            CliApi.SetDlgtOnNotifyMsgNtf(OnNotifyMsgNtf);
            CliApi.Start();

            return true;
        }

        public static String GetIP(String strDoMain)
        {
            strDoMain = strDoMain.Replace("http://", "").Replace("https://", "");
            IPHostEntry hostEntry = Dns.GetHostEntry(strDoMain);
            IPEndPoint ipEndPoint = new IPEndPoint(hostEntry.AddressList[0], 0);
            return ipEndPoint.Address.ToString();

        }

        public static void OnConnected()
        {
            s_formMain.SetStatus("服务器已连接");
        }

        public static void OnDisConnected()
        {
            s_formMain.SetStatus("服务器已断开");
        }

        public static void OnErrorInfo(int iModuleErr, int iSysErr)
        {
            //s_formMain.SetStatus("Serever error.");
        }

        public static void OnMsgCallBack(String strMsg)
        {
           //if(strMsg.ToLower() == "#{ping};")
           // {
           //     s_formMain.HeartBeatLostTime = 0;
           //     s_formMain.SetStatus("服务器已连接");
           // }
        }

        public static void OnNotifyMsgNtf(String strNotfiMsg)
        {
            s_formMain.OnNotifyMsgNtf(strNotfiMsg);
        }

        /// <summary>
        /// 替换字符串起始位置(开头)中指定的字符串
        /// </summary>
        /// <param name="s">源串</param>
        /// <param name="searchStr">查找的串</param>
        /// <param name="replaceStr">替换的目标串</param>
        /// <returns></returns>
        public static string TrimStartString(string s, string searchStr, string replaceStr)
        {
            var result = s;
            try
            {
                if (string.IsNullOrEmpty(result))
                {
                    return result;
                }
                if (s.Length < searchStr.Length)
                {
                    return result;
                }
                if (s.IndexOf(searchStr, 0, searchStr.Length, StringComparison.Ordinal) > -1)
                {
                    result = s.Substring(searchStr.Length);
                }
                return result;
            }
            catch (Exception e)
            {
                return result;
            }
        }

        /// <summary>
        /// 替换字符串末尾位置中指定的字符串
        /// </summary>
        /// <param name="s">源串</param>
        /// <param name="searchStr">查找的串</param>
        /// <param name="replaceStr">替换的目标串</param>
        public static string TrimEndString(string s, string searchStr, string replaceStr)
        {
            var result = s;
            try
            {
                if (string.IsNullOrEmpty(result))
                {
                    return result;
                }
                if (s.Length < searchStr.Length)
                {
                    return result;
                }
                if (s.IndexOf(searchStr, s.Length - searchStr.Length, searchStr.Length, StringComparison.Ordinal) > -1)
                {
                    result = s.Substring(0, s.Length - searchStr.Length);
                }
                return result;
            }
            catch (Exception e)
            {
                return result;
            }
        }

        public static string Utf8ConvertTo(String utf8String)
        {
            // Create two different encodings.
            Encoding utf8 = Encoding.UTF8;
            Encoding defaultCode = Encoding.Default;

            // Convert the string into a byte[].
            byte[] utf8Bytes = defaultCode.GetBytes(utf8String);

            // Perform the conversion from one encoding to the other.
            byte[] defaultBytes = Encoding.Convert(utf8, defaultCode, utf8Bytes);

            // Convert the new byte[] into a char[] and then into a string.
            // This is a slightly different approach to converting to illustrate
            // the use of GetCharCount/GetChars.
            char[] defaultChars = new char[defaultCode.GetCharCount(defaultBytes, 0, defaultBytes.Length)];
            defaultCode.GetChars(defaultBytes, 0, defaultBytes.Length, defaultChars, 0);
            string defaultString = new string(defaultChars);

            return defaultString;
        }

        public static FormMain s_formMain;
    }
}
