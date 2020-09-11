using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace MapTool
{
    class Tile
    {
        public const int Width = 160;
        public const int Height = 80;
        public const int WidthHalf = 80;
        public const int HeightHalf = 40;
        public const int WidthQuarter = 40;
        public const int HeightQuarter = 20;

        public MyTransform transform;
        public SpriteType key;
        public TableIndex offset;
        public TableIndex index;

        

        public Tile()
        {
            transform = new MyTransform();
            key = SpriteType.NONE;
            offset = new TableIndex(0,0);
        }
        public void Render()
        {
            if (transform.position.X < Camera.X - Tile.Width) return;
            if (transform.position.Y < Camera.Y - Tile.Height) return;
            if (transform.position.X > Camera.X + Form1.GetMainPanelWidth()) return;
            if (transform.position.Y > Camera.Y + Form1.GetMainPanelHeight()) return;
            RenderManager.DrawSprite(key, transform, offset);

        }

        public void Render(float ratio)
        {
            RenderManager.DrawSprite(key, transform, offset, ratio);
        }
    }
}
