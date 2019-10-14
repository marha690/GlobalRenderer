#pragma once

#ifndef DEFINITIONS
#define DEFINITIONS



#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <dvec.h>
#include <mat4x4.hpp>

namespace CONSTANTS {
	const double   EPSILON = 0.0000001;
	const int   screenSize_X = 800;
	const int   screenSize_Y = 800;
}

enum Surface {
	diffuse,
	specular,
	transparent
};


using Color = glm::dvec3;
using Vertex = glm::dvec4;
using Direction = glm::dvec3;
/*
Use this if i want to remove my own vertex class.
*/

#endif // DEFINITIONS
