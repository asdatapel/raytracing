//
// Created by Asda Tapel on 2/3/17.
//

#ifndef RAYTRACING_WALL_H
#define RAYTRACING_WALL_H

#include <SFML/System/Vector3.hpp>

#include "Object.h"
#include "Shapes/Sphere.h"
#include "Shapes/Triangle.h"

class Wall : public Object{
public:
	Wall(sf::Vector3f position);
	~Wall();

	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:
	Shape* _shape;
};


#endif //RAYTRACING_WALL_H
