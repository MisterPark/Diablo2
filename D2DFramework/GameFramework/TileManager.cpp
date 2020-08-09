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
	DeleteAllTiles();
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
	RenderTileSet();
	// 타일 선택영역
	RenderTileSelector();
	// 선택된 타일 표시
	RenderSelectedTile();
}

void TileManager::RenderTile()
{
	for (auto iter : pTileManager->tileMap)
	{
		Tile* tile = iter.second;
		Transform pos = tile->GetPositionFromCamera();
		RenderManager::DrawTile(SpriteType::NORMAL, tile->tileset, tile->offsetIndex, pos.x, pos.y);

		RECT rt = { pos.x + 1,pos.y + 1,pos.x + dfTILE_W - 1,pos.y + dfTILE_H - 1 };

		if (tile->option & dfTILE_OPTION_COLLISION_TOP)
		{
			RenderManager::DrawLine(rt.left, rt.top, rt.right, rt.top, RGB(255, 0, 0));
		}
		if (tile->option & dfTILE_OPTION_COLLISION_BOTTOM)
		{
			RenderManager::DrawLine(rt.left, rt.bottom, rt.right, rt.bottom, RGB(255, 0, 0));
		}
		if (tile->option & dfTILE_OPTION_COLLISION_LEFT)
		{
			RenderManager::DrawLine(rt.left, rt.top, rt.left, rt.bottom, RGB(255, 0, 0));
		}
		if (tile->option & dfTILE_OPTION_COLLISION_RIGHT)
		{
			RenderManager::DrawLine(rt.right, rt.top, rt.right, rt.bottom, RGB(255, 0, 0));
		}
		if (tile->option & dfTILE_OPTION_STICK)
		{
			RenderManager::DrawLine(rt.left, rt.top, rt.right, rt.bottom, RGB(255, 0, 0));
		}

	}
}

void TileManager::RenderCrossLine()
{
	int screenW = RenderManager::GetWidth();
	int screenH = RenderManager::GetHeight();
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

		RenderManager::DrawLine(0, sy, screenW, sy, RGB(255, 0, 255));


}
	// 세로선
	for (int col = 0; col < w; col++)
	{
		int sx = col * dfTILE_W_HALF - offsetX;

		RenderManager::DrawLine(sx, 0, sx, screenH, RGB(255, 0, 255));
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

		RenderManager::DrawLine(sx, 0, 0, ey, RGB(255, 0, 255));
	}

	// 대각선 
	for (int cnt = -1; cnt < diagonalCount; cnt++)
	{
		int sx = RenderManager::GetWidth() - (cnt * dfTILE_W) - offsetX + (offsetY * 2);
		int ey = (cnt * dfTILE_H) - offsetY + (offsetX / 2);

		RenderManager::DrawLine(sx, 0, RenderManager::GetWidth(), ey, RGB(255, 0, 0));
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
	RenderManager::DrawString(wstr, 100, 0, RGB(254, 254, 254));
}

void TileManager::RenderTileSet()
{
	if (!pTileManager->isShowTileSet) return;

	int tileSetWidth;
	int tileSetHeight;
	RenderManager::GetSpriteSize(pTileManager->curTileSet, &tileSetWidth, &tileSetHeight);
	int tileSetX = dfEDIT_WIDTH - tileSetWidth;
	int tileSetY = dfEDIT_HEIGHT - tileSetHeight;

	pTileManager->tileSetArea.left = tileSetX;
	pTileManager->tileSetArea.top = tileSetY;
	pTileManager->tileSetArea.right = tileSetX + tileSetWidth;
	pTileManager->tileSetArea.bottom = tileSetY + tileSetHeight;
	RenderManager::DrawRect(pTileManager->tileSetArea, RGB(255, 0, 255));
	RenderManager::DrawSprite(SpriteType::NORMAL, pTileManager->curTileSet, tileSetX, tileSetY);

}

