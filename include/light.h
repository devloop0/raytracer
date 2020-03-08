#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "vec3.h"

namespace raytracer {

struct Light {
	Light(const Vec3f& p, const Rgb& c, float i);

	~Light();

	Vec3f position;
	Rgb color;
	float intensity;
};

std::vector<Light> generate_area_light(const Light& center_light,
	float width, float height, float spacing = 0.5);

} // namespace raytracer

#endif // LIGHT_H
