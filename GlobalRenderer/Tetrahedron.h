#pragma once

#include "Triangle.h"
#include <cmath>

class Tetrahedron
{
	//Variables
public:

	Triangle triangles[4];
private:
	myColor color;
	Vertex v0 = Vertex(0, 0, 0);
	Vertex v1 = Vertex(0, 0, 2);
	Vertex v2 = Vertex(0, std::sqrt(3), 1);
	Vertex v3 = Vertex(-std::sqrt(3), 1 / std::sqrt(3), 1);

	//Functions
public:
	Tetrahedron();
	Tetrahedron(Vertex pos, myColor _color);
	~Tetrahedron();

	bool rayIntersection(Ray & r, Vertex & intersectionPoint, int &triangleIndex, double &_scalar);

	void transform(Vertex ppos);
	void transform(double x, double y, double z);
};

