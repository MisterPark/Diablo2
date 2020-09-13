#pragma once
#include <Windows.h>
#include <iostream>
#include <list>

enum JPSDirection
{
	UU = 0,
	RR,
	DD,
	LL,
	LU,
	RU,
	RD,
	LD
};

typedef struct JPSNode
{
	JPSNode* parent;
	int x;
	int y;
	int direction;

	JPSNode(JPSNode* parent, int x, int y, int direct)
	{
		this->parent = parent;
		this->x = x;
		this->y = y;
		this->direction = direct;
	}
	virtual ~JPSNode()
	{

	}
	int G(int sx, int sy)
	{
		float fx = (x * dfTILE_W_HALF) + ((y % 2) * (dfTILE_W_Q)) + dfTILE_W_Q;
		float fy = y * dfTILE_H_Q;
		float fsx = (sx * dfTILE_W_HALF) + ((sy % 2) * (dfTILE_W_Q)) + dfTILE_W_Q;
		float fsy = sy * dfTILE_H_Q;
		return sqrt(pow(fsx - fx, 2) + pow(fsy - fy, 2)) * 10;
	}
	int H(int ex, int ey)
	{
		float fx = (x * dfTILE_W_HALF) + ((y % 2) * (dfTILE_W_Q)) + dfTILE_W_Q;
		float fy = y * dfTILE_H_Q;
		float fex = (ex * dfTILE_W_HALF) + ((ey % 2) * (dfTILE_W_Q)) + dfTILE_W_Q;
		float fey = ey * dfTILE_H_Q;
		return (abs(fx - fex) + abs(fy - fey)) * 10;
	}
	int F(int sx, int sy, int ex, int ey)
	{
		return G(sx, sy) + H(ex, ey);
	}
}Node;

using namespace std;

class JPS
{
public:
	JPS();
	JPS(int left, int top, int right, int bottom);
	virtual ~JPS();

	//세팅 관련
	void SetMapSize(int left, int top, int right, int bottom);
	void SetStartPos(int x, int y);
	void PushWall(int x, int y);
	void PopWall(int x, int y);
	//게터 관련
	int GetPathListSize();
	bool GetPath(int index, int* outX, int*outY);

	// 탐색 관련
	bool Search(int sx, int sy, int ex, int ey); // 목적지 탐색
private:
	bool SearchDirection(int direction, int sx, int sy, int ex, int ey, JPSNode* caller); // 방향 탐색
	void Move(int direct, int* outX, int* outY);
	bool OutofRange(int x, int y);
	bool SearchDiagonal(int direct, int sx, int sy, int ex, int ey, JPSNode* caller);
	bool SearchCorner(int direct, int sx, int sy, int ex, int ey);
	bool isCorner(int direction, int x, int y);
	bool isLeftCorner(int direction, int x, int y, int* outDir);
	bool isRightCorner(int direction, int x, int y, int* outDir);
	int GetDirection(JPSNode* target); // 해당노드의 방향확인
	bool isWall(int x, int y);

	JPSNode* CreateNodeInOpen(JPSNode* parent, int x, int y, int direct);
	void InsertToOpen(JPSNode* target);
	JPSNode* RemoveToOpen(JPSNode* target);
	JPSNode* MinFInOpen(int sx, int sy, int ex, int ey);

	void InsertToClose(JPSNode* target);
	JPSNode* RemoveToClose(JPSNode* target);
	
	void InsertToPath(JPSNode* target);
	void DeleteAllGarbageNode();

private:
	int map_left;
	int map_top;
	int map_right;
	int map_bottom;

	JPSNode* sNode = nullptr;

	list<JPSNode*> openlist;
	list<JPSNode*> closelist;
	list<JPSNode*> walllist;
	list<JPSNode*> pathlist;

	list<JPSNode*> nodeManager; // 노드관리자.(벽노드 제외) Node new할당 시 리스트에 넣어줄 것
};

