#pragma once

#include "Definitions.h"

class Surface
{
public:
	Direction normal;
	SurfaceType sufaceType;

	Surface(Direction n, SurfaceType s);
	~Surface();
};

