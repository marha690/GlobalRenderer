#include "pch.h"
#include "Camera.h"

Camera::Camera(int pxX, int pxY, Eye eye = Eye::EYE_ONE)
{
	//Insert variables from parameters.
	pixelsVericaly = pxX;
	pixelsHorizontaly = pxY;
	selectedEye = eye;

	if (eye == Eye::EYE_ONE) {
		startPosition = eye1;
	}
	else {
		startPosition = eye2;
	}

	totalPixels = pixelsVericaly * pixelsHorizontaly;
	pixels = new Pixel[totalPixels];

}

Camera::~Camera() {
	delete pixels;
}

//Connects pixel with the rays which is projected inside it.
void Camera::createPixelRays(int x, int y) 
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex(x*pixelWidth - viewHeight, y*pixelHeight - viewWidth, 0);

	//Create ray for the pixel
	Ray *myRay = new Ray(startPosition, pixelPosition);

	//connect the ray to that pixel.
	pixels[x + pixelsVericaly * y].connectRay(myRay);
}