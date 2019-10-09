#pragma once

#include "Triangle.h"
#include <cmath>

class Tetrahedron
{
	//Variables
public:

	Triangle triangles[4];
private:
	myColor lightRed = myColor(255, 0, 0);
	myColor lightGreen = myColor(0, 255, 0);
	myColor lightBlue = myColor(0, 0, 255);
	myColor h = myColor(0, 255, 255);

	Vertex v0 = Vertex(0, 0, 0);
	Vertex v1 = Vertex(0, 0, 2);
	Vertex v2 = Vertex(0, std::sqrt(3), 1);
	Vertex v3 = Vertex(-std::sqrt(3), 1 / std::sqrt(3), 1);

	//Functions
public:
	Tetrahedron();
	~Tetrahedron();

	bool rayIntersection(Ray & r, Vertex & intersectionPoint, int &triangleIndex);

	void transform(double x, double y, double z);
};

