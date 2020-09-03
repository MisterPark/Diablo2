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
            RenderManager.DrawSubTileSprite(key, transform, offset);
        }
    }
}
