#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Renderer.h"
#include "Quaternion.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

//#define TARGET_WIDTH 1920
//#define TARGET_HEIGHT 1080
#define TARGET_WIDTH 320
#define TARGET_HEIGHT 180

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raytracing", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::Image image;
	sf::Texture tex;
	image.create(TARGET_WIDTH, TARGET_HEIGHT, sf::Color::Blue);
	tex.loadFromImage(image);


	sf::Sprite sprite(tex);

	sprite.setPosition(0, 0);
	sprite.setTexture(tex);
	sprite.setScale(WINDOW_WIDTH / TARGET_WIDTH, WINDOW_HEIGHT / TARGET_HEIGHT);


	World world;
	world.init();
	Renderer renderer;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					renderer.camera_distance -= 0.01f;
				} else if (event.key.code == sf::Keyboard::S) {
					renderer.camera_distance += 0.01f;
				} else if (event.key.code == sf::Keyboard::D) {
					renderer.camera_pos.x += 0.05;
				} else if (event.key.code == sf::Keyboard::A) {
					renderer.camera_pos.x -= 0.05;
				}
			}
		}

		image.create(TARGET_WIDTH, TARGET_HEIGHT, sf::Color::Cyan);
		world.update();
		renderer.drawWorld(&image, &world);

		tex.update(image);
		window.draw(sprite);

		window.display();
	}

	return 0;
}