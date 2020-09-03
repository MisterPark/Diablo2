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

        public MyTransform transform;
        public SpriteType key;
        public TableIndex offset;
        public TableIndex index;
        public int isMoveable = 1;

        

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

            float sx = transform.position.X + (Tile.WidthHalf / 2) - Camera.X;
            float sy = transform.position.Y + (Tile.HeightHalf / 2) - Camera.Y;
            float ex = transform.position.X + (Tile.WidthHalf / 2) + Tile.WidthHalf - Camera.X;
            float ey = transform.position.Y + (Tile.HeightHalf / 2) + Tile.HeightHalf - Camera.Y;
            float sx2 = transform.position.X + Tile.WidthHalf + (Tile.WidthHalf / 2) - Camera.X;
            float sy2 = transform.position.Y + (Tile.HeightHalf / 2) - Camera.Y;
            float ex2 = transform.position.X + (Tile.WidthHalf / 2) - Camera.X;
            float ey2 = transform.position.Y + (Tile.HeightHalf / 2) + Tile.HeightHalf - Camera.Y;
            Color color = (isMoveable == 1) ? Color.Green : Color.Red;
            RenderManager.DrawLine(sx, sy, ex, ey, color);
            RenderManager.DrawLine(sx2, sy2, ex2, ey2, color);
        }

        public void Render(float ratio)
        {
            RenderManager.DrawSprite(key, transform, offset, ratio);
        }
    }
}
