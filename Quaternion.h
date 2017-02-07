//
// Created by Asda Tapel on 2/4/17.
//

#ifndef RAYTRACING_QUATERNION_H
#define RAYTRACING_QUATERNION_H

#include <cmath>

#include <SFML/System/Vector3.hpp>

#include "MathHelper.h"

class Quaternion {
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(sf::Vector3f axis, float angle);

	Quaternion conjugate();

	Quaternion operator *(const Quaternion& q2);
	sf::Vector3f operator *(const sf::Vector3f& v);

private:
	float _x, _y, _z, _w;
};


#endif //RAYTRACING_QUATERNION_H
