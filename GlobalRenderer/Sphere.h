#pragma once

#include "Ray.h"
#include "Vertex.h"
#include "myColor.h"

class myColor;

class Sphere
{
public: //Variables
	double radius = 0.5;
	Vertex center;
	myColor color;

public: //Functions
	Sphere();
	Sphere(Vertex _center, myColor _c);
	~Sphere();
	void transform(Vertex tr);
	void transform(double x, double y, double z);

	bool rayIntersection(Ray & r, Vertex & intersectionPoint, double &scalar);
};

