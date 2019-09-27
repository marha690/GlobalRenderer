#pragma once

#include "SFML/Graphics.hpp"

class myColor
{
public:
	//Variables
	double r, g, b;
	//Constructor
	myColor();
	myColor(double _r, double _g, double _b);

	//Destructor
	~myColor();

	//Convert myColor to SFML's sf::Color linear.
	sf::Color toSFLinear(double min, double max);

	//Print color values.
	void print();
};

