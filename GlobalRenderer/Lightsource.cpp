#include "pch.h"
#include "Lightsource.h"


Lightsource::Lightsource(Vertex p0, Vertex p1, Vertex p2, Vertex p3)
	: v0(p0), v1(p1), v2(p2), v3(p3)
{
	lightColor = whiteLight;
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
