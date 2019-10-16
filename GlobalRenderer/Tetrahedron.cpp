#include "pch.h"
#include "Tetrahedron.h"

//Constructors & destructors
Tetrahedron::Tetrahedron()
{
	Color color = Color(1, 1, 1);
	triangles[0] = Triangle(v0, v1, v2, color);
	triangles[1] = Triangle(v1, v2, v3, color);
	triangles[2] = Triangle(v2, v3, v0, color);
	triangles[3] = Triangle(v3, v0, v1, color);
}

Tetrahedron::Tetrahedron(Vertex pos, Color _color)
{
	triangles[0] = Triangle(v0,v1,v2, _color);
	triangles[1] = Triangle(v1,v2,v3, _color);
	triangles[2] = Triangle(v2,v3,v0, _color);
	triangles[3] = Triangle(v3,v0,v1, _color);

	transform(pos);
}

Tetrahedron::~Tetrahedron()
{
}

//Other Functions
bool Tetrahedron::rayIntersection(Ray &r) {
	bool hit = false;

	for (int i = 0; i < 4; i++) {
		if (triangles[i].rayIntersection(r)) {
			r.setSurfaceType(Surface::specular);
			hit = true;
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

	v0 = v0 + Vertex(x, y, z, 1);
	v1 = v1 + Vertex(x, y, z, 1);
	v2 = v2 + Vertex(x, y, z, 1);
	v3 = v3 + Vertex(x, y, z, 1);

	triangles[0] = Triangle(v0, v1, v2, triangles[0].getColor());
	triangles[1] = Triangle(v1, v2, v3, triangles[1].getColor());
	triangles[2] = Triangle(v2, v3, v0, triangles[2].getColor());
	triangles[3] = Triangle(v3, v0, v1, triangles[3].getColor());
}
