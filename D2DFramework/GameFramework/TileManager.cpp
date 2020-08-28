#include "pch.h"
#include "TileManager.h"

TileManager* pTileManager = nullptr;

TileManager::TileManager()
{
}

TileManager::~TileManager()
{
}

TileManager * TileManager::GetInstance()
{
	if (pTileManager == nullptr)
	{
		pTileManager = new TileManager;
	}
	return pTileManager;
}

void TileManager::Release()
{
	//DeleteAllTiles();
	delete pTileManager;
}

void TileManager::Update()
{
	if (InputManager::GetKeyDown('T'))
	{
		pTileManager->isVisible = !pTileManager->isVisible;
	}
}

void TileManager::Render()
{
	if (pTileManager->isVisible == false) return;
	
	// 타일
	RenderTile();
	// 격자
	RenderCrossLine();
	// 좌표(타일 인덱스)
	RenderMousePosition();
	// 타일 선택창
	//RenderTileSet();
	// 타일 선택영역
	RenderTileSelector();
	// 선택된 타일 표시
	//RenderSelectedTile();
}

void TileManager::RenderTile()
{
	for (auto iter : pTileManager->tileMap)
	{
		Tile* tile = iter.second;
		Vector3 pos = tile->GetPositionFromCamera();
		//RenderManager::DrawTile(SpriteType::NORMAL, tile->tileset, tile->offsetIndex, pos.x, pos.y);

		RECT rt = { pos.x + 1,pos.y + 1,pos.x + dfTILE_W - 1,pos.y + dfTILE_H - 1 };


	}
}

void TileManager::RenderCrossLine()
{
	int screenW = dfCLIENT_WIDTH;
	int screenH = dfCLIENT_HEIGHT;
	int w = screenW / dfTILE_W + 1;
	int h = screenH / dfTILE_H + 2;
	int offsetX = Camera::GetX() % dfTILE_W;
	int offsetY = Camera::GetY() % dfTILE_H;
	int diagonalCount = w + h;

	#ifdef ISOMETRIC
	w = screenW / dfTILE_W_HALF + 1;
	h = screenH / dfTILE_H_HALF + 2;
	// 가로선
	for (int row = 0; row < h; row++)
	{
		int sy = row * dfTILE_H_HALF - offsetY;

		D2DRenderManager::DrawLine(0, sy, screenW, sy);


}
	// 세로선
	for (int col = 0; col < w; col++)
	{
		int sx = col * dfTILE_W_HALF - offsetX;

		D2DRenderManager::DrawLine(sx, 0, sx, screenH);
	}

	#else
	w = screenW / dfTILE_W + 1;
	h = screenH / dfTILE_H + 2;

	// 가로선
	for (int row = 0; row < h; row++)
	{
		int sy = row * dfTILE_H - offsetY;

		RenderManager::DrawLine(0, sy, screenW, sy, RGB(255, 0, 255));


	}
	// 세로선
	for (int col = 0; col < w; col++)
	{
		int sx = col * dfTILE_W - offsetX;

		RenderManager::DrawLine(sx, 0, sx, screenH, RGB(255, 0, 255));
	}
	#endif // ISOMETRIC

	

	// 대각선 /
	for (int cnt = -1; cnt < diagonalCount; cnt++)
	{
		int sx = (cnt * dfTILE_W) - offsetX - (offsetY * 2);
		int ey = (cnt * dfTILE_H) - offsetY - (offsetX / 2);

		D2DRenderManager::DrawLine(sx, 0, 0, ey);
	}

	// 대각선 
	for (int cnt = -1; cnt < diagonalCount; cnt++)
	{
		int sx = dfCLIENT_WIDTH - (cnt * dfTILE_W) - offsetX + (offsetY * 2);
		int ey = (cnt * dfTILE_H) - offsetY + (offsetX / 2);

		D2DRenderManager::DrawLine(sx, 0, dfCLIENT_WIDTH, ey);
	}
}

