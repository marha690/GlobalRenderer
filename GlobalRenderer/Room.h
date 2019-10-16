#pragma once

#include "Triangle.h"
class Room
{
public:
	Room();
	~Room();

	bool rayIntersection(Ray & r);

	Triangle room[24];
	Color color;
};

