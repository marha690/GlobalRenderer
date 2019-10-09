#include "pch.h"
#include "Tetrahedron.h"

//Constructor
Tetrahedron::Tetrahedron()
{
	myColor color = myColor(1, 1, 1);
	triangles[0] = Triangle(v0, v1, v2, Vertex(0, 1, 1), color);
	triangles[1] = Triangle(v1, v2, v3, Vertex(0, 0, 0), color);
	triangles[2] = Triangle(v2, v3, v0, Vertex(1, 1, 0), color);
	triangles[3] = Triangle(v3, v0, v1, Vertex(1, 0, 1), color);
}
Tetrahedron::Tetrahedron(Vertex pos,myColor _color)
{
	triangles[0] = Triangle(v0,v1,v2, Vertex(0, 1, 1), _color);
	triangles[1] = Triangle(v1,v2,v3, Vertex(0, 0, 0), _color);
	triangles[2] = Triangle(v2,v3,v0, Vertex(1, 1, 0), _color);
	triangles[3] = Triangle(v3,v0,v1, Vertex(1, 0, 1), _color);

	transform(pos);
}

Tetrahedron::~Tetrahedron()
{
}

bool Tetrahedron::rayIntersection(Ray &r, Vertex &intersectionPoint, int &triangleIndex, double &scalar) {
	Vertex hitPos;
	double t = 99999999999; //Max length from camera to render.
	bool hit = false;

	for (int i = 0; i < 4; i++) {
		double _scalar = 0;
		if (triangles[i].rayIntersection(r, hitPos, _scalar)) {
			if (_scalar < t && _scalar > 0) {
				intersectionPoint = hitPos;
				triangleIndex = i;
				scalar = _scalar;
				hit = true;
			}
		}
	}
	return hit;
}

void Tetrahedron::transform(Vertex pos)
{
	transform(pos.x, pos.y, pos.z);
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
