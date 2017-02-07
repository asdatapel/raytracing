//
// Created by Asda Tapel on 2/2/17.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include <SFML/System.hpp>

#include "Ray.h"

class Shape {
public:
	Shape(){};

	virtual std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity){return {false, {}};};
};


#endif //RAYTRACING_OBJECT_H
