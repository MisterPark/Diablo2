using System;
using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Drawing;

namespace MapTool
{
    class SubTile : Tile
    {
        public SubTile()
        {
            transform = new MyTransform();
            key = SpriteType.NONE;
            offset = new TableIndex(0, 0);
        }

        public new void Render()
        {
            if (transform.position.X < Camera.X - Tile.Width) return;
            if (transform.position.Y < Camera.Y - Tile.Height) return;
            if (transform.position.X > Camera.X + Form1.GetMainPanelWidth()) return;
            if (transform.position.Y > Camera.Y + Form1.GetMainPanelHeight()) return;

            RenderManager.DrawSubTileSprite(key, transform, offset);
        }
    }
}
