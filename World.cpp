//
// Created by Asda Tapel on 1/31/17.
//

#include "World.h"

World::~World(){
	for (auto& object : _objects){
		delete object;
	}
}

void World::init() {
	_objects.push_back(new Box(sf::Vector3f(2.0f, 0.0f, -4.5f)));
}

std::pair<bool, RayCollision> World::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {
	bool any_collision = false;
	float min_t = 10000;
	RayCollision closest_collision = {};

	for (auto &object : _objects){
		auto collision = object->intersect(ray_origin, ray_velocity);
		if (collision.first){
			any_collision = true;
			if (collision.second.t < min_t){
				min_t = collision.second.t;
				closest_collision = collision.second;
			}
		}
	}

	return {any_collision, closest_collision};
}

void World::update() {
	for (auto &object : _objects){
		if (object->_position.y > 1.0f){
			object->_velocity = {0, -0.01f, 0};
		}
		if (object->_position.y < -1.0f){
			object->_velocity = {0, 0.01f, 0};
		}
		//object->_position += object->_velocity;
		static float angle = 0.0f;
		object->_rotation = Quaternion({1.0f, 0.0f, 0.0f}, angle);
		angle += 0.05;
	}
}