void TileManager::RenderTileSelector()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	if (pTileManager->isShowTileSet)
	{
		if (pTileManager->tileSetArea.left > pt.x) return;
		if (pTileManager->tileSetArea.right < pt.x) return;
		if (pTileManager->tileSetArea.top > pt.y) return;
		if (pTileManager->tileSetArea.bottom < pt.y) return;

		POINT idx;
		idx.x = (pt.x) / dfTILE_W;
		idx.y = (pt.y) / dfTILE_H;

		RECT rect;
		rect.left = idx.x * dfTILE_W;
		rect.top = idx.y * dfTILE_H;
		rect.right = rect.left + dfTILE_W;
		rect.bottom = rect.top + dfTILE_H;

		RenderManager::DrawSimpleCollider(rect, RGB(0, 255, 0));
	}
	else
	{
	#ifdef ISOMETRIC

		int worldX = pt.x;
		int worldY = pt.y;
		POINT idx;
		idx.x = (worldX / dfTILE_W_HALF + worldY / dfTILE_H_HALF) / 2;
		idx.y = (worldY / dfTILE_H_HALF - (worldX / dfTILE_W_HALF)) / 2;

		int sx = (idx.x - idx.y) * dfTILE_W_HALF -(Camera::GetX() % dfTILE_W);
		int sy = (idx.x + idx.y) * dfTILE_H_HALF -(Camera::GetY() % dfTILE_H);

		RenderManager::DrawLine(sx, sy, sx + dfTILE_W_HALF, sy +dfTILE_H_HALF,RGB(0,255,0));
		RenderManager::DrawLine(sx + dfTILE_W_HALF, sy + dfTILE_H_HALF, sx, sy +dfTILE_H, RGB(0, 255, 0));
		RenderManager::DrawLine(sx, sy+dfTILE_H, sx - dfTILE_W_HALF, sy + dfTILE_H_HALF, RGB(0, 255, 0));
		RenderManager::DrawLine(sx - dfTILE_W_HALF, sy + dfTILE_H_HALF, sx , sy, RGB(0, 255, 0));

	
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
}

void TileManager::RenderSelectedTile()
{
	RenderManager::DrawTile(SpriteType::NORMAL, pTileManager->curTileSet, pTileManager->selectedTileIndex, 600, 0);
}

void TileManager::ShowTileSet()
{
	pTileManager->isShowTileSet = !pTileManager->isShowTileSet;

}

void TileManager::SetEditMode(bool _isEdit)
{
	pTileManager->isVisible = _isEdit;
}

RECT TileManager::GetTileSetArea()
{
	return pTileManager->tileSetArea;
}

bool TileManager::IsMouseOnTileSet()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	if (pTileManager->tileSetArea.left > pt.x) return false;
	if (pTileManager->tileSetArea.right < pt.x) return false;
	if (pTileManager->tileSetArea.top > pt.y) return false;
	if (pTileManager->tileSetArea.bottom < pt.y) return false;

	return true;
}

POINT TileManager::GetTileSetIndex()
{
	POINT pt; // 클라이언트 기준 마우스 위치
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	// 타일셋창 위치
	int offsetX = pt.x - pTileManager->tileSetArea.left;
	int offsetY = pt.y - pTileManager->tileSetArea.top;

	POINT idx; // 타일 인덱스 
	idx.x = offsetX / dfTILE_W;
	idx.y = offsetY / dfTILE_H;

	return idx;
}

void TileManager::SelectTileFromTileSet(POINT pt)
{
	int w, h;
	RenderManager::GetSpriteSize(pTileManager->curTileSet, &w, &h);
	int colCount = w / dfTILE_W;

	pTileManager->selectedTileIndex = colCount * pt.y + pt.x;
}

void TileManager::SetTileSet(SpriteIndex _tileset)
{
	pTileManager->curTileSet = _tileset;
}

POINT TileManager::GetTileIndexFromMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	int worldX = (pt.x + Camera::GetX());
	int worldY = (pt.y + Camera::GetY());

	POINT idx;
	#ifdef ISOMETRIC
		idx.x = (worldX / dfTILE_W_HALF + worldY / dfTILE_H_HALF) / 2;
		idx.y = (worldY / dfTILE_H_HALF - (worldX / dfTILE_W_HALF)) / 2;
	#else
		idx.x =  worldX / dfTILE_W;
		idx.y =  worldY / dfTILE_H;
	#endif // ISOMETRIC

	

	return idx;
}

