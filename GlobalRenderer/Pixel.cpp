#include "pch.h"
#include "Pixel.h"


Pixel::Pixel()
{
	color = Color(250, 0, 250);
}

void Pixel::setColor(Color _color)
{
	color = _color;
}

void Pixel::connectRay(Ray *_ray)
{
	ray = _ray;
}