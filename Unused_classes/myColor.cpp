#include "pch.h"
#include "MyColor.h"

#include <iostream>

//Constructor
MyColor::MyColor()
	:r(101), b(101), g(101) {}
MyColor::MyColor(double _r = 255, double _g = 255, double _b = 255)
	: r(_r), b(_b), g(_g) {}

//Destructor
MyColor::~MyColor()
{
}

sf::Color MyColor::toSFLinear(double min, double max)
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

MyColor MyColor::toLinear(double min, double max)
{
	//Normalize colors
	double red = (r - min) / (max); //Norm between 0 and 1.
	double green = (g - min) / (max); //Norm between 0 and 1.
	double blue = (b - min) / (max); //Norm between 0 and 1.

	//Make them to range between 0 and 255 (8bits since sf::Color has 8bits color-input).
	red *= 255;
	green *= 255;
	blue *= 255;

	return MyColor((int)red, (int)green, (int)blue);
}

std::ostream& operator<<(std::ostream& os, const MyColor& c)
{
	os << "Color:[" << c.r << ", " << c.g << ", " << c.b << "]\n";
	return os;
}

MyColor operator*(const MyColor &c, const double &d) {
	return MyColor(c.r * d, c.g * d, c.b * d);
}