#include "pch.h"
#include "JPS.h"



JPS::JPS()
{
}

JPS::JPS(int left, int top, int right, int bottom)
{
	this->map_left = left;
	this->map_top = top;
	this->map_right = right;
	this->map_bottom = bottom;
}

JPS::~JPS()
{
	delete sNode;
	sNode = nullptr;
}

void JPS::SetMapSize(int left, int top, int right, int bottom)
{
	this->map_left = left;
	this->map_top = top;
	this->map_right = right;
	this->map_bottom = bottom;
}

void JPS::SetStartPos(int x, int y)
{
	if (sNode == nullptr)
	{
		sNode = new JPSNode(nullptr, x, y, -1);
		//노드 매니저
		nodeManager.push_back(sNode);
	}
	else
	{
		sNode->parent = nullptr;
		sNode->x = x;
		sNode->y = y;
		sNode->direction = -1;
	}
}

void JPS::PushWall(int x, int y)
{
	if (!isWall(x, y))
	{
		JPSNode* node = new JPSNode(nullptr, x, y, -1);
		walllist.push_back(node);
	}
}

void JPS::PopWall(int x, int y)
{
	list<JPSNode*>::iterator iter;
	JPSNode* target;
	for (iter = walllist.begin(); iter != walllist.end(); ++iter)
	{
		if ((*iter)->x == x && (*iter)->y == y)
		{
			target = (JPSNode*)(*iter);
			delete target;
			target = nullptr;
			iter = walllist.erase(iter);
			break;
		}
	}
}

int JPS::GetPathListSize()
{
	return pathlist.size();
}

bool JPS::GetPath(int index, int * outX, int * outY)
{
	if (outX == nullptr || outY == nullptr) { return false; }

	int count = 0;
	list<JPSNode*>::iterator iter;
	for (iter = pathlist.begin(); iter != pathlist.end(); ++iter)
	{
		if (count == index)
		{
			*outX = (*iter)->x;
			*outY = (*iter)->y;
			return true;
		}
		count++;
	}

	return false;
}


////////////////////////////////////////////////////////////////////
// 탐색 관련
////////////////////////////////////////////////////////////////////

