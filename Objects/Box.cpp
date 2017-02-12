//
// Created by Asda Tapel on 2/5/17.
//

#include "Box.h"

Box::Box(sf::Vector3f position) : Object(position), _bounding_sphere(std::sqrt(2)) {
	sf::Vector3f verts[] = {
			{0.5f,  -0.5f, -0.5f},
			{0.5f,  0.5f,  -0.5f},
			{-0.5f, -0.5f, -0.5f},

			{-0.5f, -0.5f, -0.5f},
			{0.5f,  0.5f,  -0.5f},
			{-0.5f, 0.5f,  -0.5f},

			{0.5f,  -0.5f, 0.5f},
			{-0.5f, -0.5f, 0.5f},
			{-0.5f, 0.5f,  0.5f},

			{0.5f,  -0.5f, 0.5f},
			{-0.5f, 0.5f,  0.5f},
			{0.5f,  0.5f,  0.5f},

			{0.5f,  0.5f,  0.5f},
			{0.5f,  0.5f,  -0.5f},
			{0.5f,  -0.5f, -0.5f},

			{0.5f,  0.5f,  0.5f},
			{0.5f,  -0.5f, -0.5f},
			{0.5f,  -0.5f, 0.5f},

			{-0.5f, -0.5f, -0.5f},
			{-0.5f, 0.5f,  -0.5f},
			{-0.5f, 0.5f,  0.5f},

			{-0.5f, -0.5f, -0.5f},
			{-0.5f, 0.5f,  0.5f},
			{-0.5f, -0.5f, 0.5f},

			{-0.5f, -0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f},
			{0.5f,  -0.5f, 0.5f},

			{-0.5f, -0.5f, -0.5f},
			{0.5f,  -0.5f, 0.5f},
			{0.5f,  -0.5f, -0.5f},

			{-0.5f, 0.5f,  0.5f},
			{-0.5f, 0.5f,  -0.5f},
			{0.5f,  0.5f,  -0.5f},

			{-0.5f, 0.5f,  0.5f},
			{0.5f,  0.5f,  -0.5f},
			{0.5f,  0.5f,  0.5f}
	};
	sf::Vector2f uvs[] = {
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 0.0f},

			{0.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f},

			{1.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},

			{1.0f,  1.0f},
			{1.0f,  0.0f},
			{0.0f, 0.0f},

			{1.0f,  1.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f},

			{0.0f, 0.0f},
			{1.0f,  0.0f},
			{1.0f,  1.0f},

			{0.0f, 0.0f},
			{1.0f,  1.0f},
			{0.0f, 1.0f},

			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f,  1.0f},

			{0.0f, 0.0f},
			{1.0f,  1.0f},
			{1.0f,  0.0f},

			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f,  0.0f},

			{0.0f, 1.0f},
			{1.0f,  0.0f},
			{1.0f,  1.0f}
	};
	for (int i = 0; i < 12; ++i) {
		int vert_i = i * 3;
		_triangles[i] = new Triangle(verts[vert_i], verts[vert_i + 1], verts[vert_i + 2], uvs[vert_i], uvs[vert_i + 1],
									 uvs[vert_i + 2]);
	}
	_velocity = {-0.05f, 0.0f, 0.0f};

	_texture.loadFromFile("crafting_table_top.png");
}

Box::~Box() {
	for (int i = 0; i < 12; ++i) {
		delete _triangles[i];
	}
}

std::pair<bool, RayCollision> Box::intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity) {
	ray_origin -= _position;
	ray_origin = _rotation.conjugate() * ray_origin;
	ray_velocity = _rotation.conjugate() * ray_velocity;

	auto bounding_collision = _bounding_sphere.intersect(ray_origin, ray_velocity);
	if (!bounding_collision.first){
		return {false, {}};
	}

	bool any_collision = false;
	float min_t = 10000;
	RayCollision closest_collision = {};

	for (auto &object : _triangles) {
		auto collision = object->intersect(ray_origin, ray_velocity);
		if (collision.first) {
			any_collision = true;
			if (collision.second.t < min_t) {
				min_t = collision.second.t;
				closest_collision = collision.second;
			}
		}
	}

	closest_collision.position = _rotation * closest_collision.position;
	closest_collision.position += _position;
	closest_collision.normal = _rotation * closest_collision.normal;

	sf::Vector2f tex_coords;
	tex_coords.x = closest_collision.texture_coords.x * _texture.getSize().x;
	tex_coords.y = closest_collision.texture_coords.y * _texture.getSize().y;

	//closest_collision.diffuse_color = _texture.getPixel(tex_coords.x, tex_coords.y);
	closest_collision.diffuse_color = sf::Color::Red;
	closest_collision._reflectivity = 1.0f;


	return {any_collision, closest_collision};
}