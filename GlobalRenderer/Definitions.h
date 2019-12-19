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

	const int		screenSize_X = 400; // Min: 100
	const int		screenSize_Y = 400;

	const int		RAYS_PER_PIXEL = 20; //All other possitive integers than 2 and 3.
	const int		SHADOW_RAYS = 1;
	const double	INITAL_LENGTH = 1000; //The length rays get when created. 

	const double	RAY_ABSOPTIONRATE = 0.5; //Between 0 and 1.
	const double	IMPORTANCE_SCALAR = 0.3; //Between 0 and 1.
}


enum SurfaceType {
	Lambertian,
	OrenNayar,
	Specular,
	Transparent,
	Light
};

using Color = glm::dvec3;
using Vertex = glm::dvec4;
using Direction = glm::dvec3;

namespace COLOR {
	const Color BLACK = Color(0,0,0);
	const Color WHITE = Color(255, 255, 255);

	const Color GREEN = Color(0, 155, 0);
	const Color LIGHTGREEN = Color(0, 255, 0);
	const Color BLUE = Color(0, 0, 155);
	const Color LIGHTBLUE = Color(0, 0, 255);
	const Color RED = Color(155, 0, 0);
	const Color LIGHTRED = Color(255, 0, 0);

	const Color PINK = Color(255, 192, 203);
	const Color CYAN = Color(153, 230, 179);
	const Color SPONGE = Color(253, 254, 3);
	const Color MOSSGREEN = Color(53, 94, 59);
}


#endif // DEFINITIONS
