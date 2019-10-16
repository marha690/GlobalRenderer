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
	Lightsource lightsource;
	Room room;

	//Constructor
	Scene();

	//Destructor
	~Scene();

	//Intersection
	void intersection(Ray *ray);

	bool isIntersected(Ray *ray);

	Color getDiffuseLightContribution(const Vertex & point, const Direction & normal);

private:
	Color white = Color(255, 255, 255);
	Color black = Color(2, 2, 2);

	Color green = Color(0, 155, 0);
	Color lightGreen = Color(0, 255, 0);
	Color blue = Color(0, 0, 155);
	Color lightBlue = Color(0, 0, 255);
	Color red = Color(155, 0, 0);
	Color lightRed = Color(255, 0, 0);

	Color pink = Color(255, 192, 203);
	Color cyan = Color(153, 230, 179);
	Color sponge = Color(253, 254, 3);
	Color mossgreen = Color(53, 94, 59);
};