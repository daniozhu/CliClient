using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using CliApiCS;
using Newtonsoft.Json.Linq;

namespace CliClient
{
    public partial class FormMain : Form
    {
        private readonly int MSG_ICON_READ = 2;
        private readonly int MSG_ICON_UNREAD = 3;

        //private readonly int COLUMN_TITLE = 0;
        private readonly int COLUMN_TIME = 1;
        private readonly int COLUMN_URL = 2;

        private readonly int MAX_HEARTBEAT_LOST = 10;

        private Icon TrayNormalIcon { get; set; }
        private Icon TrayNewMsgIcon { get; set; }
        public int HeartBeatLostTime { get; set; }

        private int MAX_MSGS { get; set; }
        public int MAX_MSG_DISPLAY_TIME { get; private set; }

        private TrayMsgController TrayMsgControl { get; set; }

        public FormMain()
        {
            InitializeComponent();

            MAX_MSGS = Int32.Parse(System.Configuration.ConfigurationManager.AppSettings["show_items"]);
            MAX_MSG_DISPLAY_TIME = 60 * Int32.Parse(System.Configuration.ConfigurationManager.AppSettings["msg_display_duration"]);

            TrayMsgControl = new TrayMsgController(this);
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            CurrentTrayIcon = 0;

            TrayNormalIcon = Icon.FromHandle(((Bitmap)imageList1.Images[0]).GetHicon());
            TrayNewMsgIcon = Icon.FromHandle(((Bitmap)imageList1.Images[1]).GetHicon());

            timerHeatbeat.Enabled = true;
            timerHeatbeat.Start();

            timer_ShowTrayMsg.Enabled = true;
            timer_ShowTrayMsg.Start();
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                this.Hide();
                this.notifyIcon1.Visible = true;
            }   
        }

        private void TimerHeatbeat_Tick(object sender, EventArgs e)
        {
            if (++HeartBeatLostTime > MAX_HEARTBEAT_LOST)
            {
                //SetStatus("服务器已断开");
                HeartBeatLostTime = MAX_HEARTBEAT_LOST;
            }
            
            CliApi.SendMsg("#{ping};");
        }
        public void SetStatus(string status)
        {
            if(this.InvokeRequired)
            {
                this.BeginInvoke(new DlgtVoidInputString(SetStatus), status);
            }
            else
            {
                labelStatus.Text = status;
            }
        }

        private void InsertNewMsg(NtfMsgInfo ntfMsgInfo)
        {
            if (listViewMsgs.Items.Count + 1 > MAX_MSGS)
            {
                listViewMsgs.Items.RemoveAt(listViewMsgs.Items.Count -1);
            }

            ListViewItem listItem = new ListViewItem(ntfMsgInfo.TitleInfo, MSG_ICON_UNREAD);
            listItem.SubItems.Add(ntfMsgInfo.TimeInfo);
            listItem.SubItems.Add(ntfMsgInfo.LinkInfo);

            // Later msg always shows in the first.
            listViewMsgs.Items.Insert(0, listItem);

            // Update latest msg which will be opened when click on the ballontip.
            LatestMsg = ntfMsgInfo;
        }

