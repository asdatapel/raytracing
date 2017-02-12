//
// Created by Asda Tapel on 2/3/17.
//

#ifndef RAYTRACING_BALL_H
#define RAYTRACING_BALL_H

#include <SFML/System/Vector3.hpp>

#include "Object.h"
#include "Shapes/Sphere.h"
#include "Shapes/Triangle.h"

class Ball : public Object {
public:
	Ball(sf::Vector3f position);
	~Ball();

	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:
	sf::Image _reflectivity_map;
	Shape *_shape;
};


#endif //RAYTRACING_BALL_H
