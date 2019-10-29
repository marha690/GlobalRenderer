#pragma once

#ifndef DEFINITIONS
#define DEFINITIONS

#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <dvec.h>

namespace CONSTANTS {
	const double	PI = 3.1415f;
	const double	EPSILON = 0.0000001;

	const int		screenSize_X = 300; // Min: 100
	const int		screenSize_Y = 300;

	const int		RAYS_PER_PIXEL = 10;
	const double	INITAL_LENGTH = 1000; //The length rays get when created. 

	const double	RAY_ABSOPTIONRATE = 0.5; //Between 0 and 1.
	const double	IMPORTANCE_SCALAR = 0.3; //Between 0 and 1.
}

enum SurfaceType {
	Lambertian,
	Specular
};

using Color = glm::dvec3;
using Vertex = glm::dvec4;
using Direction = glm::dvec3;

#endif // DEFINITIONS
