using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CliClient
{
    public partial class TrayMsgForm : Form
    {
        private int MaxDisplayTime { get; set; }
        private int CurrentDisplayTime { get; set; } // seconds
        public NtfMsgInfo Msg { get; private set; }
        private TrayMsgController MsgController { get; set; }

        //public TrayMsgForm()
        //{
        //    InitializeComponent();
        //}

        public TrayMsgForm(int maxDuration, NtfMsgInfo msgInfo, TrayMsgController controller)
        {
            InitializeComponent();

            MaxDisplayTime = maxDuration;
            Msg = msgInfo;

            CurrentDisplayTime = 0;

            MsgController = controller;
        }

        private void TrayMsgForm_Shown(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            timer1.Start();

            label_time.Text = Msg.TimeInfo;
            label_title.Text = Msg.TitleInfo;
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            if (++CurrentDisplayTime >= MaxDisplayTime)
            {
                CloseForm();
            }
        }


        private void BtnCheckDetail_Click(object sender, EventArgs e)
        {

        }

        public void CloseForm()
        {
            MsgController.RemoveTrayMsgForm(this);
            timer1.Stop();
            this.Close();
        }

        private void BtnCancel_Click(object sender, EventArgs e)
        {
            CloseForm();
        }

        private void CheckDetail()
        {
            System.Diagnostics.Process.Start(Msg.LinkInfo);
            MsgController.MarkMsgAsRead(Msg);

            CloseForm();
        }

        private void Label_title_Click(object sender, EventArgs e)
        {
            CheckDetail();
        }

        private void TrayMsgForm_Click(object sender, EventArgs e)
        {
            CheckDetail();
        }

        private void Label_time_Click(object sender, EventArgs e)
        {
            CheckDetail();
        }
    }
}
