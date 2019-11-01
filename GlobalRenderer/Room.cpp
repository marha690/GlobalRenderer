#include "pch.h"
#include "Room.h"


Room::Room()
{

//Roof
	std::cout << "Init room!" << std::endl;
	room[0] = Triangle(Vertex(0, 6, 5, 1), Vertex(8, 0, 5, 1), Vertex(-3, 0, 5, 1), COLOR::WHITE);
	room[1] = Triangle(Vertex(10, 6, 5, 1), Vertex(8, 0, 5, 1), Vertex(0, 6, 5, 1), COLOR::WHITE);
	room[2] = Triangle(Vertex(13, 0, 5, 1), Vertex(8, 0, 5, 1), Vertex(10, 6, 5, 1), COLOR::WHITE);
	room[3] = Triangle(Vertex(10, -6, 5, 1), Vertex(8, 0, 5, 1), Vertex(13, 0, 5, 1), COLOR::WHITE);
	room[4] = Triangle(Vertex(0, -6, 5, 1), Vertex(8, 0, 5, 1), Vertex(10, -6, 5, 1), COLOR::WHITE);
	room[5] = Triangle(Vertex(-3, 0, 5, 1), Vertex(8, 0, 5, 1), Vertex(0, -6, 5, 1), COLOR::WHITE);

	//Floor
	room[6] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);
	room[7] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);
	room[8] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);
	room[9] = Triangle(Vertex(10, -6, -5, 1), Vertex(13, 0, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);
	room[10] = Triangle(Vertex(0, -6, -5, 1), Vertex(10, -6, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);
	room[11] = Triangle(Vertex(-3, 0, -5, 1), Vertex(0, -6, -5, 1), Vertex(8, 0, -5, 1), COLOR::WHITE);

	//Walls
	room[12] = Triangle(Vertex(0, -6, -5, 1), Vertex(-3, 0, -5, 1), Vertex(-3, 0, 5, 1), COLOR::RED);
	room[13] = Triangle(Vertex(0, -6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(0, -6, 5, 1), COLOR::RED);

	room[14] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(-3, 0, -5, 1), COLOR::LIGHTRED);
	room[15] = Triangle(Vertex(0, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(-3, 0, 5, 1), COLOR::LIGHTRED);

	room[16] = Triangle(Vertex(10, -6, -5, 1), Vertex(0, -6, -5, 1), Vertex(0, -6, 5, 1), COLOR::PINK);
	room[17] = Triangle(Vertex(10, -6, -5, 1), Vertex(0, -6, 5, 1), Vertex(10, -6, 5, 1), COLOR::PINK);

	room[18] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(0, 6, -5, 1), COLOR::MOSSGREEN);
	room[19] = Triangle(Vertex(10, 6, -5, 1), Vertex(10, 6, 5, 1), Vertex(0, 6, 5, 1), COLOR::MOSSGREEN);

	room[20] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, -6, -5, 1), Vertex(10, -6, 5, 1), COLOR::CYAN);
	room[21] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, -6, 5, 1), Vertex(13, 0, 5, 1), COLOR::CYAN);

	room[22] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, 5, 1), Vertex(10, 6, -5, 1), COLOR::SPONGE);
	room[23] = Triangle(Vertex(13, 0, -5, 1), Vertex(13, 0, 5, 1), Vertex(10, 6, 5, 1), COLOR::SPONGE);
}


Room::~Room()
{
}


bool Room::rayIntersection(Ray &r) {
	bool hit = false;

	for (int i = 0; i < 24; i++) {
		if (room[i].rayIntersection(r)) {
			r.setSurfaceType(SurfaceType::Lambertian);
			hit = true;
		}
	}

	return hit;
}