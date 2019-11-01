#include "pch.h"
#include "Scene.h"
#include "Sphere.h"
#include "Room.h"

#include <random>

// Constructor
Scene::Scene()
{
	tetrahedron = Tetrahedron(Vertex(5, 2, 0, 1), COLOR::LIGHTRED);

	sphere = Sphere(Vertex(4, -2, -2, 1), 1.5, COLOR::LIGHTGREEN, SurfaceType::Specular);

	lightsource = Lightsource(Vertex(5, 0, 4.9999f, 1));

	sphere2 = Sphere(Vertex(5, 2, -2, 1), 1, COLOR::RED, SurfaceType::Lambertian);
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
	lightsource.rayInterSection(*ray);
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

	//Lightsource
	if (lightsource.rayInterSection(*ray))
		return true;

	return false;
}

//Recursion for the ray tree, return the color from that ray.
Color Scene::tracePath(Ray *ray) 
{
	Color black = COLOR::BLACK;
	intersection(ray);

	//Fail save for the bug where the ray does not hit a surface.
	if (!ray->getHitData())
		return black;

	switch (ray->getHitData()->sufaceType)
	{
	case SurfaceType::Specular:
	{
		return tracePath(&ray->perfectBounce());
		break;
	}

	case SurfaceType::Lambertian:
	{
		Color color = COLOR::BLACK;

		std::random_device randomDevice;
		std::default_random_engine gen(randomDevice());
		std::uniform_real_distribution<> dis(0.0, 1.0);

		double p = 0.8; //Between 0 and 1.
		double BRDF = p / CONSTANTS::PI;

		if (dis(gen) > CONSTANTS::RAY_ABSOPTIONRATE) {
			color = tracePath(&ray->randomBounce());
			color *= BRDF;
		}

		//Shadow rays. Give the ray color if the surface is lit.
		for (int i = 0; i < CONSTANTS::SHADOW_RAYS; i++)
		{
			Ray shadowRay = Ray(ray->getEnd(), lightsource.getRandomPoint());

			if (!isIntersected(&shadowRay)) {
				Direction light = Direction(shadowRay.getDirection());
				Direction normal = ray->getHitData()->normal;

				//Angle between surface normal and lightsource.
				double lightAngle = glm::dot(light, normal);
				if (lightAngle < 0)
					lightAngle = 0;

				color += BRDF * lightAngle * ray->getColor() * lightsource.color /  (double)CONSTANTS::SHADOW_RAYS;
			}
		}

		return color;
		break;
	}
	case SurfaceType::Light:
	{
		//return ray->getColor();
		return Color(32222); //Ugly implementation to increase light value.
		break;
	}
	default:
		break;
	}

	return black;
}


//test
Color Scene::getLightContribution(Vertex rayEnd, Direction surfaceNormal) {

	Color color{ COLOR::BLACK };

	int hit = 0;
	//Shadow rays. Give the ray color if the surface is lit.
	for (int i = 0; i < CONSTANTS::SHADOW_RAYS; i++)
	{
		Ray shadowRay = Ray(rayEnd, lightsource.getRandomPoint());

		if (!isIntersected(&shadowRay)) {
			++hit;
		}
	}
	double scalar = hit / CONSTANTS::SHADOW_RAYS;

	return color;
}