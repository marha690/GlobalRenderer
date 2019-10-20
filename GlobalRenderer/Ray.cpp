#include "pch.h"
#include "Ray.h"
#include "matrix_transform.hpp"
#include "matrix_inverse.hpp"
#include "gtx/rotate_vector.hpp"

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
	float randomAzimuth = 1;
	float randomInclination = 1;

	Direction normal = glm::normalize(this->getHitData()->normal);
	Direction helper = glm::vec3(normal) + glm::vec3(1, 1, 1);

	Direction tangent = glm::normalize(glm::cross(normal, helper));

	float inclination = acos(glm::sqrt(randomInclination));
	float azimuth = 2 * CONSTANTS::PI * randomAzimuth;

	glm::vec3 randomDir = normal;

	randomDir = glm::normalize(glm::rotate(randomDir, azimuth, glm::vec3(normal)));
	randomDir = glm::normalize(glm::rotate(randomDir, inclination, glm::vec3(tangent)));

	return new Ray(getEnd(), Vertex(randomDir,1) * 100.0);
}
