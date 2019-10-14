#include "pch.h"
#include "Camera.h"

#include <cmath>

#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>

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
			Ray *ray;
			ray = createPixelRays(x, y); //Create rays for the pixel.

			s->intersection(ray); //Checks if it intersects

			//Calculations for light.

			// from traingle to lightsource.
			//Ray *shadowRay = new Ray(ray->getEnd(), s->lightsource.position);


			//// Give ray no color if the target is in shadows!
			//if(s->isIntersected(shadowRay))
			//	ray->setColor(Color(0,0,0));


			////localLightContribution:
			//Triangle *triangle = ray->getTriangle();

			//if (!triangle) {
			//	continue;
			//	//std::cout << "ray does not hit a triangle.\n";
			//}

			//Vertex Z = glm::normalize(triangle->getNormal());
			//Vertex IT = glm::normalize(ray->getDirection()) - (glm::normalize(ray->getDirection()) * Z) * Z;
			//Vertex X = IT / glm::abs(IT);
			//Vertex Y = (-1 * X)^ Z;

			//glm::mat4x4 local{ X.x, X.y, X.z, 0, Y.x, Y.y, Y.z, 0, Z.x, Z.y, Z.z, 0, 0, 0, 0, 1};
			//glm::mat4x4 translation{0, 0, 0, -(ray->getEnd().x),
			//					    0, 1, 0, -(ray->getEnd().y),
			//					    0 ,0 , 1, -(ray->getEnd().z),
			//					    0, 0 ,0 ,1};

			//glm::mat4x4 M = local * translation;


			//Vertex u = Z.normalize();
			//Vertex v = shadowRay->getDirection().normalize();
			////std::cout << "shadowray: " << v << ".\n";
			////std::cout << "Triangle normal: " << u << ".\n";

			//double angle = std::acos((u * v) / (u.magnitude() * v.magnitude()));
			////std::cout << "acos: " << angle << ".\n";

			//double kd = 2;

			//if (angle > 3.14 / 2) {
			//	ray->setColor(ray->getColor() * kd * angle);
			//}



		}
		std::cout << "\rProgress: " << (y / (pixelsVericaly / 100)) << "%";
	}
		std::cout << "\rProgress: 100%\n";
}

//Connects pixel with the rays which is projected inside it.
Ray* Camera::createPixelRays(int x, int y) 
{
	double pixelWidth = (double(viewWidth) / double(pixelsHorizontaly));
	double pixelHeight = (double(viewHeight) / double(pixelsVericaly));

	Vertex pixelPosition = Vertex( 0, (viewWidth / 2) - x*pixelWidth, (viewHeight / 2) - y*pixelHeight, 1);

	//Create ray for the pixel
	Ray *myRay = new Ray(startPosition, pixelPosition);
	Vertex end = glm::normalize(myRay->getDirection());
	myRay->setEnd( end *= 1000, nullptr );

	//Connect the ray to that pixel.
	pixels[x + pixelsVericaly * y].connectRay(myRay);
	return myRay;
}

double Camera::maxColorValue()
{
	double max = 0;
	for (int y = 0; y < pixelsVericaly; y++) {
		for (int x = 0; x < pixelsHorizontaly; x++) {
			Color c = pixels[x + pixelsVericaly * y].ray->getColor();

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
			pixels[x + pixelsVericaly * y].color = pixels[x + pixelsVericaly * y].ray->getColor();
		}
	}
}