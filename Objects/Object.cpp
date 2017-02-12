//
// Created by Asda Tapel on 2/3/17.
//

#include "Object.h"

Object::Object(sf::Vector3f position) {
	_position = position;
	_rotation = Quaternion({0.0f, 0.0f, 1.0f}, 0);
}
