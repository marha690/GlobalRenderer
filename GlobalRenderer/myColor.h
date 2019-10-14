#pragma once

#include "SFML/Graphics.hpp"

class MyColor
{
public:
	//Variables
	double r, g, b;
	//Constructor
	MyColor();
	MyColor(double _r, double _g, double _b);

	//Destructor
	~MyColor();

	friend std::ostream& operator<<(std::ostream& os, const MyColor& c);

	friend MyColor operator*(const MyColor &c, const double &d);

	//Convert myColor to SFML's sf::Color linear.
	sf::Color toSFLinear(double min, double max);

	MyColor toLinear(double min, double max);

};

