#include "pch.h"
#include "Sphere.h"

#include <cmath>


Sphere::Sphere()
{
	center = Vertex(0,0,0);
	color = myColor(251,251,251);
}

Sphere::Sphere(Vertex _center, myColor _c)
{
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
	transform(Vertex(x, y, x));
}

bool Sphere::rayIntersection(Ray &r, Vertex &intersectionPoint, double &scalar) 
{
	Vertex start = r.start;
	Vertex direction = r.getDirection().normalize();

	double a = direction * direction;
	double b = 2 * (direction*(start - center));
	double c = (start - center) * (start - center) - (radius*radius);

	double sqrtTerm = std::sqrt(((b / 2)*(b / 2)) - a * c);
	double firstTerm = -(b / 2);

	double scalarPositive = firstTerm + sqrtTerm;
	double scalarNegative = firstTerm - sqrtTerm;

	Vertex x = start +  direction * scalarPositive; //potental intersection with the sphere.
	Vertex xx = start + direction * scalarNegative; //potential intersection with the sphere.

	double myEPSILON = 0.000001;
	if ((x - center)*(x - center) - (radius*radius) < myEPSILON) {
		scalar = scalarPositive;
		return true;
	}

	return false;
}
