#include "bounding_box.h"

#include <optional>
#include <algorithm>

#include "vec3.h"
#include "ray.h"

namespace raytracer {

BoundingBox::BoundingBox() : bottom_left(Vec3f(0, 0, 0)), top_right(Vec3f(0, 0, 0)) {

}

BoundingBox::BoundingBox(const Vec3f& bl, const Vec3f& tr) :
	bottom_left(bl), top_right(tr) {

}

BoundingBox::~BoundingBox() {

}

std::optional<std::vector<float>> BoundingBox::intersect(const Ray& r) const {
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
	return std::vector<float> {tmin, tmax};
}

BoundingBox BoundingBox::union_with(const BoundingBox& b) const {
	Vec3f new_bl, new_tr;
	new_bl.x = std::min(b.bottom_left.x, bottom_left.x);
	new_bl.y = std::min(b.bottom_left.y, bottom_left.y);
	new_bl.z = std::min(b.bottom_left.z, bottom_left.z);

	new_tr.x = std::max(b.top_right.x, top_right.x);
	new_tr.y = std::max(b.top_right.y, top_right.y);
	new_tr.z = std::max(b.top_right.z, top_right.z);
	return BoundingBox(new_bl, new_tr);
}

BoundingBox BoundingBox::union_with(const Vec3f& p) const {
	Vec3f new_bl, new_tr;
	new_bl.x = std::min(bottom_left.x, p.x);
	new_bl.y = std::min(bottom_left.y, p.y);
	new_bl.z = std::min(bottom_left.z, p.z);

	new_tr.x = std::max(top_right.x, p.x);
	new_tr.y = std::max(top_right.y, p.y);
	new_tr.z = std::max(top_right.z, p.z);
	return BoundingBox(new_bl, new_tr);
}


float BoundingBox::surface_area() const {
	// 2(xy+yz+zx)
	float length = top_right.x - bottom_left.x;
	float width = top_right.y - bottom_left.y;
	float height = top_right.z - bottom_left.z;

	return 2 * (length * width + width * height + height * length);
} 

} // namespace raytracer
