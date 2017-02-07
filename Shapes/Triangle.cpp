//
// Created by Asda Tapel on 2/2/17.
//

#include "Triangle.h"

Triangle::Triangle(sf::Vector3f vertex1, sf::Vector3f vertex2, sf::Vector3f vertex3) {
	_vertices[0] = vertex1;
	_vertices[1] = vertex2;
	_vertices[2] = vertex3;

	_normal = Math::cross(vertex2 - vertex1, vertex3 - vertex1);
	_distance_from_origin = Math::dot(_normal, vertex1);
}

std::pair<bool, RayCollision> Triangle::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {

	float parallel = Math::dot(_normal, ray_velocity);
	if (std::fabs(parallel) < 0.000000000001) {
		return {false, {}};
	}

	RayCollision collision;
	collision.normal = Math::normalize(_normal);

	collision.t = (_distance_from_origin - Math::dot(_normal, ray_origin)) / parallel;
	if (collision.t < 0){
		return {false, {}};
	}

	collision.position = ray_origin + ray_velocity * collision.t;

	for (int i = 0; i < 3; ++i)
	{
		sf::Vector3f edge = _vertices[i] - _vertices[(i + 2) % 3];
		sf::Vector3f vp = collision.position - _vertices[(i + 2) % 3];;
		sf::Vector3f perpendicular = Math::cross(edge, vp);
		if (Math::dot(_normal, perpendicular) < 0) {
			return {false, {}};
		}
	}

	return {true, collision};
};
