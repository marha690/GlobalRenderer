#pragma once

#include "Ray.h"
#include "Definitions.h"
#include "SFML/Graphics.hpp"


#include <vector>

class Ray;
class Triangle;

class Pixel
{
public:

	//Variables
	Color color;

	void setColor(Color _color);
	Color getColor() { return color; }

	Pixel();
	~Pixel() = default;

};
