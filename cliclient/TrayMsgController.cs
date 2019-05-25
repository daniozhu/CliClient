using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Media;
using System.Threading;
using System.Globalization;

namespace CliClient
{

    class MsgFormComparer :  IComparer<TrayMsgForm>
    {
        public int Compare(TrayMsgForm a, TrayMsgForm b)
        {
            DateTime dateTimeA = DateTime.ParseExact(a.Msg.TimeInfo, TimeConverter.Format, TimeConverter.CultureInfo);

            DateTime dateTimeB =  DateTime.ParseExact(b.Msg.TimeInfo, TimeConverter.Format, TimeConverter.CultureInfo);

            return DateTime.Compare(dateTimeA, dateTimeB);
        }
    }
    public class TrayMsgController
    {
        private readonly int MaxMsgForm = 3;
        private List<TrayMsgForm> TrayMsgFormList = new List<TrayMsgForm>();
        private TrayMsgForm ActiveTrayMsgForm { get; set; }
        private int FormIndex { get; set; }
        private FormMain Host { get; set; }

        private SoundPlayer _player = new SoundPlayer();

        private Queue<NtfMsgInfo> MsgQueue = new Queue<NtfMsgInfo>();

        private System.Threading.Thread SoundThread { get; set; }

        public TrayMsgController(FormMain host)
        {
            Host = host;
       //     TrayMsgFormList = new TrayMsgForm[MaxMsgForm];
            FormIndex = 0;
            ActiveTrayMsgForm = null;

           string sound_file = System.Configuration.ConfigurationManager.AppSettings["sound_file"];
            sound_file = System.IO.Path.Combine(System.IO.Directory.GetCurrentDirectory(), sound_file);

            _player.SoundLocation = sound_file;
            _player.Load();

            SoundThread = new Thread(new ThreadStart(_player.PlaySync));
        }

        public void AddToTrayMsgQueue(NtfMsgInfo msgInfo)
        {
            if(MsgQueue.Count == MaxMsgForm)
            {
                MsgQueue.Dequeue();
            }
            MsgQueue.Enqueue(msgInfo);
        }
        public void ShowTrayMsg()
        {
            if (MsgQueue.Count == 0)
                return;

            NtfMsgInfo msgInfo = MsgQueue.Dequeue();

            if(TrayMsgFormList.Count == MaxMsgForm)
            {
                TrayMsgForm formToRemove = TrayMsgFormList.First();
                formToRemove.CloseForm();
            }

            TrayMsgForm newForm = new TrayMsgForm(Host.MAX_MSG_DISPLAY_TIME, msgInfo, this);
            TrayMsgFormList.Insert(0, newForm);
            
            UpdateFormsPosition();
            newForm.Show();

            PlaySound();
        }

        public void MarkMsgAsRead(NtfMsgInfo msg)
        {
            Host.MarkMsgAsRead(msg);
        }

        public void RemoveTrayMsgForm(TrayMsgForm form)
        {
            TrayMsgFormList.Remove(form);
            UpdateFormsPosition();
        }
        
        private void UpdateFormsPosition()
        {
            if (TrayMsgFormList.Count == 0)
                return;

            // Sort forms by time.
            TrayMsgFormList.Sort(new MsgFormComparer());

            int Heightone = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height;
            int Heighttwo = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Height;
            int screenX = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width;

            int renwu = Heightone - Heighttwo;

            int frmHeigh = TrayMsgFormList[0].Height;

            int baseTop = Heightone - renwu - frmHeigh;
            int baseLeft = screenX - TrayMsgFormList[0].Width;

            int top = baseTop;
            int left = baseLeft;
            foreach (TrayMsgForm frm in TrayMsgFormList)
            {
                if (frm.Top != top)
                {
                    frm.Top = top;
                    frm.Left = left;
                }

                top -= frmHeigh + 2;
            }
        }
        private void PlaySound()
        {
            if(SoundThread.ThreadState == ThreadState.Unstarted)
            {
                SoundThread.Start();
            }
           else if( SoundThread.ThreadState == ThreadState.Running)
            {
                return;
            }
            else
            {
                SoundThread = new Thread(_player.PlaySync);
                SoundThread.Start();
            }
        }
    }
}
