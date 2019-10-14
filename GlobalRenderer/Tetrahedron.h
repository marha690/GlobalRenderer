#pragma once

#include "Triangle.h"
#include <cmath>

class Tetrahedron
{
public:
	//Constructors & destructors
	Tetrahedron();
	Tetrahedron(Vertex pos, Color _color);
	~Tetrahedron();

	//Variables
public:
	Triangle triangles[4];
private:
	Color color;
	Vertex v0 = Vertex(0, 0, 0, 1);
	Vertex v1 = Vertex(0, 0, 2, 1);
	Vertex v2 = Vertex(0, std::sqrt(3), 1, 1);
	Vertex v3 = Vertex(-std::sqrt(3), 1 / std::sqrt(3), 1, 1);

	//Functions
public:
	bool rayIntersection(Ray & r);
	void transform(Vertex pos);
	void transform(double x, double y, double z);
};

