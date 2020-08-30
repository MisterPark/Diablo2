#pragma once
#include "Tile.h"

// 아이소매트릭 미사용시 주석처리
#define ISOMETRIC

#define dfEDIT_WIDTH 800
#define dfEDIT_HEIGHT 600

#define dfTILE_W 160
#define dfTILE_H 80
#define dfTILE_W_HALF 80
#define dfTILE_H_HALF 40

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
public:
	static Vector3 MouseToTilePosition();
	static TableIndex MouseToTileIndex();
	static Vector3 TileIndexToWorld(const TableIndex& index);
//
	static void CreateTile(const wstring& spriteKey, TableIndex worldIndex, TableIndex offset);
//	//static void CreateTile(int indexX, int indexY,SpriteIndex tileSet, int offset, DWORD option, Point movePoint);
//	static void DeleteTile(int indexX, int indexY);
//	static void DeleteAllTiles();
//	static Tile* FindTile(int indexX, int indexY);
//
//	static void Save(const char* _fileName);
//	static void Load(const char* _fileName);
//	static void LoadToGameScene(const char* _fileName);

public:
	
	int selectedTileIndex = 0;
	//SpriteIndex curTileSet;
	bool isVisible = false;
	bool isShowTileSet = false;
	RECT tileSetArea;
	map<TableIndex, Tile*> tileMap;
};

