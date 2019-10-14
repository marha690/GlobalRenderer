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

	Vertex edge1 = v1 - v0;
	Vertex edge2 = v2 - v0;
	Vertex T = rayStart - v0;
	Vertex D = (rayEnd - rayStart);//.normalize(); //Direction

	// Cross products.
	Vertex P = D ^ edge2;
	Vertex Q = T ^ edge1;

	double a = P * edge1;

	if ( std::abs(a) < EPSILON)
		return false;
	

	double f = 1.0 / a;
	double u = (T*P) * f;
	double v = (Q*D) * f;


	if (u < 0.0 || u > 1.0)
		return false;

	if (v < 0.0 || u + v > 1.0)
		return false;
	
	double t = (edge2 * Q) * f;

	//Check if the hit is behind of rays startposition.
	if (t <= EPSILON || t > 1 - EPSILON)
		return false;


	Vertex rayHitPosition = rayStart + D * t;
	r.setEnd(rayHitPosition, this); // sets new end position and this triangle as hitted surface.
	r.setColor(this->color);

	return true;
}

