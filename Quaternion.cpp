//
// Created by Asda Tapel on 2/4/17.
//

#include "Quaternion.h"

Quaternion::Quaternion(){
	_x = 0;
	_y = 0;
	_z = 0;
	_w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

Quaternion::Quaternion(sf::Vector3f axis, float angle) {
	axis = Math::normalize(axis);
	_x = axis.x * std::sin(angle / 2);
	_y = axis.y * std::sin(angle / 2);
	_z = axis.z * std::sin(angle / 2);
	_w = std::cos(angle / 2);
}

Quaternion Quaternion::conjugate() {
	return Quaternion(-_x, -_y, -_z, _w);
}

Quaternion Quaternion::operator*(const Quaternion &q) {
	return Quaternion(_w * q._x + _x * q._w + _y * q._z - _z * q._y,
					  _w * q._y - _x * q._z + _y * q._w + _z * q._x,
					  _w * q._z + _x * q._y - _y * q._x + _z * q._w,
					  _w * q._w - _x * q._x - _y * q._y - _z * q._z);
}

sf::Vector3f Quaternion::operator*(const sf::Vector3f &v) {
	Quaternion temp(v.x, v.y, v.z, 0);
	Quaternion result = ((*this) * temp) * this->conjugate();

	return sf::Vector3f(result._x, result._y, result._z);
}