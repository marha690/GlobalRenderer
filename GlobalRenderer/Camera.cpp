#include "pch.h"
#include "Camera.h"

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
	int progress = 0;

	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {
			Ray *ray;
			ray = createPixelRays(x, y); //Create rays for the pixel.
			s->intersection(ray);
		}

		if ((y % (pixelsVericaly / 10)) == 0)
		{
			progress += 10; // 10% more of the scene is rendered
			std::cout << "Progress: " << progress << "%.\n";
		}
	}
}

//Connects pixel with the rays which is projected inside it.
Ray* Camera::createPixelRays(int x, int y) 
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex( 0, (viewWidth / 2) - x*pixelWidth, (viewHeight / 2) - y*pixelHeight);

	//Create ray for the pixel
	Ray *myRay = new Ray(startPosition, pixelPosition);

	//Connect the ray to that pixel.
	pixels[x + pixelsVericaly * y].connectRay(myRay);
	return myRay;
}

double Camera::maxColorValue()
{
	double max = 0;
	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {
			myColor c = pixels[x + pixelsVericaly * y].ray->color;

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
			pixels[x + pixelsVericaly * y].color = pixels[x + pixelsVericaly * y].ray->color;
		}
	}
}