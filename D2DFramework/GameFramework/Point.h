#pragma once
struct Point
{
	Point() {}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator<(const Point& other) const
	{
		if (this->y != other.y)
		{
			return this->y < other.y;
		}
		return this->x < other.x;
	}
	int x = 0;
	int y = 0;
};

struct TableIndex
{
	TableIndex() {}
	TableIndex(int row, int col)
	{
		this->row = row;
		this->col = col;
	}
	bool operator<(const TableIndex& other) const
	{
		if (this->row != other.row)
		{
			return this->row < other.row;
		}
		return this->col < other.col;
	}
	int row = 0;
	int col = 0;
};
