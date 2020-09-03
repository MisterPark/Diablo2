#include "pch.h"
#include "TileManager.h"
#include "SubTile.h"

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

	if (pTileManager->isVisible == false) return;

	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		//TableIndex pt = MouseToTileIndex();
		//
		//CreateTile(SpriteType::ACT1_TOWN_FLOOR, pt, TableIndex(0, 0), 1);
	}
}

void TileManager::Render()
{
	if (pTileManager->isVisible == false) return;
	
	// Ÿ��
	RenderTile();

	// ��ǥ(Ÿ�� �ε���)
	RenderMousePosition();
	// Ÿ�� ����â
	//RenderTileSet();
	
	// ���õ� Ÿ�� ǥ��
	//RenderSelectedTile();
}

void TileManager::RenderLine()
{
	// ����
	RenderCrossLine();
	// Ÿ�� ���ÿ���
	RenderTileSelector();
}

void TileManager::RenderTile()
{
	for (auto iter : pTileManager->tileMap)
	{
		Tile* tile = iter.second;
		tile->Render();
	}
}

void TileManager::RenderCrossLine()
{
	int screenW = dfCLIENT_WIDTH;
	int screenH = dfCLIENT_HEIGHT;
	int w = screenW / dfTILE_W_HALF + 1;
	int h = screenH / dfTILE_H_HALF + 2;
	int offsetX = Camera::GetX() % dfTILE_W_HALF;
	int offsetY = Camera::GetY() % dfTILE_H_HALF;
	int diagonalCount = w + h;

	#ifdef ISOMETRIC
	w = screenW / dfTILE_W_HALF + 1;
	h = screenH / dfTILE_H_HALF + 2;
//	// ���μ�
//	for (int row = 0; row < h; row++)
//	{
//		int sy = row * dfTILE_H_HALF - offsetY;
//
//		D2DRenderManager::DrawLine(0, sy, screenW, sy);
//
//
//}
//	// ���μ�
//	for (int col = 0; col < w; col++)
//	{
//		int sx = col * dfTILE_W_HALF - offsetX;
//
//		D2DRenderManager::DrawLine(sx, 0, sx, screenH);
//	}

	#else
	w = screenW / dfTILE_W + 1;
	h = screenH / dfTILE_H + 2;

	// ���μ�
	for (int row = 0; row < h; row++)
	{
		int sy = row * dfTILE_H - offsetY;

		RenderManager::DrawLine(0, sy, screenW, sy, RGB(255, 0, 255));


	}
	// ���μ�
	for (int col = 0; col < w; col++)
	{
		int sx = col * dfTILE_W - offsetX;

		RenderManager::DrawLine(sx, 0, sx, screenH, RGB(255, 0, 255));
	}
	#endif // ISOMETRIC

	

	// �밢�� /
	for (int cnt = -1; cnt < diagonalCount; cnt++)
	{
		int sx = (cnt * dfTILE_W_HALF) - offsetX - (offsetY * 2);
		int ey = (cnt * dfTILE_H_HALF) - offsetY - (offsetX / 2);

		D2DRenderManager::DrawLine(sx, 0, 0, ey);
	}

	// �밢�� 
	for (int cnt = -1; cnt < diagonalCount; cnt++)
	{
		int sx = dfCLIENT_WIDTH - (cnt * dfTILE_W_HALF) - offsetX + (offsetY * 2);
		int ey = (cnt * dfTILE_H_HALF) - offsetY + (offsetX / 2);

		D2DRenderManager::DrawLine(sx, 0, dfCLIENT_WIDTH, ey);
	}
}