void TileManager::RenderMousePosition()
{
	// 좌표(타일 인덱스)
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	POINT idx = GetTileIndexFromMouse();

	WCHAR wstr[128];
	wsprintf(wstr, L"Mouse[%d,%d]   Camera[%d,%d]  Tile(%d,%d) Count:%d", pt.x, pt.y,Camera::GetX(),Camera::GetY(), idx.y, idx.x, pTileManager->tileMap.size());
	D2DRenderManager::DrawString(wstr, 100, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void TileManager::RenderTileSelector()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

#ifdef ISOMETRIC

	float offsetX = (Camera::GetX());
	float offsetY = (Camera::GetY());
	POINT idx = GetTileIndexFromMouse();

	float sx = (idx.x * dfTILE_W) + ((idx.y % 2) *(dfTILE_W_HALF)) - offsetX;
	float sy = (idx.y * dfTILE_H_HALF) - offsetY;

	D2DRenderManager::DrawLine(sx, sy + dfTILE_H_HALF, sx + dfTILE_W_HALF, sy, D3DCOLOR_ARGB(255, 0, 255, 0));
	D2DRenderManager::DrawLine(sx+dfTILE_W_HALF, sy, sx + dfTILE_W, sy+dfTILE_H_HALF, D3DCOLOR_ARGB(255, 0, 255, 0));
	D2DRenderManager::DrawLine(sx+dfTILE_W, sy+dfTILE_H_HALF, sx+dfTILE_W_HALF, sy+dfTILE_H, D3DCOLOR_ARGB(255, 0, 255, 0));
	D2DRenderManager::DrawLine(sx+dfTILE_W_HALF, sy+dfTILE_H, sx, sy+dfTILE_H_HALF, D3DCOLOR_ARGB(255, 0, 255, 0));

#else
	int offsetX = Camera::GetX() % dfTILE_W;
	int offsetY = Camera::GetY() % dfTILE_H;

	POINT idx;
	idx.x = (pt.x + offsetX) / dfTILE_W;
	idx.y = (pt.y + offsetY) / dfTILE_H;

	RECT rect;
	rect.left = idx.x * dfTILE_W - offsetX;
	rect.top = idx.y * dfTILE_H - offsetY;
	rect.right = rect.left + dfTILE_W;
	rect.bottom = rect.top + dfTILE_H;

	RenderManager::DrawSimpleCollider(rect, RGB(0, 255, 0));
#endif // ISOMETRIC
}

POINT TileManager::GetTileIndexFromMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	float worldX = (pt.x + Camera::GetX());
	float worldY = (pt.y + Camera::GetY());

	POINT idx;
	#ifdef ISOMETRIC
		//idx.x = (worldX / dfTILE_W_HALF + worldY / dfTILE_H_HALF) / 2;
		//idx.y = (worldY / dfTILE_H_HALF - (worldX / dfTILE_W_HALF)) / 2;
		
		idx.y = worldY / dfTILE_H_HALF;
		idx.x = (worldX - ((idx.y % 2)*(dfTILE_W_HALF))) / dfTILE_W;
	#else
		idx.x =  worldX / dfTILE_W;
		idx.y =  worldY / dfTILE_H;
	#endif // ISOMETRIC

	

	return idx;
}

