#include "pch.h"
#include "Ray.h"
#include "matrix_transform.hpp"
#include "matrix_inverse.hpp"
#include "gtx/rotate_vector.hpp"
#include "gtx/vector_angle.hpp"

#include <random>

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
	if (hit)
		delete hit;
}


void Ray::setSurfaceType(SurfaceType s)
{
	hit->sufaceType = s;
}

void Ray::print() {
	std::cout << (end - start).x << ", " << (end - start).y << ", " << (end - start).z << "\n";
}


std::ostream& operator<<(std::ostream& os, const Ray& v)
{
	os << (v.end - v.start).x << ", " << (v.end - v.start).y << ", " << (v.end - v.start).z << "\n";
	return os;
}


Ray Ray::perfectBounce()
{
	Direction out = glm::reflect(getDirection(), Vertex(hit->normal, 0));
	return Ray(end, Vertex(out,0) * CONSTANTS::INITAL_LENGTH);
}


Ray Ray::refractedBounce()
{

	//Refraction indexes. Implement this inside material class leter.
	double n1 = 1;
	double n2 = 1;
	double refractionIndex = n1 / n2;

	Vertex normal = glm::normalize( Vertex( this->getHitData()->normal,0) );

	double dotNI = glm::dot(normal, getDirection());
	Direction T = refractionIndex * getDirection()
		+ normal*(-refractionIndex * dotNI
		- sqrt(1 - refractionIndex * refractionIndex * (1 - dotNI * dotNI)) );

	return Ray(end, Vertex(T, 0) * CONSTANTS::INITAL_LENGTH);
}


Ray Ray::randomBounce()
{
	std::uniform_real_distribution<double> rand(0.0, 1.0);

	float fMin = 0.0;
	float fMax = 1.0;
	float f1 = (float)std::rand() / RAND_MAX;
	float randomAzimuth = fMin + f1 * (fMax - fMin);
	float f2 = (float)std::rand() / RAND_MAX;
	float randomInclination = fMin + f2 * (fMax - fMin);

	Direction normal = this->getHitData()->normal;
	Direction helper = glm::vec3(normal) + glm::vec3(1, 1, 1);

	Direction tangent = glm::normalize(glm::cross(normal, helper));

	float inclination = acos(glm::sqrt(randomInclination));
	float azimuth = 2 * (float)CONSTANTS::PI * randomAzimuth;

	glm::vec3 randomDir = normal;

	randomDir = glm::normalize(glm::rotate(randomDir, azimuth, glm::vec3(normal)));
	randomDir = glm::normalize(glm::rotate(randomDir, inclination, glm::vec3(tangent)));

	return Ray(getEnd(), Vertex(randomDir,1) * CONSTANTS::INITAL_LENGTH);
}

