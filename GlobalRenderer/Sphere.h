#pragma once

#include "Ray.h"
#include "Vertex.h"
#include "Definitions.h"


class Sphere
{
public:
	//Constructors & destructors
	Sphere();
	Sphere(Vertex _center, double _radius, Color _c);
	~Sphere();

	//Variables
private:
	Vertex center;
	double radius = 0.5;
	Color color;
	
	//Getters
public:
	Color getColor() { return color; }

	//Functions
public: 
	bool rayIntersection(Ray & r);
	void transform(Vertex tr);
	void transform(double x, double y, double z);
};

