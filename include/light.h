#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

namespace raytracer {

struct Light {
	Light(const Vec3f& p, const Rgb& c, float i);

	~Light();

	Vec3f position;
	Rgb color;
	float intensity;
};

} // namespace raytracer

#endif // LIGHT_H