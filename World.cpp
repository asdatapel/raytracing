//
// Created by Asda Tapel on 1/31/17.
//

#include "World.h"

World::~World() {
	for (auto &object : _objects) {
		delete object;
	}
}

void World::init() {
	_objects.push_back(new Wall({0.0f, 0.0f, -3.0f}, {6.0f, 6.0f}, "map1.png"));
	_objects.push_back(new Wall({0.0f, 0.0f, 3.0f}, {6.0f, 6.0f}, "map2.png"));
	_objects.push_back(new Wall({3.0f, 0.0f, 0.0f}, {6.0f, 6.0f}, "map3.png"));
	_objects[2]->_rotation = Quaternion({0.0f, 1.0f, 0.0f}, Math::toRadians(90.0f));
	_objects.push_back(new Wall({-3.0f, 0.0f, -0.0f}, {6.0f, 6.0f}, "map4.png"));
	_objects[3]->_rotation = Quaternion({0.0f, 1.0f, 0.0f}, Math::toRadians(-90.0f));
	_objects.push_back(new Box(sf::Vector3f(0.0f, -0.5f, -1.5f)));
	//_objects.push_back(new Box(sf::Vector3f(2.0f, -1.0f, -2.5f)));
}

std::pair<bool, RayCollision> World::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {
	bool any_collision = false;
	float min_t = 10000;
	RayCollision closest_collision = {};

	for (auto &object : _objects) {
		auto collision = object->intersect(ray_origin, ray_velocity);
		if (collision.first) {
			any_collision = true;
			if (collision.second.t < min_t) {
				min_t = collision.second.t;
				closest_collision = collision.second;
			}
		}
	}

	return {any_collision, closest_collision};
}

void World::update() {
	Object *object = _objects[4];
	if (object->_position.x > 9.0f) {
		object->_position.x = 9.0f;
		object->_velocity = {0.0f, 0.1f, 0};
	}
	if (object->_position.y > 6.0f) {
		object->_position.y = 6.0f;
		object->_velocity = {-0.1f, 0.0f, 0};
	}
	if (object->_position.x < -9.0f) {
		object->_position.x = -9.0f;
		object->_velocity = {0.0f, -0.1f, 0};
	}
	if (object->_position.y < -6.0f) {
		object->_position.y = -6.0f;
		object->_velocity = {0.1f, 0.0f, 0};
	}
	//object->_position.z += -0.02f;
	static float angle = 0.0f;
	object->_rotation = Quaternion({1.0f, 0.0f, 0.0f}, angle);
	angle += 0.05;

}