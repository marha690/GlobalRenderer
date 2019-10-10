#pragma once

#include "myColor.h"
#include "Triangle.h"
#include "Ray.h"

class Lightsource
{
	//Constructor & destructor
public:
	Lightsource(Vertex p0, Vertex p1, Vertex p2, Vertex p3);
	~Lightsource();

	//Variables
public:
	MyColor lightColor;
private:
	Vertex v0, v1, v2, v3;
	Triangle triangles[2];
	MyColor whiteLight = MyColor(255, 255, 255);
	
	//Functions
public:
	bool rayInterSection(Ray &ray);
};

