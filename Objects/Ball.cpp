//
// Created by Asda Tapel on 2/3/17.
//

#include "Ball.h"

Ball::Ball(sf::Vector3f position) : Object(position) {
	//_shape = new Triangle({1.0f, 1.0f, 0.0f}, {-1.0f, -1.0f, 0.0f}, {1.0f, -1.0f, 0.0f});
	_shape = new Sphere(1.0f);
	//_velocity.z = -0.01f;
	_rotation = Quaternion({0.0f, 0.0f, 1.0f}, 0);

	_texture.loadFromFile("earth.png");
	_reflectivity_map.loadFromFile("earth_specular.png");
}

Ball::~Ball() {
	delete _shape;
}


std::pair<bool, RayCollision> Ball::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity){
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

	sf::Vector2f tex_coords;
	tex_coords.x = collision.second.texture_coords.x * _texture.getSize().x;
	tex_coords.y = collision.second.texture_coords.y * _texture.getSize().y;

	collision.second.diffuse_color = _texture.getPixel(tex_coords.x, tex_coords.y);
	//collision.second._reflectivity = _reflectivity_map.getPixel(tex_coords.x, tex_coords.y).r / 255.0f;
	collision.second._reflectivity = 1.0f;

	return {true, collision.second};
};