//
// Created by Asda Tapel on 1/31/17.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <SFML/System.hpp>

#include "MathHelper.h"
#include "Shape.h"
#include "Ray.h"

//TODO: stick to paradigm where shape has no position, oobject will translate away from and to origin for intersect

class Sphere : public Shape {
public:
	Sphere(float radius);

	//check if a ray collides and return the distance from the ray origin
	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);

private:
	float _radius;
};


#endif //RAYTRACING_SPHERE_H
