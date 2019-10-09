#include "pch.h"
#include "Vertex.h"

#include <iostream>
#include <cmath>



//Constructors
Vertex::Vertex()
{
	Vertex::x = 0;
	Vertex::y = 0;
	Vertex::z = 0;
}

Vertex::Vertex(double x_in, double y_in, double z_in)
{
	Vertex::x = x_in;
	Vertex::y = y_in;
	Vertex::z = z_in;
}


//Destructor
Vertex::~Vertex()
{
}


std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
	os << "( " << v.x << ", " << v.y << ", " << v.z << " )\n";
	return os;
}

Vertex operator+(const Vertex &v1, const Vertex &v2)
{
	Vertex newV = v1;
	newV.x += v2.x;
	newV.y += v2.y;
	newV.z += v2.z;
	return newV;
}

Vertex operator-(const Vertex &v1, const Vertex &v2)
{
	Vertex newV = v1;
	newV.x -= v2.x;
	newV.y -= v2.y;
	newV.z -= v2.z;
	return newV;
}

//Cross-product of two vectors
Vertex operator^(const Vertex &v1, const Vertex &v2)
{
	Vertex newV;
	newV.x = v1.y * v2.z - v2.y*v1.z;
	newV.y = v1.z * v2.x - v2.z*v1.x;
	newV.z = v1.x * v2.y - v2.x*v1.y;
	return newV;
}

//Dot-product of two vectors
double operator*(const Vertex &v1, const Vertex &v2)
{
	double sum = (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
	return sum;
}


//Division of two vectors
Vertex operator*(const Vertex &v1, const double &i)
{
	Vertex newV = v1;
	newV.x *= i;
	newV.y *= i;
	newV.z *= i;
	return newV;
}

double Vertex::magnitude() const
{
	return sqrt(x*x + y * y + z * z);
}

Vertex Vertex::normalize()
{
	double length = std::sqrt(x*x + y*y + z*z);
	return Vertex(x/length, y/length, z/length);
}
