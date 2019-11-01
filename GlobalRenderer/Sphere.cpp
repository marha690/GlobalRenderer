#include "pch.h"
#include "Sphere.h"

#include <cmath>


Sphere::Sphere()
{
	center = Vertex(0,0,0,1);
	color = COLOR::WHITE;
}

Sphere::Sphere(Vertex _center, double _radius, Color _c, SurfaceType s)
{
	radius = _radius;
	center = _center;
	color = _c;
	surface = s;
}

Sphere::~Sphere()
{

}

void Sphere::transform(Vertex tr)
{
	center = center + tr;
}

void Sphere::transform(double x, double y, double z)
{
	transform(Vertex(x, y, x, 1));
}

bool Sphere::rayIntersection(Ray &r) 
{
	Vertex o = r.getStart();
	Vertex c = center;
	Direction l = r.getDirection();

	Direction oc = o - c;
	double b = 2.0f * glm::dot(l, oc);
	double ac = glm::dot((oc), (oc)) - (radius*radius);

	double d = -(b / 2.0f);

	double sqrtTerm = glm::pow(d,2) - ac;

	//Dont make it complex!
	if (sqrtTerm < CONSTANTS::EPSILON) return false;

	sqrtTerm = glm::sqrt(sqrtTerm);

	double distance1 = d + sqrtTerm;
	if (distance1 < CONSTANTS::EPSILON)
		return false;

	double distance2 = d - sqrtTerm;
	if (distance2 < CONSTANTS::EPSILON)
		return false;

	Vertex hit1 = o + distance1 * Vertex(l,0);
	Vertex hit2 = o + distance2 * Vertex(l,0);

	Vertex closestHit;

	if (hit1.length() < hit2.length()) {
		if ((r.getEnd() - r.getStart()).length() > hit1.length())
			return false;
		closestHit = hit1;
	}
	else {
		if ((r.getEnd() - r.getStart()).length() > hit2.length())
			return false;
		closestHit = hit2;
	}

	Surface *data = new Surface(glm::normalize(closestHit - center), SurfaceType::Specular);
	r.setEnd(closestHit);
	r.setHitData(data);
	r.setSurfaceType(surface);
	r.setColor(this->color);
	return true;
}
