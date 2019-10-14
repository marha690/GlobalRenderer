#pragma once


#include "Vertex.h"
#include "Triangle.h"
#include "myColor.h"

class Triangle;

class Ray
{
	//Constructors & destructors
public:
	Ray(Vertex _startPoint, Vertex _endPoint);
	~Ray();

	//Variables.
private:
	Vertex start;
	Vertex end;
	MyColor color;
	Triangle *hitTriangle = nullptr;

	//Setters
public:
	void setEnd(Vertex _end, Triangle *t) { end = _end; hitTriangle = t; }
	void setColor(MyColor c) { color = c; }
private:
	void setStart(Vertex _start) { start = _start; }

	//Getters
public:
	Vertex getEnd() { return end; }
	Vertex getStart() { return start; }
	Vertex getDirection() { return (end - start); }
	MyColor getColor() { return color; }
	Triangle* getTriangle() { return hitTriangle; }

	//Other Functions
public:
	void print();
	friend std::ostream& operator<<(std::ostream& os, const Ray& v);


};