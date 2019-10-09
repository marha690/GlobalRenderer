#pragma once

#include "Ray.h"
#include "myColor.h"
#include "SFML/Graphics.hpp"

class Ray;
class Triangle;

class Pixel
{
public:

	//Variables
	Ray *ray;
	myColor color;

	void setColor(myColor _color);
	void connectRay(Ray *_ray);

	myColor getColor() { return color; }

	Pixel();

	~Pixel() { delete ray; }

};
