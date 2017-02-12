//
// Created by Asda Tapel on 2/2/17.
//

#include "Triangle.h"

Triangle::Triangle(sf::Vector3f vertex1, sf::Vector3f vertex2, sf::Vector3f vertex3, sf::Vector2f uv1, sf::Vector2f uv2,
				   sf::Vector2f uv3) {
	_vertices[0] = vertex1;
	_vertices[1] = vertex2;
	_vertices[2] = vertex3;

	_uv[0] = uv1;
	_uv[1] = uv2;
	_uv[2] = uv3;

	_normal = Math::cross(vertex3 - vertex1, vertex2 - vertex1);
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
	if (collision.t < 0) {
		return {false, {}};
	}

	collision.position = ray_origin + ray_velocity * collision.t;

	float area = Math::length(_normal) * 0.5f;
	for (int i = 0; i < 3; ++i) {
		sf::Vector3f edge = _vertices[i] - _vertices[(i + 2) % 3];
		sf::Vector3f vp = collision.position - _vertices[(i + 2) % 3];;
		sf::Vector3f perpendicular = Math::cross(edge, vp);

		if (i == 2) { //side 2
			collision.bary_coords.x = Math::length(perpendicular) / (2 * area);
		} else if (i == 0) { //side 3
			collision.bary_coords.y = Math::length(perpendicular) / (2 * area);
		}

		if (Math::dot(_normal, perpendicular) > 0) {
			return {false, {}};
		}
	}

	collision.texture_coords = (collision.bary_coords.x * _uv[0] + collision.bary_coords.y * _uv[1] +
							   (1 - collision.bary_coords.x - collision.bary_coords.y) * _uv[2]);

	return {true, collision};
};
