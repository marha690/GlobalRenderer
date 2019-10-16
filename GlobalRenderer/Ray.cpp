#include "pch.h"
#include "Ray.h"
#include "matrix_transform.hpp"
#include "matrix_inverse.hpp"

//Constructor
Ray::Ray(Vertex _startPoint, Vertex _endPoint)
{
	start = _startPoint;
	end = _endPoint;
	color = Color(250, 0, 250);
}


//Destructor
Ray::~Ray()
{
	if (reflectedRay)
		delete reflectedRay;

	if (refractedRay)
		delete refractedRay;
}


void Ray::setSurfaceType(Surface s)
{
	hit->sufaceType = s;
}

void Ray::print() {
	std::cout << (end - start).x << ", " << (end - start).y << ", " << (end - start).z << "\n";
}

void Ray::printRayTree()
{
	print();

	if (reflectedRay) {
		reflectedRay->printRayTree();
	}

	if (refractedRay) {
		refractedRay->printRayTree();
	}
}


std::ostream& operator<<(std::ostream& os, const Ray& v)
{
	os << (v.end - v.start).x << ", " << (v.end - v.start).y << ", " << (v.end - v.start).z << "\n";
	return os;
}


Ray* Ray::perfectBounce()
{
	Direction out = glm::reflect(getDirection(), Vertex(hit->normal, 0));
	return new Ray(end, Vertex(out,0) * 100.0);
}

Ray* Ray::randomBounce()
{
	//TODO. Doesn't work right now!

//Define new coordinate system
Direction Z = glm::normalize(hit->normal);
Direction I = glm::normalize(Direction(getDirection().x, getDirection().y, getDirection().z));
Direction IT = I - glm::dot(I, Z) * Z;
Direction X = IT / glm::abs(IT);
Direction Y = glm::cross(-X, Z);

glm::mat4 Tr = glm::translate(glm::mat4(1.0), glm::vec3(getEnd().x, getEnd().y, getEnd().z));

//Local coordinates
Vertex surfaceNormal = Vertex(0, 0, 1, 1);
Vertex in = Tr * getDirection();
Direction out = glm::reflect(in, surfaceNormal);

glm::mat3 inv = glm::inverse(Tr);

//Global coordintes
out = inv * out;

double inclinationAngle = (glm::dot(in, surfaceNormal) / (in.length() * surfaceNormal.length()));
Ray *ray = new Ray(getEnd(), Vertex(out,1) * 1000.0);
return ray;
}