void TileManager::CreateTile(int indexX, int indexY, int offset)
{
	if (indexX < 0 || indexY < 0) return;
	 
	auto target = pTileManager->tileMap.find(Point(indexX, indexY));

	if (target != pTileManager->tileMap.end())
	{
		return;
	}

	Tile* tile = new Tile;
	tile->position.x = indexX * dfTILE_W;
	tile->position.y = indexY * dfTILE_H;
	tile->tileset = pTileManager->curTileSet;
	tile->offsetIndex = offset;

	pTileManager->tileMap.insert(make_pair(Point(indexX, indexY), tile));
}

void TileManager::CreateTile(int indexX, int indexY,SpriteIndex tileSet, int offset, DWORD option, Point movePoint)
{
	auto target = pTileManager->tileMap.find(Point(indexX, indexY));

	if (target != pTileManager->tileMap.end())
	{
		return;
	}

	Tile* tile = new Tile;
	tile->position.x = indexX * dfTILE_W;
	tile->position.y = indexY * dfTILE_H;
	tile->tileset = tileSet;
	tile->offsetIndex = offset;
	tile->option = option;
	tile->ePoint = movePoint;
	tile->sPoint = { indexX,indexY };

	pTileManager->tileMap.insert(make_pair(Point(indexX, indexY), tile));
}

void TileManager::DeleteTile(int indexX, int indexY)
{
	auto target = pTileManager->tileMap.find(Point(indexX, indexY));
	
	if (target != pTileManager->tileMap.end())
	{
		delete target->second;
		pTileManager->tileMap.erase(target);
	}
	
}

void TileManager::DeleteAllTiles()
{
	auto iter = pTileManager->tileMap.begin();
	auto end = pTileManager->tileMap.end();
	for (; iter != end;)
	{
		delete iter->second;
		iter = pTileManager->tileMap.erase(iter);
	}
}

Tile* TileManager::FindTile(int indexX, int indexY)
{
	auto iter = pTileManager->tileMap.find(Point(indexX, indexY));
	if (iter != pTileManager->tileMap.end())
	{
		return iter->second;
	}
	return nullptr;
}

void TileManager::Save(const char* _fileName)
{
	FileManager::MakeDirectory("SaveData");
	
	char fullName[128] = { 0, };
	strcat_s(fullName, "SaveData");
	strcat_s(fullName, "/");
	strcat_s(fullName, _fileName);

	FileManager::SetDirectory(fullName);
	FileManager::OpenFile("wb");

	// 헤더
	int tileCount = pTileManager->tileMap.size();
	FileManager::WriteFile(&tileCount, sizeof(int), 1);

	// 데이터
	for (auto iter : pTileManager->tileMap)
	{
		Point index = iter.first;
		Tile* tile = iter.second;

		FileManager::WriteFile(&index.x, sizeof(int), 1);
		FileManager::WriteFile(&index.y, sizeof(int), 1);
		FileManager::WriteFile(&tile->tileset, sizeof(SpriteIndex), 1);
		FileManager::WriteFile(&tile->offsetIndex, sizeof(int), 1);
		FileManager::WriteFile(&tile->option, sizeof(DWORD), 1);
		FileManager::WriteFile(&tile->ePoint, sizeof(Point), 1);
	}

	FileManager::CloseFile();
}

