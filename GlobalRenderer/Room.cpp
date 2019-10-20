#include "pch.h"
#include "Room.h"


Room::Room()
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

//Roof
	std::cout << "Init room!" << std::endl;
	room[0] = Triangle(Vertex(0, 6, 5, 1), Vertex(8, 0, 5, 1), Vertex(-3, 0, 5, 1), white);
	room[1] = Triangle(Vertex(10, 6, 5, 1), Vertex(8, 0, 5, 1), Vertex(0, 6, 5, 1), white);
	room[2] = Triangle(Vertex(13, 0, 5, 1), Vertex(8, 0, 5, 1), Vertex(10, 6, 5, 1), white);
	room[3] = Triangle(Vertex(10, -6, 5, 1), Vertex(8, 0, 5, 1), Vertex(13, 0, 5, 1), white);
	room[4] = Triangle(Vertex(0, -6, 5, 1), Vertex(8, 0, 5, 1), Vertex(10, -6, 5, 1), white);
	room[5] = Triangle(Vertex(-3, 0, 5, 1), Vertex(8, 0, 5, 1), Vertex(0, -6, 5, 1), white);

	//Floor
	room[6] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, -5, 1), Vertex(8, 0, -5, 1), white);
	room[7] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, -5, 1), Vertex(8, 0, -5, 1), white);
	room[8] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, -5, 1), Vertex(8, 0, -5, 1), white);
	room[9] = Triangle(Vertex(10, -6, -5, 1), Vertex(13, 0, -5, 1), Vertex(8, 0, -5, 1), white);
	room[10] = Triangle(Vertex(0, -6, -5, 1), Vertex(10, -6, -5, 1), Vertex(8, 0, -5, 1), white);
	room[11] = Triangle(Vertex(-3, 0, -5, 1), Vertex(0, -6, -5, 1), Vertex(8, 0, -5, 1), white);

	//Walls
	room[12] = Triangle(Vertex(0, -6, -5, 1), Vertex(-3, 0, -5, 1), Vertex(-3, 0, 5, 1), red);
	room[13] = Triangle(Vertex(0, -6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(0, -6, 5, 1), red);

	room[14] = Triangle(Vertex(0, 6, -5, 1), Vertex(-3, 0, 5, 1), Vertex(-3, 0, -5, 1), lightRed);
	room[15] = Triangle(Vertex(0, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(-3, 0, 5, 1), lightRed);

	room[16] = Triangle(Vertex(10, -6, -5, 1), Vertex(0, -6, -5, 1), Vertex(0, -6, 5, 1), pink);
	room[17] = Triangle(Vertex(10, -6, -5, 1), Vertex(0, -6, 5, 1), Vertex(10, -6, 5, 1), pink);

	room[18] = Triangle(Vertex(10, 6, -5, 1), Vertex(0, 6, 5, 1), Vertex(0, 6, -5, 1), mossgreen);
	room[19] = Triangle(Vertex(10, 6, -5, 1), Vertex(10, 6, 5, 1), Vertex(0, 6, 5, 1), mossgreen);

	room[20] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, -6, -5, 1), Vertex(10, -6, 5, 1), cyan);
	room[21] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, -6, 5, 1), Vertex(13, 0, 5, 1), cyan);

	room[22] = Triangle(Vertex(13, 0, -5, 1), Vertex(10, 6, 5, 1), Vertex(10, 6, -5, 1), sponge);
	room[23] = Triangle(Vertex(13, 0, -5, 1), Vertex(13, 0, 5, 1), Vertex(10, 6, 5, 1), sponge);

}


Room::~Room()
{
}


bool Room::rayIntersection(Ray &r) {
	bool hit = false;

	for (int i = 0; i < 24; i++) {
		if (room[i].rayIntersection(r)) {
			r.setSurfaceType(Surface::diffuse);
			hit = true;
		}
	}

	return hit;
}