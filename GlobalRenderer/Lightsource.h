#pragma once

#include "Triangle.h"
#include "Ray.h"
#include "Definitions.h"

class Lightsource
{
	//Constructor & destructor
public:
	Lightsource() = default;
	Lightsource(Vertex pos);
	~Lightsource();

	//Variables
public:
	Color color;
	Vertex position;
	double L0 = 10;
private:
	Vertex v0, v1, v2, v3;
	Triangle triangles[2];

	Color whiteLight = Color(L0, L0, L0);
	
	//Functions
public:
	bool rayInterSection(Ray &ray);
};

