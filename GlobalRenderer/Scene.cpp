#include "pch.h"
#include "Scene.h"
#include "Sphere.h"

// Constructor
Scene::Scene()
{
	MyColor white = MyColor(255, 255, 255);
	MyColor black = MyColor(2, 2, 2);

	MyColor green = MyColor(0, 155, 0);
	MyColor lightGreen = MyColor(0, 255, 0);
	MyColor blue = MyColor(0, 0, 155);
	MyColor lightBlue = MyColor(0, 0, 255);
	MyColor red = MyColor(155, 0, 0);
	MyColor lightRed = MyColor(255, 0, 0);

	MyColor pink = MyColor(255, 192, 203);
	MyColor cyan = MyColor(153, 230, 179);
	MyColor sponge = MyColor(253, 254, 3);
	MyColor mossgreen = MyColor(53, 94, 59);

	//Initialize the triangles for the room.
	{

		//						v1					v2					v3			normal			color
		// room[i] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		//Roof
		room[0] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), white);
		room[1] = Triangle(Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(8, 0, 5), white);
		room[2] = Triangle(Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(8, 0, 5), white);
		room[3] = Triangle(Vertex(10, -6, 5), Vertex(13, 0, 5), Vertex(8, 0, 5), white);
		room[4] = Triangle(Vertex(0, -6, 5), Vertex(10, -6, 5), Vertex(8, 0, 5), white);
		room[5] = Triangle(Vertex(-3, 0, 5), Vertex(0, -6, 5), Vertex(8, 0, 5), white);

		//Floor
		room[6] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, -5), Vertex(8, 0, -5), white);
		room[7] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, -5), Vertex(8, 0, -5), white);
		room[8] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, -5), Vertex(8, 0, -5), white);
		room[9] = Triangle(Vertex(10, -6, -5), Vertex(13, 0, -5), Vertex(8, 0, -5), white);
		room[10] = Triangle(Vertex(0, -6, -5), Vertex(10, -6, -5), Vertex(8, 0, -5), white);
		room[11] = Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(8, 0, -5), white);

		//Walls
		room[12] = Triangle(Vertex(0, -6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), red);
		room[13] = Triangle(Vertex(0, -6, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), red);

		room[14] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), lightRed);
		room[15] = Triangle(Vertex(0, 6, -5), Vertex(0, 6, 5), Vertex(-3, 0, 5), lightRed);

		room[16] = Triangle(Vertex(10, -6, -5), Vertex(0, -6, 5), Vertex(0, -6, -5), pink);
		room[17] = Triangle(Vertex(10, -6, -5), Vertex(10, -6, 5), Vertex(0, -6, 5), pink);

		room[18] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, 5), Vertex(0, 6, -5), mossgreen);
		room[19] = Triangle(Vertex(10, 6, -5), Vertex(10, 6, 5), Vertex(0, 6, 5), mossgreen);

		room[20] = Triangle(Vertex(13, 0, -5), Vertex(10, -6, 5), Vertex(10, -6, -5), cyan);
		room[21] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, -6, 5), cyan);

		room[22] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, 5), Vertex(10, 6, -5), sponge);
		room[23] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, 6, 5), sponge);
	}

	tetrahedron = Tetrahedron(Vertex(6, -1, -1), lightRed);

	sphere = Sphere(Vertex(5, 1, 0), 0.5, lightBlue);

	lightsource = Lightsource(Vertex(5, 0, 5));
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
	if (sphere.rayIntersection(*ray)) //Returns null for hit triangle!
		return true;

	return false;
}
