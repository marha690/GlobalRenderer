#pragma once

#include "Triangle.h"
#include "Ray.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "LightSource.h"

//Forward declaration
class Trinagle;

class Scene
{
public:

	//Variables
	Triangle room[24];
	Tetrahedron tetrahedron;
	Sphere sphere;
	Lightsource lightsource;

	//Constructor
	Scene();

	//Destructor
	~Scene();

	//Intersection
	void intersection(Ray *ray);

	bool isIntersected(Ray *ray);
};