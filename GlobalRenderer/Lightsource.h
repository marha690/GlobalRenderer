#pragma once

#include "myColor.h"
#include "Triangle.h"
#include "Ray.h"

class Lightsource
{
	//Constructor & destructor
public:
	Lightsource() = default;
	Lightsource(Vertex pos);
	~Lightsource();

	//Variables
public:
	MyColor color;
	Vertex position;
private:
	Vertex v0, v1, v2, v3;
	Triangle triangles[2];

	double L0 = 500;
	MyColor whiteLight = MyColor(L0, L0, L0);
	
	//Functions
public:
	bool rayInterSection(Ray &ray);
};