void TileManager::Load(const char* _fileName)
{
	DeleteAllTiles();

	char fullName[128] = { 0, };
	strcat_s(fullName, "SaveData");
	strcat_s(fullName, "/");
	strcat_s(fullName, _fileName);

	FileManager::MakeDirectory("SaveData");
	FileManager::SetDirectory(fullName);
	FileManager::OpenFile("rb");

	// 헤더
	int tileCount;
	FileManager::ReadFile(&tileCount, sizeof(int), 1);

	// 데이터
	for (int i = 0; i < tileCount; i++)
	{
		Point index;
		SpriteIndex tileSet;
		int offsetIndex;
		DWORD option;
		Point movePoint;

		FileManager::ReadFile(&index.x, sizeof(int), 1);
		FileManager::ReadFile(&index.y, sizeof(int), 1);
		FileManager::ReadFile(&tileSet, sizeof(SpriteIndex), 1);
		FileManager::ReadFile(&offsetIndex, sizeof(int), 1);
		FileManager::ReadFile(&option, sizeof(DWORD), 1);
		FileManager::ReadFile(&movePoint, sizeof(Point), 1);

		CreateTile(index.x, index.y, tileSet, offsetIndex, option, movePoint);
	}

	FileManager::CloseFile();
}

void TileManager::LoadToGameScene(const char* _fileName)
{
	ObjectManager::DestroyAll(ObjectType::TILE);

	char fullName[128] = { 0, };
	strcat_s(fullName, "SaveData");
	strcat_s(fullName, "/");
	strcat_s(fullName, _fileName);

	FileManager::MakeDirectory("SaveData");
	FileManager::SetDirectory(fullName);
	FileManager::OpenFile("rb");

	// 헤더
	int tileCount;
	FileManager::ReadFile(&tileCount, sizeof(int), 1);

	// 데이터
	for (int i = 0; i < tileCount; i++)
	{
		Point index;
		SpriteIndex tileSet;
		int offsetIndex;
		DWORD option;
		Point movePoint;

		FileManager::ReadFile(&index.x, sizeof(int), 1);
		FileManager::ReadFile(&index.y, sizeof(int), 1);
		FileManager::ReadFile(&tileSet, sizeof(SpriteIndex), 1);
		FileManager::ReadFile(&offsetIndex, sizeof(int), 1);
		FileManager::ReadFile(&option, sizeof(DWORD), 1);
		FileManager::ReadFile(&movePoint, sizeof(Point), 1);

		Tile* tile = (Tile*)ObjectManager::CreateObject(ObjectType::TILE);
		tile->position.x = index.x * dfTILE_W;
		tile->position.y = index.y * dfTILE_H;
		tile->tileset = tileSet;
		tile->offsetIndex = offsetIndex;
		tile->option = option;
		tile->ePoint = movePoint;
		tile->sPoint = { index.x,index.y };
	}

	FileManager::CloseFile();
}

void TileManager::LoadToGameSceneBack(const char * _fileName)
{
	ObjectManager::DestroyAll(ObjectType::BACK_TILE);

	char fullName[128] = { 0, };
	strcat_s(fullName, "SaveData");
	strcat_s(fullName, "/");
	strcat_s(fullName, _fileName);

	FileManager::MakeDirectory("SaveData");
	FileManager::SetDirectory(fullName);
	FileManager::OpenFile("rb");

	// 헤더
	int tileCount;
	FileManager::ReadFile(&tileCount, sizeof(int), 1);

	// 데이터
	for (int i = 0; i < tileCount; i++)
	{
		Point index;
		SpriteIndex tileSet;
		int offsetIndex;
		DWORD option;
		Point movePoint;

		FileManager::ReadFile(&index.x, sizeof(int), 1);
		FileManager::ReadFile(&index.y, sizeof(int), 1);
		FileManager::ReadFile(&tileSet, sizeof(SpriteIndex), 1);
		FileManager::ReadFile(&offsetIndex, sizeof(int), 1);
		FileManager::ReadFile(&option, sizeof(DWORD), 1);
		FileManager::ReadFile(&movePoint, sizeof(Point), 1);

		BackTile* tile = (BackTile*)ObjectManager::CreateObject(ObjectType::BACK_TILE);
		tile->position.x = index.x * dfTILE_W;
		tile->position.y = index.y * dfTILE_H;
		tile->tileset = tileSet;
		tile->offsetIndex = offsetIndex;
	}

	FileManager::CloseFile();
}
