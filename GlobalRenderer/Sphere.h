#pragma once

#include "Ray.h"
#include "Vertex.h"
#include "MyColor.h"

class MyColor;

class Sphere
{
public:
	//Constructors & destructors
	Sphere();
	Sphere(Vertex _center, double _radius, MyColor _c);
	~Sphere();

	//Variables
private:
	Vertex center;
	double radius = 0.5;
	MyColor color;
	
	//Getters
public:
	MyColor getColor() { return color; }

	//Functions
public: 
	bool rayIntersection(Ray & r);
	void transform(Vertex tr);
	void transform(double x, double y, double z);
};

