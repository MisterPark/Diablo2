using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.IO;


namespace MapTool
{
    class TileManager
    {
        private static TileManager instance = new TileManager();
        public SortedDictionary<TableIndex, Tile> tileMap = new SortedDictionary<TableIndex, Tile>();
		public SortedDictionary<TableIndex, SubTile> subTileMap = new SortedDictionary<TableIndex, SubTile>();
		public SortedDictionary<TableIndex, TableIndex> wallMap = new SortedDictionary<TableIndex, TableIndex>();
		public string spriteKey = string.Empty;

        public static TileManager Instance
        {
            get { return instance; }
            private set { }
        }
        private TileManager()
        {
            
        }

		public static void Update()
        {
			
        }

        public static void Render()
        {
            foreach(KeyValuePair<TableIndex,Tile> pair in instance.tileMap)
            {
                pair.Value.Render();
            }
        }
		public static void Render(float ratio)
		{
			foreach (KeyValuePair<TableIndex, Tile> pair in instance.tileMap)
			{
				pair.Value.Render(ratio);
			}
		}

		public static void RenderObject()
        {
			foreach (var pair in instance.subTileMap)
			{
				pair.Value.Render();
			}
        }

		public static void RenderObject(float ratio)
        {
			foreach (var pair in instance.subTileMap)
			{
				pair.Value.Render(ratio);
			}
		}

		public static void RenderMoveableTile()
        {
			foreach(var wall in instance.wallMap)
            {
				TableIndex idx = wall.Key;
				Vector3 vec = MoveableTileIndexToWorld(idx);

				float x = vec.X - Camera.X;
				float y = vec.Y - Camera.Y;

				RenderManager.DrawLine(x, y + Tile.HeightQuarter, x + Tile.WidthHalf, y + Tile.HeightQuarter, Color.Red);
				RenderManager.DrawLine(x + Tile.WidthQuarter, y, x + Tile.WidthQuarter, y + Tile.HeightHalf, Color.Red);
            }
        }

		public static void RenderSelectedTile(SpriteType key, int offset, int targetW, int targetH)
        {
			SpriteImage img = RenderManager.GetSpriteImage(key);
			if (img == null) return;

			TableIndex tableIndex = new TableIndex(offset / img.range.col, offset % img.range.col);
			MyTransform trans = new MyTransform();
			float wRatio = Form1.GetMainPanelWidth() / targetW;
			float hRatio = Form1.GetMainPanelHeight() / targetH;
			trans.scale.X = wRatio;
			trans.scale.Y = hRatio;

			RenderManager.DrawImage(key, trans, tableIndex);
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
			Vector3 vec = TileIndexToWorld(idx);

			float sx = vec.X - offsetX;
			float sy = vec.Y - offsetY;

			RenderManager.DrawLine(sx, sy + Tile.HeightHalf, sx + Tile.WidthHalf, sy, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthHalf, sy, sx + Tile.Width, sy + Tile.HeightHalf, Color.Green);
			RenderManager.DrawLine(sx + Tile.Width, sy + Tile.HeightHalf, sx + Tile.WidthHalf, sy + Tile.Height, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthHalf, sy + Tile.Height, sx, sy + Tile.HeightHalf, Color.Green);


		}

		public static void RenderMoveableTileSelector(Control control)
        {

			float offsetX = Camera.X;
			float offsetY = Camera.Y;
			TableIndex idx = MouseToMoveableTileIndex(control);
			Vector3 vec = MoveableTileIndexToWorld(idx);

			float sx = vec.X - offsetX;
			float sy = vec.Y - offsetY;

			RenderManager.DrawLine(sx, sy + Tile.HeightQuarter, sx + Tile.WidthQuarter, sy, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthQuarter, sy, sx + Tile.WidthHalf, sy + Tile.HeightQuarter, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthHalf, sy + Tile.HeightQuarter, sx + Tile.WidthQuarter, sy + Tile.HeightHalf, Color.Green);
			RenderManager.DrawLine(sx + Tile.WidthQuarter, sy + Tile.HeightHalf, sx, sy + Tile.HeightQuarter, Color.Green);

		}

		public static TableIndex MouseToTileIndex(Control control)
        {
			TableIndex idx = new TableIndex(0, 0);

			Vector3 tilePos = MouseToTilePosition(control);
			idx.row = (int)(tilePos.Y / Tile.HeightHalf);
			idx.col = (int)(tilePos.X / Tile.Width);

			return idx;
		}


