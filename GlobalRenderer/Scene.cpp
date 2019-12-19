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

	sphere2 = Sphere(Vertex(5, 2, -2, 1), 1.0, COLOR::RED, SurfaceType::OrenNayar);
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
	intersection(ray);

	//Fail save for the bug where the ray does not hit a surface.
	if (!ray->getHitData())
		return COLOR::BLACK;

	switch (ray->getHitData()->sufaceType)
	{
	case Specular:
	{
		return tracePath(&ray->perfectBounce());
		break;
	}
	case Lambertian:
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
				double lightAngle = glm::max(glm::dot(light, normal), 0.0);

				// Render equation.
				color += BRDF * lightAngle * (ray->getColor() * 0.01) * lightsource.color /  (double)CONSTANTS::SHADOW_RAYS;
			}
		}

		return color;
		break;
	}
	case OrenNayar:
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

				// The oren nayar lightning model.
				Direction light = Direction(shadowRay.getDirection());
				Direction normal = ray->getHitData()->normal;
				Direction view = ray->getDirection();

				double deviance = 1.0; // Irregularities on the surface.
				double roughness = deviance * deviance;

				// Angles
				double inclinationLight = acos(glm::dot(normal, light));
				double inclinationView = acos(glm::dot(normal, view));
				Direction azimuthLight = light - normal * glm::dot(light, normal); //Vector on the azimuth plane.
				Direction azimuthView = view - normal * glm::dot(view, normal); //Vector on the azumuth plane.
				double azimuthDiff = (glm::dot(azimuthView, azimuthLight) ); // the angle between Light and View on the azimuth plane.


				double A = 1.0 - (0.5 * roughness) / (roughness + 0.33);
				double B = (0.45 * roughness) / (roughness + 0.09);
				double alpha = std::max(inclinationLight, inclinationView);
				double beta = std::min(inclinationLight, inclinationView);

				double orenNayar = (A + B * std::max(0.0, azimuthDiff) * sin(alpha) * tan(beta));
				double lightAngle = glm::max(glm::dot(normal, light), 0.0);
				// Render equation.
				color += BRDF * lightAngle * orenNayar * (ray->getColor() * 0.01) * lightsource.color / (double)CONSTANTS::SHADOW_RAYS;
			}
		}

		return color;
		break;

	}
	case Transparent:
	{
		// Make into material class later.
		// This code does not work as expected. 
		double n1 = 1;
		double n2 = 1.3;
		double refractionI = n1 / n2;

		Direction in = glm::normalize(ray->getDirection());
		Direction normal = glm::normalize(ray->getHitData()->normal);

		if (glm::dot(normal, in) < 0) // the normal is at the wrong angle.
		{
			normal = - normal;
		}

		double theta = acos(glm::dot(normal, in));

		// Approximative fresnel model.
		double r0 = (n1 - n2) / (n1 + n2);
		double R0 = r0 * r0;
		double fresnel = R0 + (1 - R0) * glm::pow(1 - glm::dot(normal, in),5);
		double T = 1 - fresnel;

		//std::cout << theta*180/CONSTANTS::PI << ", " << std::endl;

		// Set no refraction if Brewster angle criteria is met.
		if (cos(theta) > asin(n2 / n1)) {
			std::cout << "No refraction should be done." << std::endl;
		}

		//return 0.5 * tracePath(&ray->perfectBounce()) + 0.5 * tracePath(&ray->refractedBounce(refractionI));
		return fresnel * tracePath(&ray->perfectBounce()) + T * tracePath(&ray->refractedBounce(refractionI));
		break;
	}
	case Light:
	{
		return ray->getColor();
		break;
	}
	default:
		break;
	}

	return COLOR::BLACK;
}