void TileManager::RenderMousePosition()
{
	// ��ǥ(Ÿ�� �ε���)
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	TableIndex idx = MouseToTileIndex();

	WCHAR wstr[128];
	wsprintf(wstr, L"Mouse(%d,%d)   Camera(%d,%d)  Tile[%d,%d] Count:%d", pt.x, pt.y,Camera::GetX(),Camera::GetY(), idx.row, idx.col, pTileManager->tileMap.size());
	D2DRenderManager::DrawString(wstr, 100, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void TileManager::RenderTileSelector()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

#ifdef ISOMETRIC

	float offsetX = Camera::GetX();
	float offsetY = Camera::GetY();
	TableIndex idx = MouseToTileIndex();

	float sx = (idx.col * dfTILE_W) + ((idx.row % 2) *(dfTILE_W_HALF)) - offsetX;
	float sy = (idx.row * dfTILE_H_HALF) - offsetY;

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

Vector3 TileManager::MouseToTilePosition()
{
	Vector3 res;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	float worldX = (pt.x + Camera::GetX());
	float worldY = (pt.y + Camera::GetY());

	// y����
	// b = -ax + y;
	int interceptDown = worldX * -0.5f + worldY - dfTILE_H_HALF; // ��
	int interceptUp = worldX * 0.5f + worldY - dfTILE_H_HALF; // ��
	// �밢�� ���� ��ȣ 
	int downNum = interceptDown / dfTILE_H;
	int upNum = interceptUp / dfTILE_H;

	if (interceptDown < 0) downNum--;
	if (interceptUp < 0) upNum--;

	// �밢���� ����(����������)
	downNum *= dfTILE_H;
	upNum *= dfTILE_H;

	// y = ax + b
	res.x = upNum - downNum;
	res.y = (upNum - downNum) * 0.5f + downNum;

	// ���� // ���̾Ƹ�� ������ => ���簢�� �»��
	res.x -= dfTILE_W_HALF;
	// ���� // ùŸ�� �»�� 0,0 �������� �Ҷ�
	res.y += dfTILE_H_HALF;

	return res;
}

TableIndex TileManager::MouseToTileIndex()
{
	
	TableIndex idx;

#ifdef ISOMETRIC
	
	Vector3 tilePos = MouseToTilePosition();
	idx.row = tilePos.y / dfTILE_H_HALF;
	idx.col = tilePos.x / dfTILE_W;
		
#else
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	float worldX = (pt.x + Camera::GetX());
	float worldY = (pt.y + Camera::GetY());
	idx.col =  worldX / dfTILE_W;
	idx.row =  worldY / dfTILE_H;
	
#endif // ISOMETRIC

	return idx;
}

Vector3 TileManager::TileIndexToWorld(const TableIndex& index)
{
	Vector3 v;
	v.x = (index.col * dfTILE_W) + ((index.row % 2) * (dfTILE_W_HALF));
	v.y = index.row * dfTILE_H_HALF;
	return v;
}

void TileManager::CreateTile(SpriteType spriteKey, TableIndex worldIndex, TableIndex offset, int isMoveable)
{
	if (worldIndex.row < 0 || worldIndex.col < 0) return;
	 
	auto target = pTileManager->tileMap.find(worldIndex);

	if (target != pTileManager->tileMap.end())
	{
		return;
	}

	Tile* tile = new Tile;
	tile->transform.position = TileIndexToWorld(worldIndex);
	tile->spriteKey = spriteKey;
	tile->worldIndex = worldIndex;
	tile->offsetIndex = offset;

	pTileManager->tileMap.insert(make_pair(worldIndex, tile));
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

//Tile* TileManager::FindTile(int indexX, int indexY)
//{
//	auto iter = pTileManager->tileMap.find(Point(indexX, indexY));
//	if (iter != pTileManager->tileMap.end())
//	{
//		return iter->second;
//	}
//	return nullptr;
//}

void TileManager::Load(const char* _fileName)
{
	DeleteAllTiles();
	ObjectManager::DestroyAll(ObjectType::SUB_TILE);

	char fullName[128] = { 0, };
	strcat_s(fullName, "Data");
	strcat_s(fullName, "/");
	strcat_s(fullName, _fileName);

	FileManager::MakeDirectory("Data");
	FileManager::SetDirectory(fullName);
	FileManager::OpenFile("rb");

	// ���
	int tileCount;
	FileManager::ReadFile(&tileCount, sizeof(int), 1);

	// ������
	for (int i = 0; i < tileCount; i++)
	{
		SpriteType tileSet;
		TableIndex offset;
		TableIndex index;
		int isMoveable = 1;

		FileManager::ReadFile(&tileSet, sizeof(SpriteType), 1);
		FileManager::ReadFile(&offset.row, sizeof(int), 1);
		FileManager::ReadFile(&offset.col, sizeof(int), 1);
		FileManager::ReadFile(&index.row, sizeof(int), 1);
		FileManager::ReadFile(&index.col, sizeof(int), 1);
		FileManager::ReadFile(&isMoveable, sizeof(int), 1);

		CreateTile(tileSet,index,offset,isMoveable);
	}

	FileManager::ReadFile(&tileCount, sizeof(int), 1);

	// ������
	for (int i = 0; i < tileCount; i++)
	{
		SpriteType tileSet;
		TableIndex offset;
		TableIndex index;
		int isMoveable = 1;

		FileManager::ReadFile(&tileSet, sizeof(SpriteType), 1);
		FileManager::ReadFile(&offset.row, sizeof(int), 1);
		FileManager::ReadFile(&offset.col, sizeof(int), 1);
		FileManager::ReadFile(&index.row, sizeof(int), 1);
		FileManager::ReadFile(&index.col, sizeof(int), 1);

		CreateTile(tileSet, index, offset, isMoveable);
		SubTile* tile = (SubTile*)ObjectManager::CreateObject(ObjectType::SUB_TILE);
		tile->transform.position = TileIndexToWorld(index);
		tile->spriteKey = tileSet;
		tile->offsetIndex = offset;
		tile->worldIndex = index;
		
	}

	FileManager::CloseFile();
}

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
//	// ���
//	int tileCount;
//	FileManager::ReadFile(&tileCount, sizeof(int), 1);
//
//	// ������
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