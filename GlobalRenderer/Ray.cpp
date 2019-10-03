#include "pch.h"
#include "Ray.h"


Vertex Ray::getDirection()
{
	return (end - start);
}

Ray::Ray(Vertex _startPoint, Vertex _endPoint)
{
	start = _startPoint;
	end = _endPoint;
	color = myColor(250, 0, 250);
}

Ray::~Ray()
{
}



void Ray::print()
{
	std::cout << (end - start).x << ", " << (end - start).y << ", " << (end - start).z << "\n";
}