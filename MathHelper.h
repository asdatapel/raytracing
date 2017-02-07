//
// Created by Asda Tapel on 1/31/17.
//

#ifndef RAYTRACING_MATH_H
#define RAYTRACING_MATH_H

#include <cmath>

#include <SFML/System.hpp>

namespace Math {

	//solves quadratic function and return lower x
	std::pair<bool, float> solveQuadratic(const float a, const float b, const float c);

	//dot product
	float dot(const sf::Vector3f& v1, const sf::Vector3f& v2);
	//cross product
	sf::Vector3f cross(const sf::Vector3f& v1, const sf::Vector3f& v2);

	//convert vector to unit vector
	sf::Vector3f normalize(const sf::Vector3f& v);
	sf::Vector3f abs(const sf::Vector3f& v);
}


#endif //RAYTRACING_MATH_H
