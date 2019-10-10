#pragma once

#include "Ray.h"
#include "MyColor.h"
#include "SFML/Graphics.hpp"

class Ray;
class Triangle;

class Pixel
{
public:

	//Variables
	Ray *ray;
	MyColor color;

	void setColor(MyColor _color);
	void connectRay(Ray *_ray);

	MyColor getColor() { return color; }

	Pixel();

	~Pixel() { delete ray; }

};
