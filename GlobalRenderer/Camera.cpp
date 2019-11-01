#include "pch.h"
#include "Camera.h"

#include <cmath>


Camera::Camera(int pxX, int pxY, Eye eye = Eye::EYE_ONE)
{
	pixelsHorizontaly = pxX;
	pixelsVericaly = pxY;
	totalPixels = pixelsVericaly * pixelsHorizontaly;
	pixels = new Pixel[totalPixels];

	selectedEye = eye;
	if (eye == Eye::EYE_ONE) {
		startPosition = eye1;
	}
	else {
		startPosition = eye2;
	}
}

Camera::~Camera() {
}


void Camera::render(Scene *s)
{
	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {

			Pixel *p = &pixels[x + pixelsVericaly * y];
			p->color = createPixelRays(x, y, s);

		}
		std::cout << "\rProgress: " << (y / (pixelsVericaly / 100)) << "%";
	}
	std::cout << "\rProgress: 100%\n";
}


//Returns the color from the rays inside a pixel.
Color Camera::createPixelRays(int x, int y, Scene* s)
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));
	Vertex pixelPosition = Vertex(0, (viewWidth / 2) - x * pixelWidth, (viewHeight / 2) - y * pixelHeight, 1);

	Pixel *p = &pixels[x + pixelsVericaly * y];
	Color c = Color(0, 0, 0);

	//One ray per pixel.
	if (CONSTANTS::RAYS_PER_PIXEL == 1) {
		Ray ray = Ray(startPosition, pixelPosition);
		ray.setEnd(ray.getDirection() *= CONSTANTS::INITAL_LENGTH);
		c += (s->tracePath(&ray)); //Follow the ray out in the scene.
		return c;
	}

	//More than one ray per pixel. (does not work for 2 or 3 rays).
	int subN = CONSTANTS::RAYS_PER_PIXEL / 2;
	double rayStepsH = pixelWidth / subN;
	double rayStepsV = pixelHeight / subN;
	for (int i = 0; i < subN; i++)
	{
		for (int j = 0; j < subN; j++)
		{
			Vertex rayPos = pixelPosition + Vertex(0, j * rayStepsH, i * rayStepsV, 1);
			Ray ray = Ray(startPosition, rayPos);
			ray.setEnd(ray.getDirection() *= CONSTANTS::INITAL_LENGTH);

			c += (s->tracePath(&ray)); //Follow the ray out in the scene.
		}
	}

	return c;
}

double Camera::maxColorValue()
{
	double max = 0;
	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {
			Color c = pixels[x + pixelsVericaly * y].color;

			if (c.r > max)
				max = c.r;
			if (c.g > max)
				max = c.g;
			if (c.b > max)
				max = c.b;
		}
	}
	return max;
}


