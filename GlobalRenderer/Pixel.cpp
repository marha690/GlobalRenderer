#include "pch.h"
#include "Pixel.h"


Pixel::Pixel()
{
	color = Color(0, 0, 0);
}

void Pixel::setColor(Color _color)
{
	color = _color;
}
