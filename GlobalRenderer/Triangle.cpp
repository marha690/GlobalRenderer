#include "pch.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle()
{}

// Constructor
Triangle::Triangle(Vertex _v1, Vertex _v2, Vertex _v3, Vertex _normal, myColor _color)
	: v1(_v1), v2(_v2), v3(_v3), normal(_normal)
{
	color = _color;
}


//Destructor
Triangle::~Triangle()
{
}


// rayIntersection. Computes the intersection between a Ray and the Triangle with Möller-Trumbore alghorithm.
Vertex Triangle::rayIntersection(Ray &r, bool &hit)
{
	const double EPSILON = 0.0000001;

	Vertex rayDirection = (r.end - r.start);

	Vertex edge1 = v2 - v1;
	Vertex edge2 = v3 - v1;

	Vertex T, Q, P;
	T = r.start - v1;
	P = rayDirection ^ edge2;
	Q = T ^ edge1;

	double a, f;
	double t, u, v;

	a = P * edge1;

	if (a > -EPSILON && a < EPSILON) {
		hit = false;
		return Vertex();
	}

	f = 1.0 / a;

	t = (Q * edge2) * f;
	u = (T*P) * f;
	v = (Q*rayDirection) * f;

	if (u < 0.0 || u > 1.0) {
		hit = false;
		return Vertex();
	}

	if (v < 0.0 || u + v > 1.0) {
		hit = false;
		return Vertex();
	}


	if (v > EPSILON) { //Ray intersection!
		Vertex out = r.start + rayDirection * t;
		hit = true;
		return out;
	}
	else { //This means there are a line intersecting but not the ray.
		hit = false;
		return Vertex();
	}
}