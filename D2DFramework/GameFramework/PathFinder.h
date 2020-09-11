#pragma once

template <class Finder>
class PathFinder
{
public:
	PathFinder()
	{
		pFinder = new Finder;
	}
	~PathFinder()
	{
		delete pFinder;
	}

	void SetMapSize(int l, int t, int r, int b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	void SetStartPos(int x, int y)
	{
		sx = x;
		sy = y;
	}


private:
	Finder* pFinder = nullptr;
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;

	int sx = 0;
	int sy = 0;
};

