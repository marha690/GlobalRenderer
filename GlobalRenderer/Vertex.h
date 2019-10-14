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

	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);

	friend Vertex operator+(const Vertex &v1, const Vertex &v2);

	friend Vertex operator-(const Vertex &v1, const Vertex &v2);

	//Cross-product of two vextors
	friend Vertex operator^(const Vertex &v1, const Vertex &v2);

	//Dot-product of two vextors
	friend double operator*(const Vertex &v1, const Vertex &v2);

	//multiplication of vextor and double.
	friend Vertex operator*(const Vertex &v1, const double &i);
	friend Vertex operator*(const double &i, const Vertex &v1);

	friend Vertex operator/(const Vertex &v1, const double &d);

	double magnitude() const;
	Vertex normalize();
};