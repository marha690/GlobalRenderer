#pragma once

#include "Triangle.h"
#include "Ray.h"

//Forward declaration
class Trinagle;

class Scene
{
public:

	//Variables
	Triangle room[24];

	//Constructor
	Scene();

	//Destructor
	~Scene();

	//Intersection
	void intersection(Ray *ray);
};