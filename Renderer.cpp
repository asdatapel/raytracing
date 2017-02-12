//
// Created by Asda Tapel on 1/31/17.
//

#include "Renderer.h"

Renderer::Renderer(){
	t_loaded = false;
}

void Renderer::drawWorld(sf::Image *image, World *world) {
	float screen_width_radius = 1.0f;
	float screen_height_radius = 9.0f / 16.0f;

	for (int i = 0; i < image->getSize().x; ++i) {
		for (int j = 0; j < image->getSize().y; ++j) {

			sf::Vector2f pixel_centered_position = {((((float) i / image->getSize().x) - 0.5f) * 2.0f),
													((((float) (image->getSize().y - j) / image->getSize().y) - 0.5f) *
													 2.0f)};
			sf::Vector3f ray_velocity = {pixel_centered_position.x * screen_width_radius,
										 pixel_centered_position.y * screen_height_radius, -camera_distance};

			auto first_ray_result = world->intersect(camera_pos, ray_velocity);
			if (first_ray_result.first) {
				sf::Vector3f ray_origin = first_ray_result.second.position + 0.0001f * first_ray_result.second.normal;
				ray_velocity = first_ray_result.second.normal;


				auto second_ray_result = world->intersect(ray_origin, ray_velocity);

				if (second_ray_result.first) {
					image->setPixel(i, j, first_ray_result.second._reflectivity * second_ray_result.second.diffuse_color + (1 - first_ray_result.second._reflectivity) * first_ray_result.second.diffuse_color);
				} else {
					image->setPixel(i, j, first_ray_result.second.diffuse_color);
				}
			}
		}
	}
}