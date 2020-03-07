#include "bounding_box.h"

#include <optional>
#include <algorithm>

#include "vec3.h"
#include "ray.h"

namespace raytracer {

BoundingBox::BoundingBox(const Vec3f& bl, const Vec3f& tr) :
	bottom_left(bl), top_right(tr) {

}

BoundingBox::~BoundingBox() {

}

std::optional<float> BoundingBox::intersect(const Ray& r) {
	Vec3f inv_dir = 1.0f / r.d;

	Vec3f tbl = (bottom_left - r.o) * inv_dir,
	      ttr = (top_right - r.o) * inv_dir;

	float tmax = std::min(
		std::min(
			std::max(tbl.x, ttr.x),
			std::max(tbl.y, ttr.y)),
		std::max(tbl.z, ttr.z)),
	      tmin = std::max(
		std::max(
			std::min(tbl.x, ttr.x),
			std::min(tbl.y, ttr.y)),
		std::min(tbl.z, ttr.z));

	if (tmax < 0 || tmin > tmax) return std::nullopt;
	return tmin;
}

} // namespace raytracer
