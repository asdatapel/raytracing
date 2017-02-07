//
// Created by Asda Tapel on 1/31/17.
//

#include "Renderer.h"

void Renderer::drawWorld(sf::Image *image, World *world) {

	float screen_width_radius = 1.0f;
	float screen_height_radius = 9.0f / 16.0f;

	for (int i = 0; i < image->getSize().x; ++i){
		for (int j = 0; j < image->getSize().y; ++j){

			sf::Vector2f pixel_centered_position = {((((float)i / image->getSize().x) - 0.5f) * 2.0f), ((((float)(image->getSize().y - j) / image->getSize().y) - 0.5f) * 2.0f)};
			sf::Vector3f ray_velocity = {pixel_centered_position.x * screen_width_radius, pixel_centered_position.y * screen_height_radius, -camera_distance};

			auto ray_result = world->intersect(camera_pos, ray_velocity);
			ray_result.second.normal = Math::abs(ray_result.second.normal);
			if (ray_result.first){
				sf::Color color =  sf::Color(sf::Uint8(ray_result.second.normal.x * 255), sf::Uint8(ray_result.second.normal.y * 255), sf::Uint8(ray_result.second.normal.z * 255));
				image->setPixel( i, j, color);
			}
		}
	}
}