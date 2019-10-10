#pragma once

#include <iostream> //for debugging messages
#include "Vertex.h"
#include "MyColor.h"
#include "Ray.h"

//Forward declaration.
class Ray;

class Triangle
{
	//Constructors & destructors
public:
	Triangle();
	Triangle(Vertex _v0, Vertex _v1, Vertex _v2, MyColor _color = MyColor(255, 0, 0));
	~Triangle();

	// Variables
private:
	Vertex v0, v1, v2; // corners of the triangle
	MyColor color;
	Vertex normal;

	double EPSILON = 0.0000001;
	//Setters
public:

	void setColor(MyColor c) { color = c; }
	void setNormal(Vertex v0,Vertex v1,Vertex v2);
	//Getters
public:
	Vertex getNormal() { return normal; }
	MyColor getColor() { return color; }

	//Other Functions
public:
	// rayIntersection. Computes the intersection between a Ray and the Triangle with Möller-Trumbore alghorithm.
	bool rayIntersection(Ray &r);
};