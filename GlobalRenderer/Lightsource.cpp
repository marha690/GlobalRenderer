#include "pch.h"
#include "Lightsource.h"

#include <random>

Lightsource::Lightsource(Vertex pos)
	: position(pos)
{
	double s = sideLength / 2.0;
	v0 = pos + Vertex(-s, -s, 0, 1);
	v1 = pos + Vertex(s, -s, 0, 1);
	v2 = pos + Vertex(-s, s, 0, 1);
	v3 = pos + Vertex(s, s, 0, 1);


	color = whiteLight;
	triangles[0] = Triangle(v0, v2, v1, whiteLight);
	triangles[1] = Triangle(v1, v2, v3, whiteLight);
}

bool Lightsource::rayInterSection(Ray & ray)
{
	if (triangles[0].rayIntersection(ray) || triangles[1].rayIntersection(ray)) {
		ray.setSurfaceType(SurfaceType::Light);
		return true;
	}

	return false;
}

Vertex Lightsource::getRandomPoint()
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	double halfLength = sideLength / 2.0;
	Vertex point = Vertex(position.x + dis(rd)*sideLength - halfLength,
						  position.y + dis(rd)*sideLength - halfLength,
						  position.z,
					      1);
	
	return point;
}

Lightsource::~Lightsource()
{
}
