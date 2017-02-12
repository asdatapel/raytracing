//
// Created by Asda Tapel on 2/5/17.
//

#ifndef RAYTRACING_BOX_H
#define RAYTRACING_BOX_H

#include "Object.h"
#include "Shapes/Triangle.h"
#include "Shapes/Sphere.h"

class Box : public Object {
public :
	Box(sf::Vector3f position);
	~Box();

	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:
	Triangle *_triangles[12];

	Sphere _bounding_sphere;
};


#endif //RAYTRACING_BOX_H
