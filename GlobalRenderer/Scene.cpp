#include "pch.h"
#include "Scene.h"



// Constructor
Scene::Scene()
{
	//Initialize the triangles for the room.
	{
		myColor white = myColor(255, 255, 255);
		myColor black= myColor(2, 2, 2);
		myColor green = myColor(0, 255, 0);
		myColor lightGreen = myColor(0, 155, 0);
		myColor blue = myColor(0, 0, 255);
		myColor lightBlue = myColor(0, 0, 155);
		myColor red = myColor(255, 0, 0);
		myColor lightRed = myColor(155, 0, 0);

		//Roof
		room[0] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[1] = Triangle(Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), black);
		room[2] = Triangle(Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[3] = Triangle(Vertex(10, -6, 5), Vertex(13, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), black);
		room[4] = Triangle(Vertex(0, -6, 5), Vertex(10, -6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[5] = Triangle(Vertex(-3, 0, 5), Vertex(0, -6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), black);

		//Floor
		room[6] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[7] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), black);
		room[8] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[9] = Triangle(Vertex(10, -6, -5), Vertex(13, 0, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), black);
		room[10] = Triangle(Vertex(0, -6, -5), Vertex(10, -6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[11] = Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), black);

		//Walls
		room[12] = Triangle(Vertex(0, -6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(-2, -1, 0), green);
		room[13] = Triangle(Vertex(0, -6, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), Vertex(-2, -1, 0), lightGreen);

		room[14] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(2, -1, 0), blue);
		room[15] = Triangle(Vertex(0, 6, -5), Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(2, -1, 0), lightBlue);

		room[16] = Triangle(Vertex(10, -6, -5), Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(0, 1, 0), green);
		room[17] = Triangle(Vertex(10, -6, -5), Vertex(10, -6, 5), Vertex(0, -6, 5), Vertex(0, 1, 0), lightGreen);

		room[18] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(0, -1, 0), blue);
		room[19] = Triangle(Vertex(10, 6, -5), Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(0, -1, 0), lightBlue);

		room[20] = Triangle(Vertex(13, 0, -5), Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(-2, 1, 0), green);
		room[21] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, -6, 5), Vertex(-2, 1, 0), lightGreen);

		room[22] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(2, 1, 4), blue);
		room[23] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(2, 1, 4), lightBlue);
	}

}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{
	//std::cout << "Ray direction: "; ray->getDirection().print();
	//For each triangle in room, check which triangle it hits.

	int counter= 0;
	for (int i = 0; i < 24; i++) {
		bool isRayHitting = false;
		Vertex triangle = room[i].rayIntersection(*ray, isRayHitting);

		if (isRayHitting) {
			ray->color = room[i].color;
			counter++;
		}
	}

	if (counter == 0) {
		std::cerr << "Error! Ray missed room triangles!\n";
	}

}