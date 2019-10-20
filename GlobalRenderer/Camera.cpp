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

			//First ray!
			Ray *ray = createPixelRay(x, y); //Create rays for the pixel.
			s->intersection(ray); 



			if (ray->getHitData()) {
				Ray *temp = ray;

				//Specular surface!
				int c = 0; //Simple way to stop rays from being infinitive amount.
				while (ray->getHitData() && ray->getHitData()->sufaceType == Surface::specular && c < 5) {
					
					ray->reflectedRay = ray->perfectBounce();
					s->intersection(ray->reflectedRay);


					ray = ray->reflectedRay;
					ray->parent = temp;
					temp = ray;
					c++;
				}
				


				//We have found our rays. Make a shadow ray for the last hit.
				Ray *shadowRay = new Ray(temp->getEnd(), s->lightsource.position);
				if (s->isIntersected(shadowRay)) {
					temp->setColor(Color(0, 0, 0));
				} 
				else {

					//Make Lambertian reflection?

					double p = 0.6; //Between 0 and 1.
					double BRDF = p / CONSTANTS::PI;

					Direction light = glm::normalize(Direction(shadowRay->getDirection()));
					Direction normal = glm::normalize(temp->getHitData()->normal);

					double cosAngle = glm::dot(light, normal);

					if (cosAngle < 0)
						cosAngle = 0;

					double L = BRDF * s->lightsource.L0 * cosAngle;
					//std::cout << "Angle: " << cosAngle << std::endl;
					temp->setColor(temp->getColor() * L);
				}
			}

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

Color Camera::getColorForPixel(Pixel *p) {

	Color pixelColor = Color(0, 0, 0);

	//Retrieve value from ray to give the pixel its color.
	Ray *temp = p->ray;

	//Get last ray in the tree.
	while (temp->reflectedRay) {
		temp = temp->reflectedRay;
	}


	pixelColor = temp->getColor(); //Get the color of the last ray.

	////Adds a small diffuse thing to every ray.
	//while (temp->parent) {
	//	temp = temp->parent;

	//	pixelColor = pixelColor + temp->getColor() * 0.03;
	//}



	return pixelColor;
}