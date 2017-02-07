//
// Created by Asda Tapel on 2/5/17.
//

#ifndef RAYTRACING_BOX_H
#define RAYTRACING_BOX_H

#include "Object.h"
#include "Shapes/Triangle.h"

class Box : public Object {
public :
	Box(sf::Vector3f position);
	~Box();

	std::pair<bool, RayCollision> intersect(sf::Vector3f ray_origin, sf::Vector3f ray_velocity);
private:
	Triangle *_triangles[12];
};


#endif //RAYTRACING_BOX_H
