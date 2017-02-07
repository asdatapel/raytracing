//
// Created by Asda Tapel on 1/31/17.
//

#include "Sphere.h"

Sphere::Sphere(float radius) {
	_radius = radius;
}

std::pair<bool, RayCollision> Sphere::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {
	float a = Math::dot(ray_velocity, ray_velocity);
	float b = 2 * Math::dot(ray_velocity, ray_origin);
	float c = Math::dot(ray_origin, ray_origin) - (_radius * _radius);

	auto solved_t = Math::solveQuadratic(a, b, c);
	if (!solved_t.first || solved_t.second < 0) {
		return {false, {}};
	}

	RayCollision collision;
	collision.t = solved_t.second;
	collision.position = ray_origin + solved_t.second * ray_velocity;
	collision.normal = Math::normalize(collision.position);


	return {true, collision};
}