//
// Created by Asda Tapel on 2/3/17.
//

#ifndef RAYTRACING_ASDF_H
#define RAYTRACING_ASDF_H

#include <SFML/System.hpp>
#include <ext/SFML/include/SFML/Graphics.hpp>

#include "Ray.h"
#include "Quaternion.h"

class Object {
public:
	Object(sf::Vector3f position);

	virtual std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity){return {false, {}};};

	sf::Vector3f _position;
	Quaternion _rotation;
	sf::Vector3f _velocity;

	sf::Image _texture;
};


#endif //RAYTRACING_ASDF_H
