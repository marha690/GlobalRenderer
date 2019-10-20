#include "pch.h"
#include "Scene.h"
#include "Sphere.h"
#include "Room.h"
// Constructor
Scene::Scene()
{

	tetrahedron = Tetrahedron(Vertex(5, 2, 0, 1), lightRed);

	sphere = Sphere(Vertex(4, -2, -2, 1), 1.5, lightGreen, Surface::specular);

	lightsource = Lightsource(Vertex(5, 0, 4.9, 1));

	sphere2 = Sphere(Vertex(5, 2, -1, 1), 0.5, lightGreen, Surface::diffuse);
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
	sphere2.rayIntersection(*ray);

	//Lightsource
	//lightsource.rayInterSection(*ray);

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
	if (sphere2.rayIntersection(*ray))
		return true;


	return false;
}
