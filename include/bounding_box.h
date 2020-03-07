#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <optional>

#include "vec3.h"
#include "ray.h"

namespace raytracer {

struct BoundingBox {
	BoundingBox(const Vec3f& bl, const Vec3f& tr);

	~BoundingBox();

	std::optional<float> intersect(const Ray& r);

	Vec3f bottom_left;
	Vec3f top_right;
};

} // namespace raytracer

#endif // BOUNDING_BOX_H
