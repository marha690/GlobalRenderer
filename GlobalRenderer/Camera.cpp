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
			Ray *ray;
			ray = createPixelRays(x, y); //Create rays for the pixel.

			s->intersection(ray); //Checks if it intersects


			Ray *shadowRay = new Ray(ray->getEnd(), s->lightsource.position);

			if(s->isIntersected(shadowRay))
				ray->setColor(Color(0,0,0));

			//FakeLight: the faces which is at the direction of the light is stonger that those which are not. With witted ray trcing.
			//this does not make sence so i think i have implemented it wrong.
			bool useThis = false;
			if(useThis)
			{
				IntersectionData *data = ray->getHitData();
				if (!data) { // Safe for dead pixels.
					continue;
				}

				Direction Z = glm::normalize(data->normal);
				Direction I = glm::normalize(Direction(ray->getDirection().x, ray->getDirection().y, ray->getDirection().z));
				Direction IT = I - glm::dot(I, Z) * Z;
				Direction X = IT / glm::abs(IT);
				Direction Y = glm::cross(-X, Z);
				glm::mat4 Tr = glm::translate(glm::mat4(1.0), glm::vec3(ray->getEnd().x, ray->getEnd().y, ray->getEnd().z));

				Vertex u = Tr * shadowRay->getDirection();
				Vertex N = Vertex(0, 0, 1, 1); //Normal in Local coordinate system.
				//std::cout << u.x << ", " << u.y << ", " << u.z << ".\n";
				double num = glm::dot(u, N);
				double det = (u.length() * N.length());
				double angle = (num / det);
				double kd = 2;
				ray->setColor(ray->getColor() * kd * angle);
			}
			
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