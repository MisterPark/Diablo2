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
    public enum DrawMode
    {
        Tile,
        Move,
        Spawn,
        Object,
    }

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
        public static SpriteType selectedTileSet = SpriteType.ACT1_TOWN_FLOOR;
        public static int selectedOffset = 0;
        DrawMode mode = DrawMode.Tile;

        //==============================
        // 생성자
        //==============================
        public Form1()
        {
            InitializeComponent();
            g_mainPanel = mainPanel;
            g_updown = numericUpDown1;
            numericUpDown1.Increment = 1m / SystemInformation.MouseWheelScrollLines;// 휠이 3개씩 올라서 증분함

            comboBox2.Items.Add("타일");
            comboBox2.SelectedItem = "타일";
            comboBox2.Items.Add("이동");
            comboBox2.Items.Add("스폰");
            comboBox2.Items.Add("오브젝트");

            openFileDialog1.Filter = "데이터파일|*.dat";

            RenderManager.Initialize(mainPanel);

            LoadTileSet("\\Sprites\\Tile\\Act1_Town_Floor.png", SpriteType.ACT1_TOWN_FLOOR, new TableIndex(37, 5));
            LoadTileSet("\\Sprites\\Tile\\Act1_Outdoor_Floor.png", SpriteType.ACT1_OUTDOOR_FLOOR, new TableIndex(25, 5));
            LoadTileSet("\\Sprites\\Tile\\Act1_Town_Fence.png", SpriteType.ACT1_TOWN_FENCE, new TableIndex(1, 31));


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
            TableIndex moveIndex = TileManager.MouseToMoveableTileIndex(g_mainPanel);
            screenPosLabel.Text = Cursor.Position.ToString();
            panelPosLabel.Text = GetPositionToMainPanel().ToString();
            tileIndexLabel.Text =index.row.ToString() +", "+ index.col.ToString();
            label6.Text = moveIndex.row.ToString() + ", " + moveIndex.col.ToString();

            Input.Update();
            TileManager.Update();
            
            // 메인 패널 렌더링
            RenderManager.Clear();
            TileManager.Render();
            TileManager.RenderObject();
            TileManager.RenderMoveableTile();
            TileManager.RenderCrossLine();
            RenderSelecter();
            
            RenderManager.Present(mainPanel);
            // 미니맵 렌더링
            RenderManager.Clear();
            TileManager.Render(miniRatio);
            TileManager.RenderObject(miniRatio);
            RenderManager.Present(miniPanel);
            // 타일 선택창 렌더
            RenderManager.Clear();
            TileManager.RenderSelectedTile(selectedTileSet, selectedOffset, tilePanel.Width, tilePanel.Height);
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

        private void LoadTileSet(string path, SpriteType key, TableIndex range)
        {
            RenderManager.LoadSprite(path, key, range);
            comboBox1.Items.Add(key);

            comboBox1.SelectedIndex = 0;
            
        }

        private void CreateTile()
        {
            SpriteImage img = RenderManager.GetSpriteImage(selectedTileSet);
            if (img == null) return;
            TableIndex offset = new TableIndex(selectedOffset / img.range.col, selectedOffset % img.range.col);
            TileManager.CreateTile(selectedTileSet, TileManager.MouseToTileIndex(mainPanel), offset);
        }

        private void CreateObject()
        {
            SpriteImage img = RenderManager.GetSpriteImage(selectedTileSet);
            if (img == null) return;
            TableIndex offset = new TableIndex(selectedOffset / img.range.col, selectedOffset % img.range.col);
            TileManager.CreateObject(selectedTileSet, TileManager.MouseToTileIndex(mainPanel), offset);
        }

        private void RenderSelecter()
        {
            switch (mode)
            {
                case DrawMode.Tile:
                    TileManager.RenderSelector(mainPanel);
                    break;
                case DrawMode.Move:
                    TileManager.RenderMoveableTileSelector(mainPanel);
                    break;
                case DrawMode.Spawn:
                    TileManager.RenderSelector(mainPanel);
                    break;
                case DrawMode.Object:
                    TileManager.RenderSelector(mainPanel);
                    break;
                default:
                    break;
            }
        }

        private void LButton()
        {
            switch (mode)
            {
                case DrawMode.Tile:
                    CreateTile();
                    break;
                case DrawMode.Move:
                    TileManager.CreateMoveableTile(TileManager.MouseToMoveableTileIndex(mainPanel));
                    break;
                case DrawMode.Spawn:
                    break;
                case DrawMode.Object:
                    CreateObject();
                    break;
                default:
                    break;
            }
        }

        private void RButton()
        {
            switch (mode)
            {
                case DrawMode.Tile:
                    TileManager.DeleteTile(TileManager.MouseToTileIndex(mainPanel));
                    break;
                case DrawMode.Move:
                    TileManager.DeleteMoveableTile(TileManager.MouseToMoveableTileIndex(mainPanel));
                    break;
                case DrawMode.Spawn:
                    break;
                case DrawMode.Object:
                    TileManager.DeleteObject(TileManager.MouseToTileIndex(mainPanel));
                    break;
                default:
                    break;
            }
        }


        //==============================
        // 이벤트
        //==============================

        private void mainPanel_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    LButton();
                    isLButtonDown = true;
                    break;
                case MouseButtons.None:
                    break;
                case MouseButtons.Right:
                    RButton();
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
                LButton();
            }
            else if(isRButtonDown)
            {
                RButton();
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

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            SpriteType key = (SpriteType)comboBox1.SelectedIndex + 1;
            SpriteImage img = RenderManager.GetSpriteImage(key);
            if (img == null) return;

            SetSelectionRange(img.range.row * img.range.col);
            selectedTileSet = key;
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string select = comboBox2.SelectedItem.ToString();

            if(select == "타일")
            {
                mode = DrawMode.Tile;
            }
            else if (select == "이동")
            {
                mode = DrawMode.Move;
            }
            else if (select == "스폰")
            {
                mode = DrawMode.Spawn;
            }
            else if(select == "오브젝트")
            {
                mode = DrawMode.Object;
            }
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            TileManager.Save(textBox1.Text);
        }

        private void loadButton_Click(object sender, EventArgs e)
        {
            TileManager.Load(textBox1.Text);
        }

        private void openFileButton_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;
            }
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
