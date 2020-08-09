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

