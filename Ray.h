//
// Created by Asda Tapel on 2/2/17.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>

struct RayCollision{
	float t;
	float distance;
	sf::Color diffuse_color;
	sf::Vector3f position;
	sf::Vector3f normal;
	sf::Vector2f bary_coords;
	sf::Vector2f texture_coords;
	float _reflectivity;
};


class Ray {

};


#endif //RAYTRACING_RAY_H
