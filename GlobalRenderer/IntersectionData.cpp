#include "pch.h"
#include "IntersectionData.h"



IntersectionData::IntersectionData(Vertex p, Direction n, Surface s)
{
	normal = n;
	point = p;
	sufaceType = s;
}

IntersectionData::~IntersectionData()
{
}
