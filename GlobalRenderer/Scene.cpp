#include "pch.h"
#include "Scene.h"
#include "Sphere.h"
#include "Room.h"
// Constructor
Scene::Scene()
{
	room = Room();

	tetrahedron = Tetrahedron(Vertex(5, 2, 0, 1), lightRed);

	sphere = Sphere(Vertex(4, -2, -2, 1), 1.5, lightGreen);

	lightsource = Lightsource(Vertex(5, 0, 5, 1));
}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{
	//Room
	room.rayIntersection(*ray);

	//Tetrahedron
	tetrahedron.rayIntersection(*ray);

	//Sphere
	sphere.rayIntersection(*ray);

}

bool Scene::isIntersected(Ray *ray)
{
	//Room
	if (room.rayIntersection(*ray))
		return true;

	//Tetrahedron
	if (tetrahedron.rayIntersection(*ray))
		return true;

	//Sphere
	if (sphere.rayIntersection(*ray))
		return true;

	return false;
}

Color Scene::getDiffuseLightContribution(const Vertex &point, const Direction &normal)
{
	return Color(0, 0, 0);
}
