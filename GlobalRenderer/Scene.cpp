#include "pch.h"
#include "Scene.h"
#include "Sphere.h"
#include "Room.h"

#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <matrix_transform.hpp>

#include <random>

// Constructor
Scene::Scene()
{

	tetrahedron = Tetrahedron(Vertex(5, 2, 0, 1), lightRed);

	sphere = Sphere(Vertex(4, -2, -2, 1), 1.5, lightGreen, Surface::specular);

	lightsource = Lightsource(Vertex(5, 0, 4.9, 1));

	sphere2 = Sphere(Vertex(5, 2, -1, 1), 0.5, lightGreen, Surface::diffuse);
}

// Destructor
Scene::~Scene()
{
}

void Scene::intersection(Ray *ray)
{
	//Room
	room.rayIntersection(*ray);

	//Tetrahedron
	tetrahedron.rayIntersection(*ray);

	//Sphere
	sphere.rayIntersection(*ray);
	sphere2.rayIntersection(*ray);

	//Lightsource
	//lightsource.rayInterSection(*ray);

}

bool Scene::isIntersected(Ray *ray)
{
	//Room
	if (room.rayIntersection(*ray))
		return true;

	//Tetrahedron
	if (tetrahedron.rayIntersection(*ray))
		return true;

	//Sphere
	if (sphere.rayIntersection(*ray))
		return true;
	if (sphere2.rayIntersection(*ray))
		return true;


	return false;
}


Color Scene::tracePath(Ray *ray) 
{
	Color black = Color(0, 0, 0);

	intersection(ray);

	if (!ray->getHitData())
		return black;

	
	if (ray->getHitData()->sufaceType == Surface::specular) {
		//Specular

		return tracePath(ray->perfectBounce());


	}
	else if(ray->getHitData()->sufaceType == Surface::diffuse) {
		//Labertian

		Color color = ray->getColor();

		//Absorbtion change of the surface. 0.5
		//Importance = 0.3
		std::random_device randomDevice;
		std::default_random_engine gen(randomDevice());
		std::uniform_real_distribution<> dis(0.0, 1.0);


		//makes half the rays beeing absorbed.
		if (dis(gen) > 0.5) {
			color = tracePath(ray->randomBounce());
			color *= 0.4;  //Importance scalar.
		}

		//Shadow sample rays
		for (int i = 0; i < 2; i++)
		{
			Ray *shadowRay = new Ray(ray->getEnd(), lightsource.getRandomPoint());

			if (isIntersected(shadowRay))
				continue;


			double p = 0.8; //Between 0 and 1.
			double BRDF = p / CONSTANTS::PI;

			Direction light = glm::normalize(Direction(shadowRay->getDirection()));
			Direction normal = glm::normalize(ray->getHitData()->normal);

			double cosAngle = glm::dot(light, normal);

			if (cosAngle < 0)
				cosAngle = 0;

			double L = BRDF * cosAngle;

			color += L * lightsource.L0 * ray->getColor();
		}
		return color;
	}
	else
	{
		std::cout << "OOPSIE! YOU SHOULD NOT SEE THIS MESSAGE :S\n";
		return black;
	}


	return black; //Not reachable.
}

