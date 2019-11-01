#pragma once

#include "Pixel.h"
#include "Scene.h"

class Camera
{
public:
	enum Eye
	{
		EYE_ONE = 1,
		EYE_TWO = 2
	};

	//Variables
	const Vertex eye1 = Vertex(-2, 0, 0, 1);
	const Vertex eye2 = Vertex(-1, 0, 0, 1);

	const Vertex c1 = Vertex(0, -1, -1, 1);
	const Vertex c2 = Vertex(0, 1, -1, 1);
	const Vertex c3 = Vertex(0, 1, 1, 1);
	const Vertex c4 = Vertex(0, -1, 1, 1);
	const int viewHeight = 2;
	const int viewWidth = 2;

	int pixelsVericaly;
	int pixelsHorizontaly;
	int totalPixels;

	Eye selectedEye;
	Vertex startPosition;

	Pixel* pixels;

	//Functions
	Camera(int _pxX, int pxY, Eye eye);

	void render(Scene *s);


	double maxColorValue();



	~Camera();
private:
	//Returns the color from the rays.
	Color createPixelRays(int x, int y, Scene *s);
};

