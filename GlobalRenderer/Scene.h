#pragma once

#include "Triangle.h"
#include "Ray.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "Room.h"
#include "LightSource.h"

//Forward declaration
class Trinagle;

class Scene
{
public:

	//Variables
	Tetrahedron tetrahedron;
	Sphere sphere;
	Sphere sphere2;
	Sphere sphere3;
	Lightsource lightsource;
	Room room;

	//Constructor
	Scene();

	//Destructor
	~Scene();

	//Intersection
	void intersection(Ray *ray);

	//Return true if something intersects. Usefull for shadow rays.
	bool isIntersected(Ray *ray);

	Color tracePath(Ray * ray);

private:
	Color getLightContribution(Vertex rayEnd, Direction surfaceNormal);
};

