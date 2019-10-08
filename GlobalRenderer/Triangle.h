#pragma once

#include <iostream> //for debugging messages
#include "Vertex.h"
#include "myColor.h"
#include "Ray.h"

//Forward declaration.
class Ray;

class Triangle
{
public:

	// Variables
	Vertex v1, v2, v3; // corners of the triangle
	myColor color;
	Vertex normal;

	//Constructor
	Triangle();
	Triangle(Vertex _v1, Vertex _v2, Vertex _v3, Vertex _normal, myColor _color = myColor(255, 0, 0));


	//Distructor
	~Triangle();

	// rayIntersection. Computes the intersection between a Ray and the Triangle with Möller-Trumbore alghorithm.
	bool rayIntersection(Ray &r, Vertex &hitTriangle);
private:
	double EPSILON = 0.0000001;
};