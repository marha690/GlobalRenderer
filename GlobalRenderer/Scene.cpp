#include "pch.h"
#include "Scene.h"
#include "Sphere.h"

// Constructor
Scene::Scene()
{
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

	//Initialize the triangles for the room.
	{

		//						v1					v2					v3			normal			color
		// room[i] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		//Roof
		room[0] = Triangle(Vertex(0, 6, 5, 1), Vertex(-3, 0, 5, 1), Vertex(8, 0, 5, 1), white);
		room[1] = Triangle(Vertex(10, 6, 5, 1), Vertex(0, 6, 5, 1), Vertex(8, 0, 5, 1), white);
		room[2] = Triangle(Vertex(13, 0, 5, 1), Vertex(10, 6, 5, 1), Vertex(8, 0, 5, 1), white);
		room[3] = Triangle(Vertex(10, -6, 5, 1), Vertex(13, 0, 5, 1), Vertex(8, 0, 5, 1), white);
		room[4] = Triangle(Vertex(0, -6, 5, 1), Vertex(10, -6, 5, 1), Vertex(8, 0, 5, 1), white);
		room[5] = Triangle(Vertex(-3, 0, 5, 1), Vertex(0, -6, 5, 1), Vertex(8, 0, 5, 1), white);

		//Floor
		room[6] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, -5, 1), Vertex(8, 0, -5, 1), white);
		room[7] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, -5, 1), Vertex(8, 0, -5, 1), white);
		room[8] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, -5, 1), Vertex(8, 0, -5, 1), white);
		room[9] = Triangle(Vertex(10, -6, -5, 1), Vertex(13, 0, -5, 1), Vertex(8, 0, -5, 1), white);
		room[10] = Triangle(Vertex(0, -6, -5, 1), Vertex(10, -6, -5, 1), Vertex(8, 0, -5, 1), white);
		room[11] = Triangle(Vertex(-3, 0, -5, 1), Vertex(0, -6, -5, 1), Vertex(8, 0, -5, 1), white);

		//Walls
		room[12] = Triangle(Vertex(0, -6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(-3, 0, -5, 1), red);
		room[13] = Triangle(Vertex(0, -6, -5, 1), Vertex(0, -6, 5, 1), Vertex(-3, 0, 5, 1), red);

		room[14] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(-3, 0, -5, 1), lightRed);
		room[15] = Triangle(Vertex(0, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(-3, 0, 5, 1), lightRed);

		room[16] = Triangle(Vertex(10, -6, -5, 1), Vertex(0, -6, 5, 1), Vertex(0, -6, -5, 1), pink);
		room[17] = Triangle(Vertex(10, -6, -5, 1), Vertex(10, -6, 5, 1), Vertex(0, -6, 5, 1), pink);

		room[18] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(0, 6, -5, 1), mossgreen);
		room[19] = Triangle(Vertex(10, 6, -5, 1), Vertex(10, 6, 5, 1), Vertex(0, 6, 5, 1), mossgreen);

		room[20] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, -6, 5, 1), Vertex(10, -6, -5, 1), cyan);
		room[21] = Triangle(Vertex(13, 0, -5, 1), Vertex(13, 0, 5, 1), Vertex(10, -6, 5, 1), cyan);

		room[22] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, 5, 1), Vertex(10, 6, -5, 1), sponge);
		room[23] = Triangle(Vertex(13, 0, -5, 1), Vertex(13, 0, 5, 1), Vertex(10, 6, 5, 1), sponge);
	}

	tetrahedron = Tetrahedron(Vertex(6, -1, -1, 1), lightRed);

	sphere = Sphere(Vertex(5, 1, 0, 1), 0.5, lightBlue);

	lightsource = Lightsource(Vertex(5, 0, 5, 1));
}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{
	//Room
	for (int i = 0; i < 24; i++) {
		room[i].rayIntersection(*ray);
	}
	//Tetrahedron
	tetrahedron.rayIntersection(*ray);

	//Sphere
	sphere.rayIntersection(*ray); //Returns null for hit triangle!
}

bool Scene::isIntersected(Ray *ray)
{
	//Room
	for (int i = 0; i < 24; i++) {
		if (room[i].rayIntersection(*ray))
			return true;
	}

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
