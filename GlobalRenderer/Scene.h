#pragma once

#include "Triangle.h"
#include "Ray.h"
#include "Tetrahedron.h"

//Forward declaration
class Trinagle;

class Scene
{
public:

	//Variables
	Triangle room[24];
	Tetrahedron tetrahedron;

	//Constructor
	Scene();

	//Destructor
	~Scene();

	//Intersection
	void intersection(Ray *ray);

	void intersections();
};