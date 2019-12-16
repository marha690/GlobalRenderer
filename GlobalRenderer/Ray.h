#pragma once


#include "Triangle.h"
#include "Definitions.h"
#include "IntersectionData.h"

class Triangle;
class Ray;

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
	Surface *hit = nullptr;


	//Setters
public:
	void setEnd(Vertex _end) { end = _end;}
	void setHitData(Surface *d) { hit = d; }
	void setColor(Color c) { color = c; }
	void setSurfaceType(SurfaceType s);

	//Getters
public:
	Vertex getEnd() { return end; }
	Vertex getStart() { return start; }
	Vertex getDirection() { return glm::normalize(end - start); }
	Color getColor() { return color; }
	Surface* getHitData() { return hit; }

	//Other Functions
public:
	void print();
	friend std::ostream& operator<<(std::ostream& os, const Ray& v);

	Ray perfectBounce();
	Ray refractedBounce();
	Ray randomBounce();
};