namespace CliClient
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.menuStripTrdClient = new System.Windows.Forms.MenuStrip();
            this.ToolStripMenuItemHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.labelStatus = new System.Windows.Forms.Label();
            this.listViewMsgs = new System.Windows.Forms.ListView();
            this.Message = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Time = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.URL = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.CheckDetail = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.MarkAsRead = new System.Windows.Forms.ToolStripMenuItem();
            this.MarkAsUnRead = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.Delete = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.ctxTrayIcon = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ExitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timerIconFlash = new System.Windows.Forms.Timer(this.components);
            this.timerHeatbeat = new System.Windows.Forms.Timer(this.components);
            this.timer_ShowTrayMsg = new System.Windows.Forms.Timer(this.components);
            this.menuStripTrdClient.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.ctxTrayIcon.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStripTrdClient
            // 
            this.menuStripTrdClient.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStripTrdClient.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemHelp});
            this.menuStripTrdClient.Location = new System.Drawing.Point(0, 0);
            this.menuStripTrdClient.Name = "menuStripTrdClient";
            this.menuStripTrdClient.Size = new System.Drawing.Size(649, 24);
            this.menuStripTrdClient.TabIndex = 0;
            this.menuStripTrdClient.Text = "menuStripTrdClient";
            // 
            // ToolStripMenuItemHelp
            // 
            this.ToolStripMenuItemHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemAbout});
            this.ToolStripMenuItemHelp.Name = "ToolStripMenuItemHelp";
            this.ToolStripMenuItemHelp.Size = new System.Drawing.Size(45, 20);
            this.ToolStripMenuItemHelp.Text = "帮助";
            // 
            // ToolStripMenuItemAbout
            // 
            this.ToolStripMenuItemAbout.Name = "ToolStripMenuItemAbout";
            this.ToolStripMenuItemAbout.Size = new System.Drawing.Size(98, 22);
            this.ToolStripMenuItemAbout.Text = "关于";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(12, 394);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(110, 13);
            this.labelStatus.TabIndex = 2;
            this.labelStatus.Text = "Not connect to server";
            // 
            // listViewMsgs
            // 
            this.listViewMsgs.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Message,
            this.Time,
            this.URL});
            this.listViewMsgs.ContextMenuStrip = this.contextMenuStrip1;
            this.listViewMsgs.FullRowSelect = true;
            this.listViewMsgs.GridLines = true;
            this.listViewMsgs.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listViewMsgs.Location = new System.Drawing.Point(12, 44);
            this.listViewMsgs.Name = "listViewMsgs";
            this.listViewMsgs.Size = new System.Drawing.Size(616, 334);
            this.listViewMsgs.SmallImageList = this.imageList1;
            this.listViewMsgs.TabIndex = 3;
            this.listViewMsgs.UseCompatibleStateImageBehavior = false;
            this.listViewMsgs.View = System.Windows.Forms.View.Details;
            this.listViewMsgs.DoubleClick += new System.EventHandler(this.ListViewMsgs_DoubleClick);
            // 
            // Message
            // 
            this.Message.Text = "标题";
            this.Message.Width = 300;
            // 
            // Time
            // 
            this.Time.Text = "更新时间";
            this.Time.Width = 130;
            // 
            // URL
            // 
            this.URL.Text = "来源";
            this.URL.Width = 180;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CheckDetail,
            this.toolStripMenuItem1,
            this.MarkAsRead,
            this.MarkAsUnRead,
            this.toolStripMenuItem2,
            this.Delete});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(140, 104);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.ContextMenuStrip1_Opening);
            // 
            // CheckDetail
            // 
            this.CheckDetail.Image = ((System.Drawing.Image)(resources.GetObject("CheckDetail.Image")));
            this.CheckDetail.Name = "CheckDetail";
            this.CheckDetail.Size = new System.Drawing.Size(139, 22);
            this.CheckDetail.Text = "查看";
            this.CheckDetail.Click += new System.EventHandler(this.CheckDetail_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(136, 6);
            // 
            // MarkAsRead
            // 
            this.MarkAsRead.Image = ((System.Drawing.Image)(resources.GetObject("MarkAsRead.Image")));
            this.MarkAsRead.Name = "MarkAsRead";
            this.MarkAsRead.Size = new System.Drawing.Size(139, 22);
            this.MarkAsRead.Text = "标记为已读";
            this.MarkAsRead.Click += new System.EventHandler(this.MarkAsRead_Click);
            // 
            // MarkAsUnRead
            // 
            this.MarkAsUnRead.Image = ((System.Drawing.Image)(resources.GetObject("MarkAsUnRead.Image")));
            this.MarkAsUnRead.Name = "MarkAsUnRead";
            this.MarkAsUnRead.Size = new System.Drawing.Size(139, 22);
            this.MarkAsUnRead.Text = "标记为未读";
            this.MarkAsUnRead.Click += new System.EventHandler(this.MarkAsUnRead_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(136, 6);
            // 
            // Delete
            // 
            this.Delete.Image = ((System.Drawing.Image)(resources.GetObject("Delete.Image")));
            this.Delete.Name = "Delete";
            this.Delete.Size = new System.Drawing.Size(139, 22);
            this.Delete.Text = "删除";
            this.Delete.Click += new System.EventHandler(this.Delete_Click);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "message_32px.ico");
            this.imageList1.Images.SetKeyName(1, "message_32px.net.ico");
            this.imageList1.Images.SetKeyName(2, "message_32px_read.ico");
            this.imageList1.Images.SetKeyName(3, "message_32px_unread.ico");
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.notifyIcon1.BalloonTipTitle = "Message";
            this.notifyIcon1.ContextMenuStrip = this.ctxTrayIcon;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "通知消息";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.BalloonTipClicked += new System.EventHandler(this.NotifyIcon1_BalloonTipClicked);
            this.notifyIcon1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.NotifyIcon1_MouseClick);
            // 
            // ctxTrayIcon
            // 
            this.ctxTrayIcon.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ExitToolStripMenuItem});
            this.ctxTrayIcon.Name = "ctxTrayIcon";
            this.ctxTrayIcon.Size = new System.Drawing.Size(101, 26);
            // 
            // ExitToolStripMenuItem
            // 
            this.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem";
            this.ExitToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.ExitToolStripMenuItem.Text = "退出";
            this.ExitToolStripMenuItem.Click += new System.EventHandler(this.ExitToolStripMenuItem_Click);
            // 
            // timerIconFlash
            // 
            this.timerIconFlash.Interval = 1000;
            this.timerIconFlash.Tick += new System.EventHandler(this.TimerIconFlash_Tick);
            // 
            // timerHeatbeat
            // 
            this.timerHeatbeat.Interval = 3000;
            this.timerHeatbeat.Tick += new System.EventHandler(this.TimerHeatbeat_Tick);
            // 
            // timer_ShowTrayMsg
            // 
            this.timer_ShowTrayMsg.Interval = 1000;
            this.timer_ShowTrayMsg.Tick += new System.EventHandler(this.Timer_ShowTrayMsg_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(649, 425);
            this.Controls.Add(this.listViewMsgs);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.menuStripTrdClient);
            this.ForeColor = System.Drawing.Color.Black;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStripTrdClient;
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "通知窗口";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.SizeChanged += new System.EventHandler(this.FormMain_SizeChanged);
            this.menuStripTrdClient.ResumeLayout(false);
            this.menuStripTrdClient.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ctxTrayIcon.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStripTrdClient;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemHelp;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemAbout;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.ListView listViewMsgs;
        private System.Windows.Forms.ColumnHeader Message;
        private System.Windows.Forms.ColumnHeader URL;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.Timer timerIconFlash;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ColumnHeader Time;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem CheckDetail;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem MarkAsRead;
        private System.Windows.Forms.ToolStripMenuItem MarkAsUnRead;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem Delete;
        private System.Windows.Forms.ContextMenuStrip ctxTrayIcon;
        private System.Windows.Forms.ToolStripMenuItem ExitToolStripMenuItem;
        private System.Windows.Forms.Timer timerHeatbeat;
        private System.Windows.Forms.Timer timer_ShowTrayMsg;
    }
}

