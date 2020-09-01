using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace MapTool
{
    class Tile
    {
        public MyTransform transform;
        public string key;
        public TableIndex offset;
        public TableIndex index;
        public const int Width = 160;
        public const int Height = 80;
        public const int WidthHalf = 80;
        public const int HeightHalf = 40;

        public Tile()
        {
            transform = new MyTransform();
            key = string.Empty;
            offset = new TableIndex(0,0);
        }
        public void Render()
        {
            RenderManager.DrawSprite(key, transform, offset);
        }

        public void Render(float ratio)
        {
            RenderManager.DrawSprite(key, transform, offset, ratio);
        }
    }
}
