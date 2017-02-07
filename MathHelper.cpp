//
// Created by Asda Tapel on 1/31/17.
//

#include "MathHelper.h"

std::pair<bool, float> Math::solveQuadratic(const float a, const float b, const float c) {
	float x_low;
	float x_high;

	float discr = b * b - 4 * a * c;
	if (discr < 0) return {false, 0};
	else if (discr == 0) x_low = x_high = -0.5f * b / a;
	else {
		float q = (b > 0) ?
				  -0.5f * (b + sqrt(discr)) :
				  -0.5f * (b - sqrt(discr));
		x_low = q / a;
		x_high = c / q;
	}
	if (x_low < 0 || x_low > x_high) std::swap(x_low, x_high);

	return {true, x_low};
}

float Math::dot(const sf::Vector3f &v1, const sf::Vector3f &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

sf::Vector3f Math::cross(const sf::Vector3f &v1, const sf::Vector3f &v2) {
	return {v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x};
}

sf::Vector3f Math::normalize(const sf::Vector3f &v) {
	float mag = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return v / mag;
}

sf::Vector3f Math::abs(const sf::Vector3f &v) {
	return {std::fabs(v.x), std::fabs(v.y), std::fabs(v.z)};
}