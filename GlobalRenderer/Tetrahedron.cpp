#include "pch.h"
#include "Tetrahedron.h"

//Constructor
Tetrahedron::Tetrahedron()
{
	triangles[0] = Triangle(v0,v1,v2, Vertex(0, 1, 1), lightRed);
	triangles[1] = Triangle(v1,v2,v3, Vertex(0, 0, 0), lightBlue);
	triangles[2] = Triangle(v2,v3,v0, Vertex(1, 1, 0), lightGreen);
	triangles[3] = Triangle(v3,v0,v1, Vertex(1, 0, 1), h);
}

Tetrahedron::~Tetrahedron()
{
}

bool Tetrahedron::rayIntersection(Ray &r, Vertex &intersectionPoint, int &triangleIndex) {
	Vertex hitPos;
	double t = 99999999999; //Max length from camera to render.
	bool hit = false;

	for (int i = 0; i < 4; i++) {
		double temp = 0;
		if (triangles[i].rayIntersection(r, hitPos, temp)) {
			if (temp < t && temp > 0) {
				intersectionPoint = hitPos;
				triangleIndex = i;
				hit = true;
			}
		}
	}
	return hit;
}

void Tetrahedron::transform(double x, double y, double z) 
{

	v0 = v0 + Vertex(x, y, z);
	v1 = v1 + Vertex(x, y, z);
	v2 = v2 + Vertex(x, y, z);
	v3 = v3 + Vertex(x, y, z);

	triangles[0] = Triangle(v0, v1, v2, triangles[0].normal, triangles[0].color);
	triangles[1] = Triangle(v1, v2, v3, triangles[0].normal, triangles[1].color);
	triangles[2] = Triangle(v2, v3, v0, triangles[0].normal, triangles[2].color);
	triangles[3] = Triangle(v3, v0, v1, triangles[0].normal, triangles[3].color);
}
