#include "pch.h"
#include "Lightsource.h"


Lightsource::Lightsource(Vertex pos)
	: position(pos)
{
	v0 = pos + Vertex(-1, -1, 0, 1);
	v1 = pos + Vertex(-1, 1, 0, 1);
	v2 = pos + Vertex(1, -1, 0, 1);
	v3 = pos + Vertex(1, 1, 0, 1);


	color = whiteLight;
	triangles[0] = Triangle(v0, v2, v1, whiteLight);
	triangles[1] = Triangle(v1, v2, v3, whiteLight);
}

bool Lightsource::rayInterSection(Ray & ray)
{
	if (triangles[0].rayIntersection(ray) || triangles[0].rayIntersection(ray))
		return true;

	return false;
}

Lightsource::~Lightsource()
{
}
