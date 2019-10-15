#pragma once


#include "Triangle.h"
#include "Definitions.h"
#include "IntersectionData.h"

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
	IntersectionData *hit = nullptr;


	//Setters
public:
	void setEnd(Vertex _end) { end = _end;}
	void setHitData(IntersectionData *d) { hit = d; }
	void setColor(Color c) { color = c; }
private:
	void setStart(Vertex _start) { start = _start; }

	//Getters
public:
	Vertex getEnd() { return end; }
	Vertex getStart() { return start; }
	Vertex getDirection() { return (end - start); }
	Color getColor() { return color; }
	IntersectionData* getHitData() { return hit; }

	//Other Functions
public:
	void print();
	friend std::ostream& operator<<(std::ostream& os, const Ray& v);


};