//void TileManager::CreateTile(int indexX, int indexY, int offset)
//{
//	if (indexX < 0 || indexY < 0) return;
//	 
//	auto target = pTileManager->tileMap.find(Point(indexX, indexY));
//
//	if (target != pTileManager->tileMap.end())
//	{
//		return;
//	}
//
//	Tile* tile = new Tile;
//	//tile->transform.x = indexX * dfTILE_W;
//	//tile->transform.y = indexY * dfTILE_H;
//	//tile->tileset = pTileManager->curTileSet;
//	//tile->offsetIndex = offset;
//
//	pTileManager->tileMap.insert(make_pair(Point(indexX, indexY), tile));
//}
//
//void TileManager::CreateTile(int indexX, int indexY,SpriteIndex tileSet, int offset, DWORD option, Point movePoint)
//{
//	auto target = pTileManager->tileMap.find(Point(indexX, indexY));
//
//	if (target != pTileManager->tileMap.end())
//	{
//		return;
//	}
//
//	Tile* tile = new Tile;
//	//tile->transform.x = indexX * dfTILE_W;
//	//tile->transform.y = indexY * dfTILE_H;
//	//tile->tileset = tileSet;
//	//tile->offsetIndex = offset;
//	//tile->option = option;
//	//tile->ePoint = movePoint;
//	//tile->sPoint = { indexX,indexY };
//
//	pTileManager->tileMap.insert(make_pair(Point(indexX, indexY), tile));
//}
//
//void TileManager::DeleteTile(int indexX, int indexY)
//{
//	auto target = pTileManager->tileMap.find(Point(indexX, indexY));
//	
//	if (target != pTileManager->tileMap.end())
//	{
//		delete target->second;
//		pTileManager->tileMap.erase(target);
//	}
//	
//}
//
//void TileManager::DeleteAllTiles()
//{
//	auto iter = pTileManager->tileMap.begin();
//	auto end = pTileManager->tileMap.end();
//	for (; iter != end;)
//	{
//		delete iter->second;
//		iter = pTileManager->tileMap.erase(iter);
//	}
//}
//
//Tile* TileManager::FindTile(int indexX, int indexY)
//{
//	auto iter = pTileManager->tileMap.find(Point(indexX, indexY));
//	if (iter != pTileManager->tileMap.end())
//	{
//		return iter->second;
//	}
//	return nullptr;
//}
//
//void TileManager::Save(const char* _fileName)
//{
//	FileManager::MakeDirectory("SaveData");
//	
//	char fullName[128] = { 0, };
//	strcat_s(fullName, "SaveData");
//	strcat_s(fullName, "/");
//	strcat_s(fullName, _fileName);
//
//	FileManager::SetDirectory(fullName);
//	FileManager::OpenFile("wb");
//
//	// 헤더
//	int tileCount = pTileManager->tileMap.size();
//	FileManager::WriteFile(&tileCount, sizeof(int), 1);
//
//	// 데이터
//	for (auto iter : pTileManager->tileMap)
//	{
//		Point index = iter.first;
//		Tile* tile = iter.second;
//
//		//FileManager::WriteFile(&index.x, sizeof(int), 1);
//		//FileManager::WriteFile(&index.y, sizeof(int), 1);
//		//FileManager::WriteFile(&tile->tileset, sizeof(SpriteIndex), 1);
//		//FileManager::WriteFile(&tile->offsetIndex, sizeof(int), 1);
//		//FileManager::WriteFile(&tile->option, sizeof(DWORD), 1);
//		//FileManager::WriteFile(&tile->ePoint, sizeof(Point), 1);
//	}
//
//	FileManager::CloseFile();
//}
//
//void TileManager::Load(const char* _fileName)
//{
//	DeleteAllTiles();
//
//	char fullName[128] = { 0, };
//	strcat_s(fullName, "SaveData");
//	strcat_s(fullName, "/");
//	strcat_s(fullName, _fileName);
//
//	FileManager::MakeDirectory("SaveData");
//	FileManager::SetDirectory(fullName);
//	FileManager::OpenFile("rb");
//
//	// 헤더
//	int tileCount;
//	FileManager::ReadFile(&tileCount, sizeof(int), 1);
//
//	// 데이터
//	for (int i = 0; i < tileCount; i++)
//	{
//		Point index;
//		SpriteIndex tileSet;
//		int offsetIndex;
//		DWORD option;
//		Point movePoint;
//
//		FileManager::ReadFile(&index.x, sizeof(int), 1);
//		FileManager::ReadFile(&index.y, sizeof(int), 1);
//		FileManager::ReadFile(&tileSet, sizeof(SpriteIndex), 1);
//		FileManager::ReadFile(&offsetIndex, sizeof(int), 1);
//		FileManager::ReadFile(&option, sizeof(DWORD), 1);
//		FileManager::ReadFile(&movePoint, sizeof(Point), 1);
//
//		CreateTile(index.x, index.y, tileSet, offsetIndex, option, movePoint);
//	}
//
//	FileManager::CloseFile();
//}
//
//void TileManager::LoadToGameScene(const char* _fileName)
//{
//	ObjectManager::DestroyAll(ObjectType::TILE);
//
//	char fullName[128] = { 0, };
//	strcat_s(fullName, "SaveData");
//	strcat_s(fullName, "/");
//	strcat_s(fullName, _fileName);
//
//	FileManager::MakeDirectory("SaveData");
//	FileManager::SetDirectory(fullName);
//	FileManager::OpenFile("rb");
//
//	// 헤더
//	int tileCount;
//	FileManager::ReadFile(&tileCount, sizeof(int), 1);
//
//	// 데이터
//	for (int i = 0; i < tileCount; i++)
//	{
//		Point index;
//		SpriteIndex tileSet;
//		int offsetIndex;
//		DWORD option;
//		Point movePoint;
//
//		FileManager::ReadFile(&index.x, sizeof(int), 1);
//		FileManager::ReadFile(&index.y, sizeof(int), 1);
//		FileManager::ReadFile(&tileSet, sizeof(SpriteIndex), 1);
//		FileManager::ReadFile(&offsetIndex, sizeof(int), 1);
//		FileManager::ReadFile(&option, sizeof(DWORD), 1);
//		FileManager::ReadFile(&movePoint, sizeof(Point), 1);
//
//		Tile* tile = (Tile*)ObjectManager::CreateObject(ObjectType::TILE);
//		//tile->transform.x = index.x * dfTILE_W;
//		//tile->transform.y = index.y * dfTILE_H;
//		//tile->tileset = tileSet;
//		//tile->offsetIndex = offsetIndex;
//		//tile->option = option;
//		//tile->ePoint = movePoint;
//		//tile->sPoint = { index.x,index.y };
//	}
//
//	FileManager::CloseFile();
//}