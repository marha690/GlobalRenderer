// Course: TNCG15, Advanced global illumination and rendering
// Date: 2019-09-26 - 2019-12-16
// Author: Martin Hag

#include "pch.h"
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Scene.h"
#include "Camera.h"

#include "Definitions.h"


// Loop if i want to use it in main later. Code has to be in while loop to update.
void loopUpdate(sf::RenderWindow &_window, sf::Sprite &_sprite)
{
	// Set FPS so this draws at 60 FPS (note:  I didn't do this for the WinAPI version because it'd be too hard for such
//  a small example)
	_window.setFramerateLimit(60);

	bool program_running = true;        // true until the user wants to quit
	while (program_running)
	{
		// Do the event pump -- same idea as with Windows... look for events and process them
		sf::Event evt;
		while (_window.pollEvent(evt))      // while there are any events to process...
		{
			// process them. But we're only interested in the closed event
			if (evt.type == sf::Event::EventType::Closed)        // is this a close event?
				program_running = false;                        // indicate that we want the window to close
		}

		// now that events are processed... draw our image
		_window.draw(_sprite);        // just draw it to the back buffer
		_window.display();           // and display it so the back buffer moves to the front
	}
}

sf::Color toSFLinear(Color c, double min, double max ) {

	//Normalize colors
	double red = (c.r - min) / (max); //Norm between 0 and 1.
	double green = (c.g - min) / (max); //Norm between 0 and 1.
	double blue = (c.b - min) / (max); //Norm between 0 and 1.

	//Make them to range between 0 and 255 (8bits since sf::Color has 8bits color-input).
	red *= 255;
	green *= 255;
	blue *= 255;

	return sf::Color((int)red, (int)green, (int)blue);
}


sf::Color toSFLog(Color c, double min, double max) {

	//Normalize colors
	double red = log(c.r - min) / log(max); //Norm between 0 and 1.
	double green = log(c.g - min) / log(max); //Norm between 0 and 1.
	double blue = log(c.b - min) / log(max); //Norm between 0 and 1.

	//Make them to range between 0 and 255 (8bits since sf::Color has 8bits color-input).
	red *= 255;
	green *= 255;
	blue *= 255;

	return sf::Color((int)red, (int)green, (int)blue);
}


//updates window.
void updateWindow(sf::RenderWindow &_window, sf::Sprite &_sprite, sf::Texture &_texture, sf::Image &_image)
{
	_texture.loadFromImage(_image);
	_window.draw(_sprite);        // just draw it to the back buffer
	_window.display();
}


void setImagePixels(sf::Image &_image, Camera &camera, double min, double max)
{
	for (int y = 0; y < CONSTANTS::screenSize_Y; y++) {
		for (int x = 0; x < CONSTANTS::screenSize_X; x++) {
			Color internalColor = camera.pixels[x + CONSTANTS::screenSize_Y* y].color;

			sf::Color color = toSFLinear(internalColor, 0, max); // convert colors in schene to 8bits
			_image.setPixel(x, y, color);
		}
	}
}
/************************
*			Main		*
*************************/
int main()
{
	// Create our window
	sf::RenderWindow window(
		sf::VideoMode(CONSTANTS::screenSize_X, CONSTANTS::screenSize_Y),       // size of the client area we want
		"Display an Image"                              // The text to appear on the window title
	);
	// load our image
	sf::Texture     texture;        // the texture which will contain our pixel data
	sf::Sprite      sprite;         // the sprite which will actually draw it
	sf::Image		image;
	sprite.setTexture(texture);         // put that texture in our sprite
	sprite.setTextureRect(sf::IntRect(0, 0, CONSTANTS::screenSize_X, CONSTANTS::screenSize_Y));    // the rectangle of the texture to use for this sprite
	image.create(CONSTANTS::screenSize_X, CONSTANTS::screenSize_Y, sf::Color::Cyan);
	//Create scene with objects.
	Scene scene = Scene();
	//Create camera in scene.
	Camera camera = Camera(CONSTANTS::screenSize_X, CONSTANTS::screenSize_Y, Camera::Eye::EYE_TWO);


	//Render.
	std::cout << "Starting rendering process. Size[" << CONSTANTS::screenSize_X 
		<< "x" << CONSTANTS::screenSize_Y << "].\n";

	camera.render(&scene);

	//camera.setInternalPixelColors();

	setImagePixels(image, camera,0, camera.maxColorValue());
	std::cout << "Max color value in the scene:" << camera.maxColorValue() << "\n";
	updateWindow(window, sprite, texture, image);

	std::cout << "Image finished.\n";
	loopUpdate(window, sprite); //Loop render window
}
