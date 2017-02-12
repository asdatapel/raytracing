//
// Created by Asda Tapel on 2/10/17.
//

#include "Wall.h"

Wall::Wall(sf::Vector3f position, sf::Vector2f size, std::string texture_name) : Object(position) {
	float half_radius_x = size.x / 2;
	float half_radius_y = size.y / 2;
	_t1 = new Triangle({-half_radius_x, half_radius_y, 0.0f}, {half_radius_x, half_radius_y, 0.0f},
					   {-half_radius_x, -half_radius_y, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f});
	_t2 = new Triangle({-half_radius_x, -half_radius_y, 0.0f}, {half_radius_x, half_radius_y, 0.0f},
					   {half_radius_x, -half_radius_y, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.0f});
	
	_texture.loadFromFile(texture_name);
}

Wall::~Wall() {
	delete _t1;
	delete _t2;
}

std::pair<bool, RayCollision> Wall::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {
	ray_origin -= _position;
	ray_origin = _rotation.conjugate() * ray_origin;
	ray_velocity = _rotation.conjugate() * ray_velocity;

	auto t1_collision = _t1->intersect(ray_origin, ray_velocity);
	auto final_collision = &t1_collision.second;
	if (!t1_collision.first) {
		auto t2_collision = _t2->intersect(ray_origin, ray_velocity);
		if (!t2_collision.first){
			return {false, {}};
		}
		
		final_collision = &t2_collision.second;
	}

	final_collision->position = _rotation * final_collision->position;
	final_collision->position += _position;

	final_collision->normal = _rotation * final_collision->normal;

	sf::Vector2f tex_coords;
	tex_coords.x = final_collision->texture_coords.x * _texture.getSize().x;
	tex_coords.y = final_collision->texture_coords.y * _texture.getSize().y;

	final_collision->diffuse_color = _texture.getPixel(tex_coords.x, tex_coords.y);
	final_collision->_reflectivity = 0;

	return {true, *final_collision};
}