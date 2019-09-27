#include "pch.h"
#include "Scene.h"



// Constructor
Scene::Scene()
{
	//Initialize the triangles for the room.
	{
		//Roof
		room[0] = Triangle(Vertex(0, 6, 5), Vertex(-3, 0, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));
		room[1] = Triangle(Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));
		room[2] = Triangle(Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));
		room[3] = Triangle(Vertex(10, -6, 5), Vertex(13, 0, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));
		room[4] = Triangle(Vertex(0, -6, 5), Vertex(10, -6, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));
		room[5] = Triangle(Vertex(-3, 0, 5), Vertex(0, -6, 5), Vertex(5, 0, 5), Vertex(0, 0, -1), myColor(255, 255, 255));

		//Floor
		room[6] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));
		room[7] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));
		room[8] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));
		room[9] = Triangle(Vertex(10, -6, -5), Vertex(13, 0, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));
		room[10] = Triangle(Vertex(0, -6, -5), Vertex(10, -6, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));
		room[11] = Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(5, 0, -5), Vertex(0, 0, 1), myColor(255, 255, 255));

		//Walls
		room[12] = Triangle(Vertex(0, -6, -5), Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(-2, -1, 0), myColor(0, 0, 255));
		room[13] = Triangle(Vertex(0, -6, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), Vertex(-2, -1, 0), myColor(0, 0, 255));

		room[14] = Triangle(Vertex(0, 6, -5), Vertex(-3, 0, 0), Vertex(-3, 0, -5), Vertex(2, -1, 0), myColor(255, 255, 0));
		room[15] = Triangle(Vertex(0, 6, -5), Vertex(0, 6, 0), Vertex(-3, 0, 0), Vertex(2, -1, 0), myColor(255, 255, 0));

		room[16] = Triangle(Vertex(10, -6, -5), Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(0, 1, 0), myColor(0, 0, 255));
		room[17] = Triangle(Vertex(10, -6, -5), Vertex(10, -6, 5), Vertex(0, -6, 5), Vertex(0, 1, 0), myColor(0, 0, 255));

		room[18] = Triangle(Vertex(10, 6, -5), Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(0, -1, 0), myColor(0, 255, 255));
		room[19] = Triangle(Vertex(10, 6, -5), Vertex(10, 6, 5), Vertex(0, 6, 5), Vertex(0, -1, 0), myColor(0, 255, 255));

		room[20] = Triangle(Vertex(13, 0, -5), Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(-2, 1, 0), myColor(255, 0, 0));
		room[21] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, -6, 5), Vertex(-2, 1, 0), myColor(255, 0, 0));

		room[22] = Triangle(Vertex(13, 0, -5), Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(2, 1, 4), myColor(0, 40, 0));
		room[23] = Triangle(Vertex(13, 0, -5), Vertex(13, 0, 5), Vertex(10, 6, 5), Vertex(2, 1, 4), myColor(0, 40, 0));
	}

	//Set up camera.

}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{
	///std::cout << "Looking for intersections for the ray...\n";
	//For each triangle in room, check which triangle it hits.
	for (int i = 0; i < 24; i++) {
		bool isRayHitting = false;
		Vertex triangle = room[i].rayIntersection(*ray, isRayHitting);

		if (isRayHitting) {
			///std::cout << "It hitted triangle: " << i << "\n";
			ray->color = room[i].color;
			///ray->color.print();
		}
	}
	///std::cout << "No more triangles to check with.\n\n";
}