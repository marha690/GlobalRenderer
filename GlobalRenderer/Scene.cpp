#include "pch.h"
#include "Scene.h"



// Constructor
Scene::Scene()
{
	//Initialize the triangles for the room.
	{
		myColor white = myColor(255, 255, 255);
		myColor black= myColor(2, 2, 2);

		myColor green = myColor(0, 155, 0);
		myColor lightGreen = myColor(0, 255, 0);
		myColor blue = myColor(0, 0, 155);
		myColor lightBlue = myColor(0, 0, 255);
		myColor red = myColor(155, 0, 0);
		myColor lightRed = myColor(255, 0, 0);

		myColor pink = myColor(255, 192, 203);
		myColor cyan = myColor(153, 230, 179);
		myColor sponge = myColor(253, 254, 3);
		myColor mossgreen = myColor(53, 94, 59);


		//						v1					v2					v3			normal			color
		// room[i] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		//Roof
		room[0] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[1] = Triangle(Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[2] = Triangle(Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[3] = Triangle(Vertex(10, -6, 5), Vertex(13, 0, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[4] = Triangle(Vertex(0, -6, 5), Vertex(10, -6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);
		room[5] = Triangle(Vertex(-3, 0, 5), Vertex(0, -6, 5), Vertex(8, 0, 5), Vertex(0, 0, -1), white);

		//Floor
		room[6] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[7] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[8] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[9] = Triangle(Vertex(10, -6, -5), Vertex(13, 0, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[10] = Triangle(Vertex(0, -6, -5), Vertex(10, -6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);
		room[11] = Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(8, 0, -5), Vertex(0, 0, 1), white);

		//Walls
		room[12] = Triangle(Vertex(0, -6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(-2, -1, 0), red);
		room[13] = Triangle(Vertex(0, -6, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), Vertex(-2, -1, 0), red);

		room[14] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(2, -1, 0), lightRed);
		room[15] = Triangle(Vertex(0, 6, -5), Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(2, -1, 0), lightRed);

		room[16] = Triangle(Vertex(10, -6, -5), Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(0, 1, 0), pink);
		room[17] = Triangle(Vertex(10, -6, -5), Vertex(10, -6, 5), Vertex(0, -6, 5), Vertex(0, 1, 0), pink);

		room[18] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(0, -1, 0), mossgreen);
		room[19] = Triangle(Vertex(10, 6, -5), Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(0, -1, 0), mossgreen);

		room[20] = Triangle(Vertex(13, 0, -5), Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(-2, 1, 0), cyan);
		room[21] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, -6, 5), Vertex(-2, 1, 0), cyan);

		room[22] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(2, 1, 4), sponge);
		room[23] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(2, 1, 4), sponge);
	}
}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{

	int counter= 0;
	for (int i = 0; i < 24; i++) {
		Vertex triangle;
		bool isRayHitting = room[i].rayIntersection(*ray, triangle);

		if (isRayHitting) {
			ray->color = room[i].color;
			counter++;
		}
	}

	if (counter == 0) {
		std::cerr << "Error! Ray missed room triangles!\n";
	}

}