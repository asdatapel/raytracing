//
// Created by Asda Tapel on 2/3/17.
//

#ifndef RAYTRACING_ASDF_H
#define RAYTRACING_ASDF_H

#include <SFML/System.hpp>

#include "Ray.h"
#include "Quaternion.h"

class Object {
public:
	Object(sf::Vector3f position);

	virtual std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity){return {false, {}};};

	sf::Vector3f _position;
	Quaternion _rotation;
	sf::Vector3f _velocity;
};


#endif //RAYTRACING_ASDF_H
