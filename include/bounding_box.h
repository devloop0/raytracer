#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>
#include <optional>

#include "vec3.h"
#include "ray.h"

namespace raytracer {

struct BoundingBox {
	BoundingBox();

	BoundingBox(const Vec3f& bl, const Vec3f& tr);

	~BoundingBox();

	std::optional<std::vector<float>> intersect(const Ray& r) const;

	BoundingBox union_with(const BoundingBox& b) const;

	BoundingBox union_with(const Vec3f& p) const;

	size_t longest_axis() const; 

	Vec3f relative_position(const Vec3f& p) const;

	float surface_area() const;

	Vec3f bottom_left;
	Vec3f top_right;
};

} // namespace raytracer

#endif // BOUNDING_BOX_H
