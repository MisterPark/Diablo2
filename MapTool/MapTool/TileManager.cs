using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace MapTool
{
    class TileManager
    {
        private static TileManager instance = new TileManager();
        public Dictionary<TableIndex, Tile> tileMap = new Dictionary<TableIndex, Tile>();
        
        public static TileManager Instance
        {
            get { return instance; }
            private set { }
        }
        private TileManager()
        {
            
        }

        public static void Render()
        {
            foreach(KeyValuePair<TableIndex,Tile> pair in instance.tileMap)
            {
                pair.Value.Render();
            }
        }

        public static void RenderCrossLine()
        {
			int screenW = 1920;
			int screenH = Form1.GetMainPanelHeight();
			int w = screenW / Tile.WidthHalf + 1;
			int h = screenH / Tile.HeightHalf + 2;
			int offsetX = (int)Camera.X % Tile.WidthHalf;
			int offsetY = (int)Camera.Y % Tile.HeightHalf;
			int diagonalCount = w + h;

			// 대각선 /
			for (int cnt = -1; cnt < diagonalCount; cnt++)
			{
				int sx = (cnt * Tile.WidthHalf) - offsetX - (offsetY * 2);
				int ey = (cnt * Tile.HeightHalf) - offsetY - (offsetX / 2);

				RenderManager.DrawLine(sx, 0, 0, ey);
			}

			// 대각선 
			for (int cnt = -1; cnt < diagonalCount; cnt++)
			{
				int sx = screenW - (cnt * Tile.WidthHalf) - offsetX + (offsetY * 2);
				int ey = (cnt * Tile.HeightHalf) - offsetY + (offsetX / 2);

				RenderManager.DrawLine(sx, 0, screenW, ey);
			}
		}

        public static void RenderSelector(Control control)
        {

			float offsetX = Camera.X;
			float offsetY = Camera.Y;
			TableIndex idx = MouseToTileIndex(control);

			float sx = (idx.col * Tile.Width) + ((idx.row % 2) * (Tile.WidthHalf)) - offsetX;
			float sy = (idx.row * Tile.HeightHalf) - offsetY;

			RenderManager.DrawLine(sx, sy + Tile.HeightHalf, sx + Tile.WidthHalf, sy, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthHalf, sy, sx + Tile.Width, sy + Tile.HeightHalf, Color.Green);
			RenderManager.DrawLine(sx + Tile.Width, sy + Tile.HeightHalf, sx + Tile.WidthHalf, sy + Tile.Height, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthHalf, sy + Tile.Height, sx, sy + Tile.HeightHalf, Color.Green);


		}

		public static TableIndex MouseToTileIndex(Control control)
        {
			TableIndex idx;

			Vector3 tilePos = MouseToTilePosition(control);
			idx.row = (int)(tilePos.Y / Tile.HeightHalf);
			idx.col = (int)(tilePos.X / Tile.Width);

			return idx;
		}


		public static Vector3 MouseToTilePosition(Control control)
		{
			Vector3 res = new Vector3();
			Point pt = Cursor.Position;

			float worldX = (control.PointToClient(pt).X + Camera.X);
			float worldY = (control.PointToClient(pt).Y + Camera.Y);

			// y절편
			// b = -ax + y;
			int interceptDown = (int)(worldX * -0.5f + worldY - Tile.HeightHalf); // ↘
			int interceptUp = (int)(worldX * 0.5f + worldY - Tile.HeightHalf); // ↗
																	  // 대각선 라인 번호 
			int downNum = interceptDown / Tile.Height;
			int upNum = interceptUp / Tile.Height;

			if (interceptDown < 0) downNum--;
			if (interceptUp < 0) upNum--;

			// 대각라인 절편(딱떨어지는)
			downNum *= Tile.Height;
			upNum *= Tile.Height;

			// y = ax + b
			res.X = upNum - downNum;
			res.Y = (upNum - downNum) * 0.5f + downNum;

			// 보정 // 다이아몬드 위꼭지 => 직사각형 좌상단
			res.X -= Tile.WidthHalf;
			// 보정 // 첫타일 좌상단 0,0 기준으로 할때
			res.Y += Tile.HeightHalf;

			return res;
		}
	}
}
