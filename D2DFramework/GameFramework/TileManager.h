#pragma once
#include "Tile.h"
class JPS;

// 아이소매트릭 미사용시 주석처리
#define ISOMETRIC

#define dfEDIT_WIDTH 800
#define dfEDIT_HEIGHT 600

#define dfTILE_W 160
#define dfTILE_H 80
#define dfTILE_W_HALF 80
#define dfTILE_H_HALF 40
#define dfTILE_W_Q 40
#define dfTILE_H_Q 20

class TileManager
{
private:
	TileManager();
	~TileManager();

public:
	static TileManager* GetInstance();
	static void Release();

	static void Update();
	static void Render();
	static void RenderLine();
private:
	static void RenderTile();
	static void RenderCrossLine();
	static void RenderMousePosition();
	static void RenderTileSelector();
	static void RenderWall();
	static void RenderPath();
public:
	static Vector3 MouseToTilePosition();
	static TableIndex MouseToTileIndex();
	static Vector3 TileIndexToWorld(const TableIndex& index);

	static Vector3 MouseToWallPosition();
	static TableIndex MouseToWallIndex();
	static Vector3 WallIndexToWorld(const TableIndex& index);
	static Vector3 WallIndexToWorldCenter(const TableIndex& index);

	static TableIndex PositionToWallIndex(Vector3 pos);
	static TableIndex PositionToWallIndex(POINT pos);
	//
	
	//
	static void CreateTile(SpriteType spriteKey, TableIndex worldIndex, TableIndex offset);
//	//static void CreateTile(int indexX, int indexY,SpriteIndex tileSet, int offset, DWORD option, Point movePoint);
//	static void DeleteTile(int indexX, int indexY);
	static void DeleteAllTiles();
//	static Tile* FindTile(int indexX, int indexY);
	static void AddWall(TableIndex idx);
	static void RemoveWall(TableIndex idx);
	static void RemoveAllWall();
//
//	static void Save(const char* _fileName);
	static void Load(const char* _fileName);
//	static void LoadToGameScene(const char* _fileName);

	static bool PathFinding(int sx, int sy, int ex, int ey);
	static void SetSearchSize(int left, int top, int right, int bottom);
	static int GetPathListCount();
	static bool GetPath(int index, int* outX, int* outY);

public:
	
	int selectedTileIndex = 0;
	//SpriteIndex curTileSet;
	bool isVisible = true;
	bool isDebugMode = false;
	bool isShowTileSet = false;
	RECT tileSetArea;
	map<TableIndex, Tile*> tileMap;
	set<TableIndex> wallList;


	JPS* pJPS = nullptr;
	list<TableIndex> pathList;
};

