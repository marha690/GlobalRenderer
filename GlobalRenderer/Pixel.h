#pragma once

#include "Ray.h"
#include "Definitions.h"
#include "SFML/Graphics.hpp"

class Ray;
class Triangle;

class Pixel
{
public:

	//Variables
	Ray *ray;
	Color color;

	void setColor(Color _color);
	void connectRay(Ray *_ray);

	Color getColor() { return color; }

	Pixel();

	~Pixel() { delete ray; }

};
