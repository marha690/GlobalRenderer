#pragma once

#include <iostream> //for debugging messages

class Vertex
{
public:

	//Variables
	double x, y, z; //spatial coordinates

	//constructors
	Vertex();
	Vertex(double x_in, double y_in, double z_in);

	//Destructor
	~Vertex();

	//Print function, writes teh vertex coordinates to the console.
	void print();

	friend Vertex operator+(const Vertex &v1, const Vertex &v2);

	friend Vertex operator-(const Vertex &v1, const Vertex &v2);

	//Cross-product of two vextors
	friend Vertex operator^(const Vertex &v1, const Vertex &v2);

	//Dot-product of two vextors
	friend double operator*(const Vertex &v1, const Vertex &v2);

	//multiplication of vextor and double.
	friend Vertex operator*(const Vertex &v1, const double &i);

	double magnitude() const;
};