bool JPS::Search(int sx, int sy, int ex, int ey)
{
	int outX = 0;
	int outY = 0;
	openlist.clear();
	closelist.clear();
	pathlist.clear();
	DeleteAllGarbageNode();

	if (sNode == nullptr)
	{
		sNode = new JPSNode(nullptr, sx, sy, -1);
		//노드 매니저
		nodeManager.push_back(sNode);
	}
	else
	{
		sNode->parent = nullptr;
		sNode->x = sx;
		sNode->y = sy;
		sNode->direction = -1;
	}

	for (int i = 0; i < 8; i++)
	{
		SearchDirection(i, sx, sy, ex, ey, sNode);
	}

	InsertToClose(sNode);

	JPSNode* min;
	int direct;
	JPSDirection d;

	for (;;)
	{
		min = MinFInOpen(sx, sy, ex, ey);
		if (min == nullptr) { return false; }
		RemoveToOpen(min);
		InsertToClose(min);
		if (min->x == ex && min->y == ey)
		{
			// 길 리스트
			InsertToPath(min);
			return true;
		}

		d = (JPSDirection)min->direction;
		switch (d)
		{
		case UU:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case RR:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case DD:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case LL:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case LU:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			SearchDirection(UU, min->x, min->y, ex, ey, min);
			SearchDirection(LL, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case RU:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			SearchDirection(UU, min->x, min->y, ex, ey, min);
			SearchDirection(RR, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case RD:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			SearchDirection(RR, min->x, min->y, ex, ey, min);
			SearchDirection(DD, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		case LD:
			SearchDirection(min->direction, min->x, min->y, ex, ey, min);
			SearchDirection(DD, min->x, min->y, ex, ey, min);
			SearchDirection(LL, min->x, min->y, ex, ey, min);
			if (isLeftCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			if (isRightCorner(min->direction, min->x, min->y, &direct))
			{
				SearchDirection(direct, min->x, min->y, ex, ey, min);
			}
			break;
		default:
			break;
		}

	}

	return false;
}

bool JPS::SearchDirection(int direction, int sx, int sy, int ex, int ey, JPSNode* caller)
{
	int nowX = sx;
	int nowY = sy;

	for (;;)
	{

		// 한칸이동
		Move(direction, &nowX, &nowY);

		// 범위밖 확인
		if (OutofRange(nowX, nowY)) { break; }
		// 벽확인
		if (isWall(nowX, nowY)) { break; }
		
		// 임시 렌더
		//InsertToSearch(nowX, nowY);
		//Render();
		//Flip();

		// 대각선 전용
		if (SearchDiagonal(direction, nowX, nowY, ex, ey, caller)) { break; }

		// 코너확인
		if (isCorner(direction, nowX, nowY))
		{
			CreateNodeInOpen(caller, nowX, nowY, direction);
			return true;
		}
		// 도착확인
		if (nowX == ex && nowY == ey)
		{
			CreateNodeInOpen(caller, nowX, nowY, direction);
			return true;
		}
	}
	return false;
}

void JPS::Move(int direct, int * outX, int * outY)
{
	if (outX == nullptr) throw "인자 outX로 전달된 값이 nullptr 이었습니다.";
	if (outY == nullptr) throw "인자 outY로 전달된 값이 nullptr 이었습니다.";

	JPSDirection d = (JPSDirection)direct;
	int x = (*outX);
	int y = (*outY);

	switch (d)
	{
	case UU:
		y -= 2;
		break;
	case RR:
		x++;
		break;
	case DD:
		y += 2;
		break;
	case LL:
		x--;
		break;
	case LU:
		x -= (((y + 1) % 2) * 1);
		y--;
		break;
	case RU:
		x += ((y % 2) * 1);
		y--;
		break;
	case RD:
		x += ((y % 2) * 1);
		y++;
		break;
	case LD:
		x -= (((y + 1) % 2) * 1);
		y++;
		break;
	default:
		break;
	}

	*outX = x;
	*outY = y;
}

bool JPS::OutofRange(int x, int y)
{
	return (x < this->map_left || y < this->map_top || x >= this->map_right || y >= this->map_bottom);
}

bool JPS::SearchDiagonal(int direct, int sx, int sy, int ex, int ey, JPSNode * caller)
{
	bool find = false;
	JPSDirection d = (JPSDirection)direct;
	switch (d)
	{
	case LU:
		if (SearchCorner(LL, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		if (SearchCorner(UU, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		break;
	case RU:
		if (SearchCorner(RR, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		if (SearchCorner(UU, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		break;
	case RD:
		if (SearchCorner(RR, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		if (SearchCorner(DD, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		break;
	case LD:
		if (SearchCorner(LL, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		if (SearchCorner(DD, sx, sy, ex, ey)) { CreateNodeInOpen(caller, sx, sy, direct); return true; }
		break;
	default:
		return false;
		break;
	}

	return false;
}

bool JPS::SearchCorner(int direct, int sx, int sy, int ex, int ey)
{
	int nowX = sx;
	int nowY = sy;

	for (;;)
	{
		// 한칸이동
		Move(direct, &nowX, &nowY);
		// 범위밖 확인
		if (OutofRange(nowX, nowY)) { break; }
		// 벽확인
		if (isWall(nowX, nowY)) { break; }
		
		// 임시 렌더
		//InsertToSearch(nowX, nowY);
		//Render();
		//Flip();
		
		// 코너확인
		if (isCorner(direct, nowX, nowY)) { return true; }
		// 도착확인
		if (nowX == ex && nowY == ey) { return true; }

	}
	return false;
}

bool JPS::isCorner(int direction, int x, int y)
{
	JPSDirection d = (JPSDirection)direction;
	int t1x = x;
	int t1y = y;
	int t2x = x;
	int t2y = y;
	int t3x = x;
	int t3y = y;
	int t4x = x;
	int t4y = y;
	switch (d)
	{
	case UU:
		Move(RR, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(LL, &t3x, &t3y);
		Move(LU, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case RR:
		Move(UU, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(DD, &t3x, &t3y);
		Move(RD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case DD:
		Move(LL, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(RR, &t3x, &t3y);
		Move(RD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case LL:
		Move(UU, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(DD, &t3x, &t3y);
		Move(LD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case LU:
		Move(DD, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(RR, &t3x, &t3y);
		Move(RU, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case RU:
		Move(LL, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(DD, &t3x, &t3y);
		Move(RD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case RD:
		Move(UU, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(LL, &t3x, &t3y);
		Move(LD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	case LD:
		Move(UU, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { return true; }
		Move(RR, &t3x, &t3y);
		Move(RD, &t4x, &t4y);
		if (isWall(t3x, t3y) && !isWall(t4x, t4y) && !OutofRange(t4x, t4y)) { return true; }
		break;
	default:
		break;
	}
	return false;
}

bool JPS::isLeftCorner(int direction, int x, int y, int* outDir)
{
	JPSDirection d = (JPSDirection)direction;
	int t1x = x;
	int t1y = y;
	int t2x = x;
	int t2y = y;
	switch (d)
	{
	case UU:
		Move(LL, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LU; return true; }
		break;
	case RR:
		Move(UU, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RU; return true; }
		break;
	case DD:
		Move(RR, &t1x, &t1y);
		Move(RD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RD; return true; }
		break;
	case LL:
		Move(DD, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LD; return true; }
		break;
	case LU:
		Move(DD, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LD; return true; }
		break;
	case RU:
		Move(LL, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LU; return true; }
		break;
	case RD:
		Move(UU, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RU; return true; }
		break;
	case LD:
		Move(RR, &t1x, &t1y);
		Move(RD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RD; return true; }
		break;
	default:
		break;
	}
	return false;
}

bool JPS::isRightCorner(int direction, int x, int y, int* outDir)
{
	JPSDirection d = (JPSDirection)direction;
	int t1x = x;
	int t1y = y;
	int t2x = x;
	int t2y = y;
	switch (d)
	{
	case UU:
		Move(RR, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RU; return true; }
		break;
	case RR:
		Move(DD, &t1x, &t1y);
		Move(RD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RD; return true; }
		break;
	case DD:
		Move(LL, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LD; return true; }
		break;
	case LL:
		Move(UU, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LU; return true; }
		break;
	case LU:
		Move(RR, &t1x, &t1y);
		Move(RU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RU; return true; }
		break;
	case RU:
		Move(DD, &t1x, &t1y);
		Move(RD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = RD; return true; }
		break;
	case RD:
		Move(LL, &t1x, &t1y);
		Move(LD, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LD; return true; }
		break;
	case LD:
		Move(UU, &t1x, &t1y);
		Move(LU, &t2x, &t2y);
		if (isWall(t1x, t1y) && !isWall(t2x, t2y) && !OutofRange(t2x, t2y)) { *outDir = LU; return true; }
		break;
	default:
		break;
	}
	return false;
}

int JPS::GetDirection(JPSNode * target)
{
	if (target == nullptr) { return  -1; }
	if (target->parent == nullptr) { return -1; }

	int dx, dy, direct;
	dx = target->x - target->parent->x; // 음수:왼쪽 0: 동일수직 양수:오른쪽
	dy = target->y - target->parent->y; // 음수:위 0: 동일수평 양수: 아래

	if (dx < 0 && dy < 0) // 좌상
	{
		direct = LU;
	}
	else if (dx == 0 && dy < 0) // 상
	{
		direct = UU;
	}
	else if (dx > 0 && dy < 0) // 우상
	{
		direct = RU;
	}
	else if (dx < 0 && dy == 0) // 좌
	{
		direct = LL;
	}
	else if (dx > 0 && dy == 0) // 우
	{
		direct = RR;
	}
	else if (dx < 0 && dy > 0) // 좌하
	{
		direct = LD;
	}
	else if (dx == 0 && dy > 0) // 하
	{
		direct = DD;
	}
	else if (dx > 0 && dy > 0) // 우하
	{
		direct = RD;
	}
	else // 같은좌표
	{
		direct = -1;
	}

	return direct;
}


bool JPS::isWall(int x, int y)
{
	list<JPSNode*>::iterator iter;
	for (iter = walllist.begin(); iter != walllist.end(); ++iter)
	{
		if ((*iter)->x == x && (*iter)->y == y)
		{
			return true;
		}
	}
	return false;
}

JPSNode* JPS::CreateNodeInOpen(JPSNode* parent, int x, int y, int direct)
{
	JPSNode* node = nullptr;
	bool already = false;
	list<JPSNode*>::iterator iter;
	for (iter = openlist.begin(); iter != openlist.end(); ++iter)
	{
		if (x == (*iter)->x && y == (*iter)->y)
		{
			node = (*iter);
			return node;
		}
	}
	for (iter = closelist.begin(); iter != closelist.end(); ++iter)
	{
		if (x == (*iter)->x &&y == (*iter)->y)
		{
			already = true;
			break;
		}
	}

	if (already)
	{
		return nullptr;
	}
	else
	{
		node = new JPSNode(parent, x, y, direct);
		openlist.push_front(node);
		//노드 매니저
		nodeManager.push_back(node);
		return node;
	}
}

void JPS::InsertToOpen(JPSNode * target)
{
	list<JPSNode*>::iterator iter;
	JPSNode* node = nullptr;
	for (iter = openlist.begin(); iter != openlist.end(); ++iter)
	{
		if (target == (*iter))
		{
			node = target;
		}
	}

	if (node == nullptr)
	{
		openlist.push_back(target);
	}
}

JPSNode * JPS::RemoveToOpen(JPSNode* target)
{
	list<JPSNode*>::iterator iter;
	for (iter = openlist.begin(); iter != openlist.end(); ++iter)
	{
		if (target == (*iter))
		{
			iter = openlist.erase(iter);
			break;
		}
	}
	return target;
}

JPSNode * JPS::MinFInOpen(int sx, int sy, int ex, int ey)
{
	JPSNode* target = nullptr;
	list<JPSNode*>::iterator iter;
	for (iter = openlist.begin(); iter != openlist.end(); ++iter)
	{
		if (target == nullptr)
		{
			target = (*iter);
			continue;
		}
		if (target->F(sx, sy, ex, ey) > (*iter)->F(sx, sy, ex, ey))
		{
			target = (*iter);
			continue;
		}
	}
	return target;
}

void JPS::InsertToClose(JPSNode * target)
{
	list<JPSNode*>::iterator iter;
	JPSNode* node = nullptr;
	for (iter = closelist.begin(); iter != closelist.end(); ++iter)
	{
		if (target == (*iter))
		{
			node = target;
		}
	}

	if (node == nullptr)
	{
		closelist.push_back(target);
	}
}

JPSNode * JPS::RemoveToClose(JPSNode * target)
{
	list<JPSNode*>::iterator iter;
	for (iter = closelist.begin(); iter != closelist.end(); ++iter)
	{
		if (target == (*iter))
		{
			iter = closelist.erase(iter);
			break;
		}
	}
	return target;
}

void JPS::InsertToPath(JPSNode * target)
{
	if (target == nullptr) { return; }
	JPSNode* node = (JPSNode*)target;
	for (;;)
	{
		pathlist.push_front(node);
		node = node->parent;
		if (node == nullptr) { break; }
	}
}

void JPS::DeleteAllGarbageNode()
{
	list<JPSNode*>::iterator iter;
	JPSNode* target;
	for (iter = nodeManager.begin(); iter != nodeManager.end();)
	{
		if (sNode != nullptr)
		{
			if ((*iter) == sNode)
			{
				iter = nodeManager.erase(iter);
				continue;
			}
		}
		target = (JPSNode*)(*iter);
		delete target;
		target = nullptr;
		++iter;

	}

	nodeManager.clear();
}
