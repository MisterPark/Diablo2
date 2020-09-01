using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Runtime.InteropServices;



namespace MapTool
{
    
    public partial class Form1 : Form
    {
        
        //==============================
        // 멤버
        //==============================
        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        public static Panel g_mainPanel = null;
        static NumericUpDown g_updown = null;
        bool isLButtonDown = false;
        bool isRButtonDown = false;
        float miniRatio = 1.0f;
        public static string selectedTileSet = "ACT1_TOWN_FLOOR";
        public static int selectedOffset = 0;

        //==============================
        // 생성자
        //==============================
        public Form1()
        {
            InitializeComponent();
            g_mainPanel = mainPanel;
            g_updown = numericUpDown1;
            numericUpDown1.Increment = 1m / SystemInformation.MouseWheelScrollLines;// 휠이 3개씩 올라서 증분함

            RenderManager.Initialize(mainPanel);
            RenderManager.LoadSprite("\\Sprites\\Tile\\Act1_Town_Floor.png", "ACT1_TOWN_FLOOR", new TableIndex(37, 5));

            SetSelectionRange(37 * 5); // 나중에 이거 지우고 타일셋 셀렉션 만들면 거기에서 넣어줄것.

            timer.Interval = 20;
            timer.Tick += new EventHandler(Loop); //주기마다 실행되는 이벤트 등록
            timer.Start();

        }

        //==============================
        // 메소드
        //==============================
        public void Loop(object sender, EventArgs e)
        {
            // 좌표정보 출력
            TableIndex index = TileManager.MouseToTileIndex(g_mainPanel);
            screenPosLabel.Text = Cursor.Position.ToString();
            panelPosLabel.Text = GetPositionToMainPanel().ToString();
            tileIndexLabel.Text =index.row.ToString() +", "+ index.col.ToString();

            Input.Update();
            
            // 메인 패널 렌더링
            RenderManager.Clear();
            TileManager.RenderCrossLine();
            TileManager.Render();
            TileManager.RenderSelector(mainPanel);
            RenderManager.Present(mainPanel);
            // 미니맵 렌더링
            RenderManager.Clear();
            TileManager.Render(miniRatio);
            RenderManager.Present(miniPanel);
            // 타일 선택창 렌더
            RenderManager.Clear();
            TileManager.RenderSelectedTile(selectedTileSet, selectedOffset);
            RenderManager.Present(tilePanel);

        }

        public static int GetMainPanelWidth()
        {
            if (g_mainPanel == null) return 0;

            return g_mainPanel.Width;
        }

        public static int GetMainPanelHeight()
        {
            if (g_mainPanel == null) return 0;

            return g_mainPanel.Height;
        }

        public static Point GetPositionToMainPanel()
        {
            return g_mainPanel.PointToClient(Cursor.Position);
        }

        public static void SetSelectionRange(int max)
        {
            g_updown.Maximum = max;
            g_updown.Value = 0;
        }


        //==============================
        // 이벤트
        //==============================
        private void Form1_Load(object sender, EventArgs e)
        {
            
        }



        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.A) // Left
            {
                Camera.X -= 10;
            }
            else if(e.KeyCode == Keys.D) // Right
            {
                Camera.X += 10;
            }
            else if (e.KeyCode == Keys.W) // Up
            {
                Camera.Y -= 10;
            }
            else if (e.KeyCode == Keys.S) // Down
            {
                Camera.Y += 10;
            }
            else if(e.KeyCode == Keys.Q)
            {
                Camera.X = 0;
                Camera.Y = 0;
            }

           
        }


        private void mainPanel_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    TileManager.CreateTile();
                    isLButtonDown = true;
                    break;
                case MouseButtons.None:
                    break;
                case MouseButtons.Right:
                    TileManager.DeleteTile(TileManager.MouseToTileIndex(mainPanel));
                    isRButtonDown = true;
                    break;
                case MouseButtons.Middle:
                    break;
                case MouseButtons.XButton1:
                    break;
                case MouseButtons.XButton2:
                    break;
                default:
                    break;
            }

            
        }

        private void mainPanel_MouseMove(object sender, MouseEventArgs e)
        {
            if(isLButtonDown)
            {
                TileManager.CreateTile();
            }
            else if(isRButtonDown)
            {
                TileManager.DeleteTile(TileManager.MouseToTileIndex(mainPanel));
            }
        }

        private void mainPanel_MouseUp(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    isLButtonDown = false;
                    break;
                case MouseButtons.None:
                    break;
                case MouseButtons.Right:
                    isRButtonDown = false;
                    break;
                case MouseButtons.Middle:
                    break;
                case MouseButtons.XButton1:
                    break;
                case MouseButtons.XButton2:
                    break;
                default:
                    break;
            }
        }

        private void miniTrackBar_ValueChanged(object sender, EventArgs e)
        {
            miniRatio = 1.0f / (miniTrackBar.Value);
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            selectedOffset = (int)numericUpDown1.Value;
        }

        // 뉴메릭업다운 휠이 3개씩 증가해서 찾은건데 수정해야할듯
        //private void numericUpDown1_MouseWheel(object sender, MouseEventArgs e)
        //{
        //    decimal newValue = numericUpDown1.Value;
        //    if (e.Delta > 0) 
        //        newValue += SystemInformation.MouseWheelScrollLines;
        //    else 
        //        newValue -= SystemInformation.MouseWheelScrollLines;

        //    if (newValue > numericUpDown1.Maximum) 
        //        newValue = numericUpDown1.Maximum;
        //    else if (newValue < numericUpDown1.Minimum) 
        //        newValue = numericUpDown1.Minimum;
        //    numericUpDown1.Value = newValue;
        //}
    }
}
