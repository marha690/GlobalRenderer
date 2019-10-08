#pragma once


#include "Vertex.h"
#include "Triangle.h"
#include "myColor.h"

class Triangle;

class Ray
{
public:

	//Variables.
	Vertex start;
	Vertex end;
	myColor color;

	Triangle *hitTriangle;

	Vertex getDirection();

	//Constructor
	Ray(Vertex _startPoint, Vertex _endPoint);

	void print();
	friend std::ostream& operator<<(std::ostream& os, const Ray& v);
	//Destructor
	~Ray();
};