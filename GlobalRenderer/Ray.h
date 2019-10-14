#pragma once


#include "Vertex.h"
#include "Triangle.h"
#include "Definitions.h"

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
	Color color;
	Triangle *hitTriangle = nullptr;

	//Setters
public:
	void setEnd(Vertex _end, Triangle *t) { end = _end; hitTriangle = t; }
	void setColor(Color c) { color = c; }
private:
	void setStart(Vertex _start) { start = _start; }

	//Getters
public:
	Vertex getEnd() { return end; }
	Vertex getStart() { return start; }
	Vertex getDirection() { return (end - start); }
	Color getColor() { return color; }
	Triangle* getTriangle() { return hitTriangle; }

	//Other Functions
public:
	void print();
	friend std::ostream& operator<<(std::ostream& os, const Ray& v);


};