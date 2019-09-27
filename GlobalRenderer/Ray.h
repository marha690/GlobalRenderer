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


	//Constructor
	Ray(Vertex _startPoint, Vertex _endPoint);

	void print();

	//Destructor
	~Ray();
};