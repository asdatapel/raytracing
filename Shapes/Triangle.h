//
// Created by Asda Tapel on 2/2/17.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H

#include <SFML/System.hpp>

#include "MathHelper.h"
#include "Ray.h"
#include "Shape.h"

class Triangle : public Shape {
public:
	Triangle(sf::Vector3f vertex1, sf::Vector3f vertex2, sf::Vector3f vertex3);

	//check if a ray collides and return the distance from the ray origin
	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:
	sf::Vector3f _vertices[3];
	sf::Vector3f _normal;
	float _distance_from_origin;
};


#endif //RAYTRACING_TRIANGLE_H
