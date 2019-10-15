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
	
	double b = glm::dot(2.0*l, Vertex(oc, 1));

	double ac = glm::dot((oc), (oc)) - (radius*radius);

	double d1 = -(b / 2.0);

	double sqrtTerm = glm::pow(d1,2) - ac;


	if (sqrtTerm < CONSTANTS::EPSILON) return false;

	sqrtTerm = glm::sqrt(sqrtTerm);

	double d2 = d1;

	d1 += sqrtTerm;
	d2 -= sqrtTerm;


	if (d1 > CONSTANTS::EPSILON) {
		Vertex temp = o + d1 * l;
		IntersectionData *data = new IntersectionData(temp, glm::normalize(temp - center), Surface::specular);
		r.setEnd(temp);
		r.setHitData(data);
		r.setColor(this->color);
		return true;
	}
	else if (d2 > CONSTANTS::EPSILON) {
		Vertex temp = o + d2 * l;
		IntersectionData *data = new IntersectionData(temp, glm::normalize(temp - center), Surface::specular);
		r.setEnd(temp);
		r.setHitData(data);
		r.setColor(this->color);
		return true;
	}


	return false;
}
