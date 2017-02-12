//
// Created by Asda Tapel on 1/31/17.
//

#ifndef RAYTRACING_WORLD_H
#define RAYTRACING_WORLD_H

#include <vector>

#include <SFML/System.hpp>

#include "Ray.h"
#include "Objects/Box.h"
#include "Objects/Wall.h"
#include "Objects/Ball.h"


class World {
public:
	~World();

	void init();

	//return closest intersection distance
	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);

	void update();

private:
	std::vector<Object*> _objects;
};


#endif //RAYTRACING_WORLD_H
