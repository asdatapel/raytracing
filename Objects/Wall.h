//
// Created by Asda Tapel on 2/10/17.
//

#ifndef RAYTRACING_WALL_H
#define RAYTRACING_WALL_H

#include "Object.h"
#include "Shapes/Triangle.h"

class Wall : public Object{
public:
	Wall(sf::Vector3f position, sf::Vector2f size, std::string texture_name);
	~Wall();

	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:

	Triangle* _t1;
	Triangle* _t2;
};


#endif //RAYTRACING_WALL_H
