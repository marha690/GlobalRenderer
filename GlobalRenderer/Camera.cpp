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
	delete pixels;
}

//Connects pixel with the rays which is projected inside it.
void Camera::createPixelRays(int x, int y) 
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex( 0, x*pixelWidth - (viewWidth / 2), y*pixelHeight - (viewHeight / 2));

	//Create ray for the pixel
	Ray *myRay = new Ray(startPosition, pixelPosition);


	//connect the ray to that pixel.
	pixels[x + pixelsVericaly * y].connectRay(myRay);
}