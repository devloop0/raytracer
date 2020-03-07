#ifndef RAY_H
#define RAY_H

#include "vec3.h"

namespace raytracer {

struct Ray {
	Ray(const Vec3f& o, const Vec3f& d);

	~Ray();

	Vec3f o, d;
};

} // namespace raytracer

#endif // RAY_H