        NtfMsgInfo LatestMsg { get; set; }
        public void OnNotifyMsgNtf(String strNotifyMsg)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new DlgtVoidInputString(OnNotifyMsgNtf), strNotifyMsg);
            }
            else
            {
                string[] msgs = strNotifyMsg.Split(new Char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
                foreach (string msg in msgs)
                {
                    string jsonMsg = GlobalMgr.TrimStartString(msg, "#", "");

                    if (jsonMsg.ToLower() == "{ping}")
                    {
                        //if(HeartBeatLostTime >= MAX_HEARTBEAT_LOST)
                            //SetStatus("服务器已连接");

                        // We get feedback, reset the heart beat lost count to 0.
                        HeartBeatLostTime = 0;
                        continue;
                    }

                    try
                    {
                        JObject jo = JObject.Parse(jsonMsg);
                        if (jo == null)
                            return;

                        NtfMsgInfo ntfMsgInfo = new NtfMsgInfo();

                        ntfMsgInfo.TitleInfo = jo["title"].ToString();
                        ntfMsgInfo.LinkInfo = jo["link"].ToString();
                        ntfMsgInfo.TimeInfo = DateTime.Now.ToString(TimeConverter.Format, TimeConverter.CultureInfo);

                        InsertNewMsg(ntfMsgInfo);

                       TrayMsgControl.AddToTrayMsgQueue(ntfMsgInfo);
                     //   notifyIcon1.ShowBalloonTip(5000, ntfMsgInfo.TimeInfo, ntfMsgInfo.TitleInfo, ToolTipIcon.Info);

                        if (this.WindowState == FormWindowState.Minimized)
                        {
                            // Enable icon flash on Tray.
                            TrayIconFlash(true);
                        }
                    }
                    catch
                    {
                        continue;
                    }
                }
            }
        }

        public delegate void DlgtVoidInputString(string str);

        private void ListViewMsgs_DoubleClick(object sender, EventArgs e)
        {
            if (listViewMsgs.SelectedItems.Count > 0)
            {
                try
                {
                    ListViewItem selectedItem = listViewMsgs.SelectedItems[0];
                    OpenMsgItem(selectedItem);
                }
                catch
                {
                    // Fail to open the link, don't change status of the message.
                }
            }
        }

        private void FormMain_SizeChanged(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                this.notifyIcon1.Visible = true;
            }
        }

        int CurrentTrayIcon { get; set; }

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern bool MessageBeep(uint uType);

        private void TimerIconFlash_Tick(object sender, EventArgs e)
        {
            if (CurrentTrayIcon == 0)
            {
                notifyIcon1.Icon = TrayNewMsgIcon;
                CurrentTrayIcon = 1;
            }
            else
            {
                notifyIcon1.Icon = TrayNormalIcon;
                CurrentTrayIcon = 0;
            }
        }

        private void NotifyIcon1_BalloonTipClicked(object sender, EventArgs e)
        {
            NtfMsgInfo msg = LatestMsg;
            if(msg != null)
            {
                System.Diagnostics.Process.Start(msg.LinkInfo);
                TrayIconFlash(false);

                // Mark it as read
                MarkMsgAsRead(msg);
            }
        }

        private void TrayIconFlash(bool bEnable)
        {
            if (bEnable)
            {
                timerIconFlash.Enabled = true;
                timerIconFlash.Start();
            }
            else
            {
                timerIconFlash.Stop();

                // Reset to normal tray icon.
                notifyIcon1.Icon = TrayNormalIcon;
            }
        }

        public void MarkMsgAsRead(NtfMsgInfo msg)
        {
            foreach(ListViewItem item in listViewMsgs.Items)
            {
                if(item.SubItems[COLUMN_TIME].Text == msg.TimeInfo)
                {
                    item.ImageIndex = MSG_ICON_READ;
                    return;
                }
            }
        }

        private void OpenMsgItem(ListViewItem item)
        {
            string url = item.SubItems[COLUMN_URL].Text;
            System.Diagnostics.Process.Start(url);

            // Change icon as read.
            item.ImageIndex = MSG_ICON_READ;
        }

        private void ContextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            if (listViewMsgs.SelectedItems.Count == 0)
                e.Cancel = true;

            // If select items more than 1, disable "CheckDetail" sub menu.
            bool bEnableCheckDetail = listViewMsgs.SelectedItems.Count == 1;
            contextMenuStrip1.Items[0].Enabled = bEnableCheckDetail;
        }

        // Event handler for context menu in ListView control
        //
        private void CheckDetail_Click(object sender, EventArgs e)
        {
            if (listViewMsgs.SelectedItems.Count == 0)
                return;

            OpenMsgItem(listViewMsgs.SelectedItems[0]);
        }

        private void MarkAsRead_Click(object sender, EventArgs e)
        {
            foreach(ListViewItem item in listViewMsgs.SelectedItems)
            {
                item.ImageIndex = MSG_ICON_READ;
            }
        }

        private void MarkAsUnRead_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in listViewMsgs.SelectedItems)
            {
                item.ImageIndex = MSG_ICON_UNREAD;
            }
        }

        private void Delete_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in listViewMsgs.SelectedItems)
            {
                listViewMsgs.Items.Remove(item);
            }
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timerHeatbeat.Stop();
            timerIconFlash.Stop();
            timer_ShowTrayMsg.Stop();

            Application.Exit();
        }

        private void NotifyIcon1_MouseClick(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
            {
                this.Visible = true;
                this.WindowState = FormWindowState.Normal;
                //   this.notifyIcon1.Visible = false;
                this.BringToFront();

                TrayIconFlash(false);
            }
        }

        private void Timer_ShowTrayMsg_Tick(object sender, EventArgs e)
        {
            TrayMsgControl.ShowTrayMsg();
        }
    }
}
