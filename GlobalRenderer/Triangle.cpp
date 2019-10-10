#include "pch.h"
#include "Triangle.h"

// Constructors & destructors
Triangle::Triangle() {
}

Triangle::Triangle(Vertex _v0, Vertex _v1, Vertex _v2, MyColor _color)
	: v0(_v0), v1(_v1), v2(_v2), color(_color)
{
	setNormal(v0, v1, v2);
}



Triangle::~Triangle()
{
}



//Setters
void Triangle::setNormal(Vertex v0, Vertex v1, Vertex v2)
{
	Vertex line1 = v1 - v0;
	Vertex line2 = v2 - v0;

	Vertex normalDir = line1 ^ line2;

	normal = normalDir.normalize();
}



//Other Functions

//Computes the intersection between a Ray and the Triangle with Möller-Trumbore alghorithm.
bool Triangle::rayIntersection(Ray &r)
{
	Vertex rayEnd = r.getEnd();
	Vertex rayStart = r.getStart();
	Vertex rayDirection = (rayEnd - rayStart).normalize();

	Vertex edge1 = v1 - v0;
	Vertex edge2 = v2 - v0;

	Vertex T, Q, P;
	T = rayStart - v0;

	// Cross products.
	P = rayDirection ^ edge2;

	double a, f;
	a = P * edge1;

	if ( std::abs(a) < EPSILON) {
		return false;
	}

	Q = T ^ edge1;
	f = 1.0 / a;

	double t, u, v;
	t = (Q * edge2) * f;
	u = (T*P) * f;
	v = (Q*rayDirection) * f;

	if (u < 0.0 || u > 1.0) {
		return false;
	}

	//Does it hit the triangle?
	if (v < 0.0 || u + v > 1.0) {
		return false;
	}

	//Check if the hit is behind of rays startposition.
	if (t <= 0)
		return false;

	Vertex newRayEnd = rayStart + rayDirection * t;

	//Is the new hit futher away than the rays end?
	if (newRayEnd.magnitude() > rayEnd.magnitude())
		return false;

	r.setEnd(newRayEnd, this); // sets new end position and this triangle as hitted surface.
	r.setColor(this->color);

	return true;
}

