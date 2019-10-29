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
			Color c = Color(0.0);

			createPixelRays(x, y, CONSTANTS::RAYS_PER_PIXEL); //Create rays for the pixels.

			for (unsigned int i = 0; i < CONSTANTS::RAYS_PER_PIXEL; i++) {
				c += (s->tracePath(p->rays.at(i))); //Follow the ray out in the scene.
			}

			p->color = c; //Set the color for the pixel.
		}
		std::cout << "\rProgress: " << (y / (pixelsVericaly / 100)) << "%";
	}
	std::cout << "\rProgress: 100%\n";
}


void Camera::createPixelRays(int x, int y, int n)
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex(0, (viewWidth / 2) - x * pixelWidth, (viewHeight / 2) - y * pixelHeight, 1);

	int subN = n / 2;
	double rayStepsH = pixelWidth / subN;
	double rayStepsV = pixelHeight / subN;

	for (int i = 0; i < subN; i++)
	{
		for (int j = 0; j < subN; j++)
		{
			Vertex rayPos = pixelPosition + Vertex(0, j * rayStepsH, i * rayStepsV, 1);
			Ray *ray = new Ray(startPosition, rayPos);
			ray->setEnd(ray->getDirection() *= 1000); //ugly

			pixels[x + pixelsVericaly * y].rays.push_back(ray);
		}
	}
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


