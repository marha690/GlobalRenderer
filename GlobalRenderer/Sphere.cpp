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
	Vertex start = r.getStart();
	Vertex d= glm::normalize(r.getDirection());

	double a = glm::dot(d, d);
	double b = 2 * (glm::dot(d, (start - center)));
	double c = glm::dot((start - center), (start - center)) - (radius*radius);

	double sqrtTerm = std::sqrt(((b / 2)*(b / 2)) - a * c);
	double firstTerm = -(b / 2);

	double scalarPositive = firstTerm + sqrtTerm;
	double scalarNegative = firstTerm - sqrtTerm;

	Vertex sphereHit1 = start + d * scalarPositive; //potental intersection with the sphere.
	Vertex sphereHit2 = start + d * scalarNegative; //potential intersection with the sphere.

	double myEPSILON = 0.000001;
	if (glm::dot((sphereHit1 - center), (sphereHit1 - center)) - (radius*radius) < myEPSILON) {
		r.setEnd(sphereHit1, nullptr);
		r.setColor(this->color);
		return true;
	}

	return false;
}
