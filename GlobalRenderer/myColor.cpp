#include "pch.h"
#include "myColor.h"

#include <iostream>

//Constructor
myColor::myColor()
	:r(101), b(101), g(101) {}
myColor::myColor(double _r = 255, double _g = 255, double _b = 255)
	: r(_r), b(_b), g(_g) {}

//Destructor
myColor::~myColor()
{
}

sf::Color myColor::toSFLinear(double min, double max)
{
	//Normalize colors
	double red = (r-min) / (max); //Norm between 0 and 1.
	double green = (g-min) / (max); //Norm between 0 and 1.
	double blue = (b-min) / (max); //Norm between 0 and 1.

	//Make them to range between 0 and 255 (8bits since sf::Color has 8bits color-input).
	red *= 255;
	green *= 255;
	blue *= 255;

	return sf::Color((int)red, (int)green, (int)blue);
}

void myColor::print()
{
	std::cout << "Color:[" << r << ", " << g << ", " << b << "]\n";
}