		public static Vector3 MouseToTilePosition(Control control)
		{
			Vector3 tilePos = new Vector3();
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
			tilePos.X = upNum - downNum;
			tilePos.Y = (upNum - downNum) * 0.5f + downNum;

			// 보정 // 다이아몬드 위꼭지 => 직사각형 좌상단
			tilePos.X -= Tile.WidthHalf;
			// 보정 // 첫타일 좌상단 0,0 기준으로 할때
			tilePos.Y += Tile.HeightHalf;

			return tilePos;
		}

		public static Vector3 TileIndexToWorld(TableIndex index)
		{
			Vector3 v;
			v.X = (index.col* Tile.Width) + ((index.row % 2) * (Tile.WidthHalf));
			v.Y = index.row* Tile.HeightHalf;
			v.Z = 0;
			return v;
		}

		public static TableIndex MouseToMoveableTileIndex(Control control)
		{
			TableIndex idx = new TableIndex(0, 0);

			Vector3 tilePos = MouseToMoveableTilePosition(control);
			idx.row = (int)(tilePos.Y / Tile.HeightQuarter);
			idx.col = (int)(tilePos.X / Tile.WidthHalf);

			return idx;
		}


		public static Vector3 MouseToMoveableTilePosition(Control control)
		{
			Vector3 tilePos = new Vector3();
			Point pt = Cursor.Position;

			float worldX = (control.PointToClient(pt).X + Camera.X);
			float worldY = (control.PointToClient(pt).Y + Camera.Y);

			// y절편
			// b = -ax + y;
			int interceptDown = (int)(worldX * -0.5f + worldY ); // ↘
			int interceptUp = (int)(worldX * 0.5f + worldY ); // ↗
																			   // 대각선 라인 번호 
			int downNum = interceptDown / Tile.HeightHalf;
			int upNum = interceptUp / Tile.HeightHalf;

			if (interceptDown < 0) downNum--;
			if (interceptUp < 0) upNum--;

			// 대각라인 절편(딱떨어지는)
			downNum *= Tile.HeightHalf;
			upNum *= Tile.HeightHalf;

			// y = ax + b
			tilePos.X = upNum - downNum;
			tilePos.Y = (upNum - downNum) * 0.5f + downNum;

			//// 보정 // 다이아몬드 위꼭지 => 직사각형 좌상단
			tilePos.X -= Tile.WidthQuarter;
			//// 보정 // 첫타일 좌상단 0,0 기준으로 할때
			tilePos.Y += Tile.HeightQuarter;

			return tilePos;
		}

		public static Vector3 MoveableTileIndexToWorld(TableIndex index)
		{
			Vector3 v;
			v.X = (index.col * Tile.WidthHalf) + ((index.row % 2) * (Tile.WidthQuarter));
			v.Y = index.row * Tile.HeightQuarter - Tile.HeightQuarter;
			v.Z = 0;
			return v;
		}

		public static void CreateTile(SpriteType key, TableIndex worldIndex, TableIndex offset)
        {
			if (worldIndex.row < 0 || worldIndex.col < 0) return;

			Tile tile = null;
			if(instance.tileMap.TryGetValue(worldIndex, out tile))
            {
				return;
            }

			tile = new Tile();
			tile.transform.position = TileIndexToWorld(worldIndex);
			tile.key = key;
			tile.index = worldIndex;
			tile.offset = offset;

			instance.tileMap.Add(worldIndex, tile);

        }

		public static void DeleteTile(TableIndex worldIndex)
        {
			instance.tileMap.Remove(worldIndex);
		}

		public static Tile FindTile(TableIndex worldIndex)
        {
			Tile tile;
			if(instance.tileMap.TryGetValue(worldIndex, out tile) == true)
            {
				return tile;
            }
			return null;
        }

		public static void CreateObject(SpriteType key, TableIndex worldIndex, TableIndex offset)
		{
			if (worldIndex.row < 0 || worldIndex.col < 0) return;

			SubTile tile;
			if (instance.subTileMap.TryGetValue(worldIndex, out tile))
			{
				return;
			}

			tile = new SubTile();
			tile.transform.position = TileIndexToWorld(worldIndex);
			tile.key = key;
			tile.index = worldIndex;
			tile.offset = offset;

			instance.subTileMap.Add(worldIndex, tile);

		}

