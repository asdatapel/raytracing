//
// Created by Asda Tapel on 2/3/17.
//

#include "Wall.h"

Wall::Wall(sf::Vector3f position) : Object(position) {
	_shape = new Triangle({1.0f, 1.0f, 0.0f}, {-1.0f, -1.0f, 0.0f}, {1.0f, -1.0f, 0.0f});
	//_shape = new Sphere(1.0f);
	//_velocity.y = 0.01f;
	//_velocity.x = 0.01f;
	_velocity.z = 0.01f;
	_rotation = Quaternion({0.0f, 0.0f, 1.0f}, 0);
}

Wall::~Wall() {
	delete _shape;
}


std::pair<bool, RayCollision> Wall::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity){
	ray_origin -= _position;
	ray_origin = _rotation.conjugate() * ray_origin;
	ray_velocity = _rotation.conjugate() * ray_velocity;


	auto collision = _shape->intersect(ray_origin, ray_velocity);

	if (!collision.first){
		return {false, {}};
	}

	collision.second.position = _rotation * collision.second.position;
	collision.second.position += _position;
	collision.second.normal = _rotation * collision.second.normal;
	return {true, collision.second};
};