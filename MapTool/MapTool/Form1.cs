using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace MapTool
{
    public partial class Form1 : Form
    {
        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        static Panel g_mainPanel = null;
        static Splitter g_splitter = null;
        public Form1()
        {
            InitializeComponent();
            g_mainPanel = mainPanel;
            g_splitter = splitter2;

            RenderManager.Initialize(mainPanel);
            RenderManager.LoadSprite("\\Sprites\\Tile\\Act1_Town_Floor.png", "ACT1_TOWN_FLOOR", new TableIndex(37, 5));


            timer.Interval = 20;
            timer.Tick += new EventHandler(Loop); //주기마다 실행되는 이벤트 등록
            timer.Start();

        }

        public void Loop(object sender, EventArgs e)
        {
            // 좌표정보 출력
            TableIndex index = TileManager.MouseToTileIndex(g_mainPanel);
            screenPosLabel.Text = Cursor.Position.ToString();
            panelPosLabel.Text = GetPositionToMainPanel().ToString();
            tileIndexLabel.Text =index.row.ToString() +", "+ index.col.ToString();
            

            // 렌더링
            RenderManager.Clear();
            TileManager.RenderCrossLine();
            TileManager.RenderSelector(mainPanel);
            RenderManager.Present(mainPanel);
            RenderManager.Clear();
            TileManager.RenderCrossLine();
            TileManager.RenderSelector(mainPanel);
            RenderManager.Present(miniPanel);

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

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            RenderManager.Clear();
            TileManager.RenderCrossLine();
            TileManager.RenderSelector(mainPanel);
            RenderManager.Present(mainPanel);
        }

        private void miniPanel_Paint(object sender, PaintEventArgs e)
        {
            RenderManager.Clear();
            TileManager.RenderCrossLine();
            TileManager.RenderSelector(mainPanel);
            RenderManager.Present(miniPanel);
        }


        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.NumPad4) // Left
            {
                Camera.X-=10;
            }
            else if(e.KeyCode == Keys.NumPad6) // Right
            {
                Camera.X+=10;
            }
            else if (e.KeyCode == Keys.NumPad8) // Up
            {
                Camera.Y-=10;
            }
            else if (e.KeyCode == Keys.NumPad5) // Down
            {
                Camera.Y+=10;
            }
            else if(e.KeyCode == Keys.NumPad7)
            {
                Camera.X = 0;
                Camera.Y = 0;
            }

           
        }

        private void mainPanel_MouseMove(object sender, MouseEventArgs e)
        {
            
        }
    }
}
