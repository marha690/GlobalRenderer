#include "pch.h"
#include "Pixel.h"


Pixel::Pixel()
{
	color = MyColor(250, 0, 250);
}

void Pixel::setColor(MyColor _color)
{
	color = _color;
}

void Pixel::connectRay(Ray *_ray)
{
	ray = _ray;
}