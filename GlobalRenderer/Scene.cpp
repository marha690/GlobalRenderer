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

	sphere = Sphere(Vertex(4, -2, -2, 1), 1.5, lightGreen, SurfaceType::Specular);

	lightsource = Lightsource(Vertex(5, 0, 5, 1));

	sphere2 = Sphere(Vertex(5, 2, -1, 1), 0.5, lightGreen, SurfaceType::Lambertian);
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

//Recursion for the ray tree, return the color from that ray.
Color Scene::tracePath(Ray *ray) 
{
	Color black = Color(0, 0, 0);
	intersection(ray);

	//Fail save for the bug where the ray does not hit a surface.
	if (!ray->getHitData())
		return black;

	switch (ray->getHitData()->sufaceType)
	{
	case SurfaceType::Specular:
		return tracePath(ray->perfectBounce());
		break;

	case SurfaceType::Lambertian:

		Color color = Color(0.0);

		std::random_device randomDevice;
		std::default_random_engine gen(randomDevice());
		std::uniform_real_distribution<> dis(0.0, 1.0);

		double p = 0.8; //Between 0 and 1.
		double BRDF = p / CONSTANTS::PI;

		if (dis(gen) > CONSTANTS::RAY_ABSOPTIONRATE) {
			color = tracePath(ray->randomBounce());
			color *= CONSTANTS::IMPORTANCE_SCALAR;
		}

		//Shadow rays. Give the ray color if the surface is lit.
		int shadowRays = 3;
		for (int i = 0; i < shadowRays; i++)
		{
			Ray *shadowRay = new Ray(ray->getEnd(), lightsource.getRandomPoint());

			if (!isIntersected(shadowRay)) {

				Direction light = glm::normalize(Direction(shadowRay->getDirection()));
				Direction normal = glm::normalize(ray->getHitData()->normal);

				double cosAngle = glm::dot(light, normal);

				if (cosAngle < 0)
					cosAngle = 0;

				double L = BRDF * cosAngle;
				color += L * lightsource.L0 * ray->getColor();
			}
			delete shadowRay;
		}
		return color;
		break;
	}

	return black;
}


