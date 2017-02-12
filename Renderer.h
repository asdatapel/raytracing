//
// Created by Asda Tapel on 1/31/17.
//

#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <SFML/Graphics.hpp>

#include "MathHelper.h"
#include "World.h"

class Renderer {
public:
	Renderer();

	void drawWorld (sf::Image* image, World* world);

	sf::Vector3f camera_pos = {0,0,0};
	float camera_distance = 0.5f;

	sf::Image t;
	bool t_loaded = false;

};


#endif //RAYTRACING_RENDERER_H
