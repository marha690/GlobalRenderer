#include "pch.h"
#include "Sphere.h"

#include <cmath>


Sphere::Sphere()
{
	center = Vertex(0,0,0,1);
	color = Color(251,251,251);
}

Sphere::Sphere(Vertex _center, double _radius, Color _c)
{
	radius = _radius;
	center = _center;
	color = _c;
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
	Vertex l = r.getDirection();

	l = glm::normalize(l);

	
	Direction oc = o - c;
	double b = 2.0 * glm::dot(l, Vertex(oc, 1));
	double ac = glm::dot((oc), (oc)) - (radius*radius);

	double d = -(b / 2.0);

	double sqrtTerm = glm::pow(d,2) - ac;

	//Dont make it complex!
	if (sqrtTerm < CONSTANTS::EPSILON) return false;

	sqrtTerm = glm::sqrt(sqrtTerm);

	double distance1 = d + sqrtTerm;
	double distance2 = d - sqrtTerm;

	Vertex hit1 = o + distance1 * l;
	Vertex hit2 = o + distance2 * l;

	//Ugly but works
	if (distance1 > CONSTANTS::EPSILON && hit1.length() < hit2.length()) {

		if ((r.getEnd() - r.getStart()).length() > hit1.length())
			return false;

		IntersectionData *data = new IntersectionData(hit1, glm::normalize(hit1 - center), Surface::specular);
		r.setEnd(hit1);
		r.setHitData(data);
		r.setSurfaceType(Surface::specular);
		r.setColor(this->color);
		return true;
	}
	else if (distance2 > CONSTANTS::EPSILON) {

		if ((r.getEnd() - r.getStart()).length() > hit2.length())
			return false;

		IntersectionData *data = new IntersectionData(hit2, glm::normalize(hit2 - center), Surface::specular);
		r.setEnd(hit2);
		r.setHitData(data);
		r.setSurfaceType(Surface::specular);
		r.setColor(this->color);
		return true;
	}

	return false;
}