		public static void DeleteObject(TableIndex worldIndex)
		{
			instance.subTileMap.Remove(worldIndex);
		}

		public static Tile FindObject(TableIndex worldIndex)
		{
			SubTile tile = null;
			if (instance.subTileMap.TryGetValue(worldIndex, out tile) == true)
			{
				return tile;
			}
			return null;
		}

		public static void CreateMoveableTile(TableIndex idx)
        {
			TableIndex val;
			if(instance.wallMap.TryGetValue(idx,out val))
            {
				return;
            }

			instance.wallMap.Add(idx, idx);
        }

		public static void DeleteMoveableTile(TableIndex idx)
        {
			instance.wallMap.Remove(idx);
        }

		public static bool FindMoveableTile(TableIndex idx)
        {
			TableIndex val;
			if (instance.wallMap.TryGetValue(idx, out val))
			{
				return true;
			}
			return false;
		}

		public static void Save(string path)
        {
			FileStream fs = new FileStream(path, FileMode.OpenOrCreate);
			if (fs == null) return;

			byte[] buffer;
			int count = instance.tileMap.Count;
			buffer = BitConverter.GetBytes(count);
			fs.Write(buffer, 0, buffer.Length);

			foreach(KeyValuePair<TableIndex,Tile> pair in instance.tileMap)
            {
				Tile tile = pair.Value;
				int key = (int)tile.key;
				buffer = BitConverter.GetBytes(key);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.offset.row);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.offset.col);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.index.row);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.index.col);
				fs.Write(buffer, 0, buffer.Length);
			}

			count = instance.subTileMap.Count;
			buffer = BitConverter.GetBytes(count);
			fs.Write(buffer, 0, buffer.Length);

			foreach (var pair in instance.subTileMap)
			{
				SubTile tile = pair.Value;
				int key = (int)tile.key;
				buffer = BitConverter.GetBytes(key);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.offset.row);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.offset.col);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.index.row);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(tile.index.col);
				fs.Write(buffer, 0, buffer.Length);
			}

			count = instance.wallMap.Count;
			buffer = BitConverter.GetBytes(count);
			fs.Write(buffer, 0, buffer.Length);

			foreach (var pair in instance.wallMap)
			{
				TableIndex idx = pair.Key;
				buffer = BitConverter.GetBytes(idx.row);
				fs.Write(buffer, 0, buffer.Length);
				buffer = BitConverter.GetBytes(idx.col);
				fs.Write(buffer, 0, buffer.Length);
			}

			fs.Close();
        }

		public static void Load(string path)
        {
			instance.tileMap.Clear();

			FileStream fs = new FileStream(path, FileMode.Open);
			if (fs == null) return;


			byte[] buffer = new byte[4];
			int count = 0;

			fs.Read(buffer, 0, 4);
			count = BitConverter.ToInt32(buffer, 0);

			for (int i = 0; i < count; i++) 
            {
				SpriteType key = 0;
				TableIndex offset = new TableIndex(0, 0);
				TableIndex index = new TableIndex(0, 0);

				fs.Read(buffer, 0, 4);
				key = (SpriteType)BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				offset.row = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				offset.col = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				index.row = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				index.col = BitConverter.ToInt32(buffer, 0);

				CreateTile(key, index, offset);
            }


			fs.Read(buffer, 0, 4);
			count = BitConverter.ToInt32(buffer, 0);

			for (int i = 0; i < count; i++)
			{
				SpriteType key = 0;
				TableIndex offset = new TableIndex(0, 0);
				TableIndex index = new TableIndex(0, 0);

				fs.Read(buffer, 0, 4);
				key = (SpriteType)BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				offset.row = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				offset.col = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				index.row = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				index.col = BitConverter.ToInt32(buffer, 0);

				CreateObject(key, index, offset);
			}

			fs.Read(buffer, 0, 4);
			count = BitConverter.ToInt32(buffer, 0);

			for (int i = 0; i < count; i++)
			{
				TableIndex index = new TableIndex(0, 0);

				fs.Read(buffer, 0, 4);
				index.row = BitConverter.ToInt32(buffer, 0);
				fs.Read(buffer, 0, 4);
				index.col = BitConverter.ToInt32(buffer, 0);

				CreateMoveableTile(index);
			}

			fs.Close();
        }
	}
}
