// Course: TNCG15, Advanced global illumination and rendering
// Date: 2019-09-26
// Author: Martin Hag

#include "pch.h"
#include <iostream>
#include "SFML/Graphics.hpp"

#include "myColor.h"
#include "Scene.h"
#include "Camera.h"

namespace CONSTANTS
{
	const int   screenSize_X = 800;
	const int   screenSize_Y = 800;
}

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

//updates window.
void updateWindow(sf::RenderWindow &_window, sf::Sprite &_sprite, sf::Texture &_texture, sf::Image &_image)
{
	_texture.loadFromImage(_image);
	_window.draw(_sprite);        // just draw it to the back buffer
	_window.display();
}

/************************
*			Main		*
*************************/
int main()
{
	std::cout << "Setup window...\n";
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

	int renderCounter = 0;
	std::cout << "Starting rendering process\n";
	for (int y = 0; y < CONSTANTS::screenSize_Y; y++) { //Vertical
		for (int x = 0; x < CONSTANTS::screenSize_X; x++) { //Horizontal
			
			//Create ray to the pixel.
			camera.createPixelRays(x, y);

			//Get pointer to the pixel
			Pixel *activePixel = &camera.pixels[x + CONSTANTS::screenSize_Y* y];

			//Give the ray of the pixel the color of what it hits.
			scene.intersection(activePixel->ray);

			//Give the pixel color from its ray.
			activePixel->color = activePixel->ray->color;

			//Extract color from double to integer.
			sf::Color color = activePixel->color.toSFLinear(0,255);

			//set pixel in image.
			image.setPixel(x, y, color);
		}
		renderCounter++;
		if (renderCounter == 10)
		{
			//Draw all pixels.
			updateWindow(window, sprite, texture, image);
			renderCounter = 0;
		}
	}

	updateWindow(window, sprite, texture, image);
	std::cout << "Render Complete!\n";
	loopUpdate(window, sprite);
	int a;
	std::cin >> a;
}
