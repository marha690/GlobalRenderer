#include "pch.h"
#include "Camera.h"

#include <cmath>

#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <matrix_transform.hpp>

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

			Ray *ray = createPixelRay(x, y); //Create rays for the pixel.
			ray->setColor(s->tracePath(ray));

		}
		std::cout << "\rProgress: " << (y / (pixelsVericaly / 100)) << "%";
	}
	std::cout << "\rProgress: 100%\n";
}


//Connects pixel with the rays which is projected inside it.
Ray* Camera::createPixelRay(int x, int y) 
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex( 0, (viewWidth / 2) - x*pixelWidth, (viewHeight / 2) - y*pixelHeight, 1);

	//Create ray for the pixel
	Ray *myRay = new Ray(startPosition, pixelPosition);
	Vertex end = glm::normalize(myRay->getDirection());
	myRay->setEnd( end *= 1000);

	//Connect the ray to that pixel.
	pixels[x + pixelsVericaly * y].connectRay(myRay);
	return myRay;
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

//Set pixels color from the pixel-rays interpolated colors.
void Camera::setInternalPixelColors()
{
	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {

			Pixel *p = &pixels[x + pixelsVericaly * y];

			p->color = getColorForPixel(p);
		}
	}
}

Color Camera::getColorForPixel(Pixel *p) 
{
	return p->ray->getColor();

}

