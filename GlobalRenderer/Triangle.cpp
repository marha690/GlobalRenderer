#include "pch.h"
#include "Triangle.h"

// Constructors & destructors
Triangle::Triangle() {
}

Triangle::Triangle(Vertex _v0, Vertex _v1, Vertex _v2, Color _color)
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
	Direction line1 = v1 - v0;
	Direction line2 = v2 - v0;

	Direction normalDir = glm::cross(line1, line2);

	normal = glm::normalize(normalDir);
}



//Other Functions

//Computes the intersection between a Ray and the Triangle with Möller-Trumbore alghorithm.
bool Triangle::rayIntersection(Ray &r)
{
	Vertex rayEnd = r.getEnd();
	Vertex rayStart = r.getStart();

	Direction edge1 = v1 - v0;
	Direction edge2 = v2 - v0;
	Direction T = rayStart - v0;
	Direction D = (rayEnd - rayStart); //Direction

	// Cross products.
	Direction P = glm::cross(D, edge2);
	Direction Q = glm::cross(T, edge1);

	double a = glm::dot(P,edge1);

	if ( std::abs(a) < EPSILON)
		return false;
	

	double f = 1.0 / a;
	double u = glm::dot(glm::dot(T, P), f);
	double v = glm::dot(glm::dot(Q, D), f);


	if (u < 0.0 || u > 1.0)
		return false;

	if (v < 0.0 || u + v > 1.0)
		return false;
	
	double t = glm::dot(glm::dot(edge2, Q), f);

	//Check if the hit is behind of rays startposition.
	if (t <= EPSILON || t > 1 - EPSILON)
		return false;


	Direction rayHitPosition = Direction(rayStart) + t * D;
	Vertex point = Vertex(rayHitPosition.x, rayHitPosition.y, rayHitPosition.z, 1);
	r.setEnd(point); // sets new end position and this triangle as hitted surface.
	IntersectionData *data = new IntersectionData(point, normal, Surface::specular);
	r.setHitData(data);
	r.setColor(this->color);

	return true;
}

