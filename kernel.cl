typedef struct td_Color {
	char r;
	char g;
	char b;
	char a;
} Color;

typedef struct td_RayCollision {
	float t;
	float3 position;
	float3 normal;
	float3 emission;
	float3 diffuse_color;
} RayCollision;

typedef struct td_Sphere {
	float3 position;
	float3 emission;
	float3 diffuse_color;
	float4 radius;
} Sphere;

typedef struct td_Triangle {
	float3 vertices[3];
} Triangle;

//random code taken from ray tracey's blog
static float get_random(unsigned int *seed0, unsigned int *seed1) {

	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

bool solve_quadratic(float a, float b, float c, float *result) {
	float x_low;
	float x_high;

	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x_low = x_high = -0.5f * b / a;
	else {
		float q = (b > 0) ?
				  -0.5f * (b + sqrt(discr)) :
				  -0.5f * (b - sqrt(discr));
		x_low = q / a;
		x_high = c / q;
	}

	if (x_low < 0 || x_low > x_high) {
		float temp = x_low;
		x_low = x_high;
		x_high = temp;
	}

	*result = x_low;
	return true;
}

bool intersect_sphere(float3 ray_origin, float3 ray_velocity, Sphere *sphere, RayCollision *result) {
	float3 l = {ray_origin.x - sphere->position.x, ray_origin.y - sphere->position.y,
				ray_origin.z - sphere->position.z};
	float a = dot(ray_velocity, ray_velocity);
	float b = 2 * dot(ray_velocity, l);
	float c = dot(l, l) - (sphere->radius.x * sphere->radius.x);

	float t;

	if (!solve_quadratic(a, b, c, &t)) {
		return false;
	}
	if (t < 0) {
		return false;
	}

	result->t = t;
	result->position = (float3) {ray_origin.x + t * ray_velocity.x, ray_origin.y + t * ray_velocity.y,
								 ray_origin.z + t * ray_velocity.z};

	float3 relative_collision_position = {result->position.x - sphere->position.x,
										  result->position.y - sphere->position.y,
										  result->position.z - sphere->position.z};
	result->normal = normalize(relative_collision_position);

	result->emission = sphere->emission;
	result->diffuse_color = sphere->diffuse_color;

	/*collision.texture_coords.x =  0.5f + std::atan2(collision.normal.x, collision.normal.z) / (2 * Math::Pi);
	collision.texture_coords.y = 0.5f - std::asin(collision.normal.y) / Math::Pi;*/

	return true;
}

float intersect_triangle(float3 ray_origin, float3 ray_velocity, Triangle *triangle, RayCollision *result) {
	float3 normal = cross(triangle->vertices[2] - triangle->vertices[0], triangle->vertices[1] - triangle->vertices[0]);
	float distance_from_origin = dot(normal, triangle->vertices[0]);

	float parallel = dot(normal, ray_velocity);
	if (fabs(parallel) < 0.000000000001) {
		return false;
	}

	result->normal = normalize(normal);

	result->t = (distance_from_origin - dot(normal, ray_origin)) / parallel;
	if (result->t < 0) {
		return false;
	}

	result->position = ray_origin + ray_velocity * result->t;

	float area = length(normal) * 0.5f;
	for (int i = 0; i < 3; ++i) {
		float3 edge = triangle->vertices[i] - triangle->vertices[(i + 2) % 3];
		float3 vp = result->position - triangle->vertices[(i + 2) % 3];;
		float3 perpendicular = cross(edge, vp);

		/*if (i == 2) { //side 2
			result.bary_coords.x = length(perpendicular) / (2 * area);
		} else if (i == 0) { //side 3
			result.bary_coords.y = length(perpendicular) / (2 * area);
		}*/

		if (dot(normal, perpendicular) > 0) {
			return false;
		}
	}

	//result.texture_coords = (result.bary_coords.x * _uv[0] + result.bary_coords.y * _uv[1] +
	//(1 - result.bary_coords.x - result.bary_coords.y) * _uv[2]);

	return true;
}

#if __CIDR_clang__has_attribute_noreturn
#define Sphere float
#define Triangle float
#endif

float3 intersect(float3 ray_origin, float3 ray_velocity, global const Sphere *spheres, int sphere_count,
				 global const Triangle *triangles, int triangle_count, unsigned int *seed1, unsigned int *seed2) {


	float3 final_color = (float3)(0, 0, 0);
	float3 contribution = (float3)(1.0f, 1.0f, 1.0f);
	for (int bounce = 0; bounce < 8; ++bounce) {

		bool any_collision = false;
		RayCollision closest_collision;
		closest_collision.t = 10000;

		bool bounce_collision = false;

		for (int s = 0; s < sphere_count; ++s) {

			Sphere sphere = spheres[s];

			RayCollision ray_result;
			if (intersect_sphere(ray_origin, ray_velocity, &sphere, &ray_result)) {
				if (ray_result.t < closest_collision.t) {
					any_collision = true;
					closest_collision = ray_result;
					bounce_collision = true;
				}
			}
		}

		/*for (int t = 0; t < triangle_count; ++t) {
			Triangle triangle = triangles[t];

			RayCollision ray_result;
			if (intersect_triangle(ray_origin, ray_velocity, &triangle, &ray_result)) {
				if (ray_result.t < closest_collision.t) {
					any_collision = true;
					closest_collision = ray_result;
					bounce_collision = true;
				}
			}
		}*/

		if (!bounce_collision) {
			//return final_color;
			return (float3)(0.0f, 1.0f, 1.0f);
		}

		float rand1 = 2.0f * 3.1415f * get_random(seed1, seed2);
		float rand2 = get_random(seed1, seed2);
		float rand2s = sqrt(rand2);

		float3 w = closest_collision.normal;
		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
		float3 u = normalize(cross(axis, w));
		float3 v = cross(w, u);

		ray_velocity = normalize(u * cos(rand1) * rand2s + v * sin(rand1) * rand2s + w * sqrt(1.0f - rand2));

		ray_origin = closest_collision.position + ray_velocity * 0.001f;

		final_color += contribution * closest_collision.emission;
		contribution *= closest_collision.diffuse_color;

		contribution *= dot(ray_velocity, closest_collision.normal);
	}

	return final_color;
}

__kernel void
render_image(global const int *image_width, global const int *image_height, global unsigned char *output,
			 global const Sphere *spheres, global const int *sphere_count, global const Triangle *triangles,
			 global const int *triangle_count, global const int *seed) {

	int ID = get_global_id(0);
	int Nthreads = get_global_size(0);
	int n = image_width[0] * image_height[0];

	int ratio = (n / Nthreads);
	int start = ratio * ID;
	int stop = ratio * (ID + 1);

	unsigned int seed1 = seed[0];
	unsigned int seed2 = start % image_width[0] * (start / image_width[0]) * seed1;

	for (int i = start; i < stop; i++) {
		float2 pixel_pos;
		pixel_pos.x = i % image_width[0];
		pixel_pos.y = i / image_width[0];

		float2 pixel_centered_position = {((((float) pixel_pos.x / image_width[0]) - 0.5f) * 2.0f),
										  ((((float) (image_height[0] - pixel_pos.y) / image_height[0]) -
											0.5f) *
										   2.0f)};

		float3 ray_origin = {0, 0, 0.0f};


		float screen_width_radius = 1.0f;
		float screen_height_radius = 9.0f / 16.0f;
		float3 ray_velocity = normalize((float3) {pixel_centered_position.x * screen_width_radius,
												  pixel_centered_position.y * screen_height_radius, -0.5f});



		float3 final_color = (float3) (0.0f, 0.0f, 0.0f);
		int n_samples = 64;
		float weight = (1.0f / ((float)n_samples * 8.0f));
		for (int s = 0; s < n_samples; ++s) {
			final_color += intersect(ray_origin, ray_velocity, spheres, sphere_count[0], triangles, triangle_count[0], &seed1,
									 &seed2) * weight;
		}


		int pixel_data_pos = i * 4;

		float3 old_color;
		old_color.x = output[pixel_data_pos] / 255.0f;
		old_color.y = output[pixel_data_pos + 1] / 255.0f;
		old_color.z = output[pixel_data_pos + 2] / 255.0f;

		final_color = old_color + final_color;
		final_color = min(final_color, (float3)(1.0f, 1.0f, 1.0f));

		output[pixel_data_pos] = final_color.x * 255;
		output[pixel_data_pos + 1] = final_color.y * 255;
		output[pixel_data_pos + 2] = final_color.z * 255;
		output[pixel_data_pos + 3] = 255;


	}
};
