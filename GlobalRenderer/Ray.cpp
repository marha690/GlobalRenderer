#include "pch.h"
#include "Ray.h"


//Constructor
Ray::Ray(Vertex _startPoint, Vertex _endPoint)
{
	start = _startPoint;
	end = _endPoint;
	color = Color(250, 0, 250);
}


//Destructor
Ray::~Ray()
{
}



void Ray::print()
{
	std::cout << (end - start).x << ", " << (end - start).y << ", " << (end - start).z << "\n";
}



std::ostream& operator<<(std::ostream& os, const Ray& v)
{
	os << (v.end - v.start).x << ", " << (v.end - v.start).y << ", " << (v.end - v.start).z << "\n";
	return os;
}