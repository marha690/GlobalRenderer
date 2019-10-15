#pragma once

#include "Definitions.h"

class IntersectionData
{
public:
	Direction normal;
	Vertex point;
	Surface sufaceType;

	IntersectionData(Vertex p, Direction n, Surface s);
	~IntersectionData();
};

