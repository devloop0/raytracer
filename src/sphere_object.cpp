#include "sphere_object.h"

#include <cmath>
#include <algorithm>

#include "vec3.h"

namespace raytracer {

SphereObject::SphereObject(const Vec3f& p, float r, const Rgb& c, MaterialType m) :
	position_(p), radius_(r), color_(c), material_type_(m) {

}

SphereObject::~SphereObject() {

}

BoundingBox SphereObject::bounding_box() const {
	return BoundingBox(position_ - radius_, position_ + radius_);
}

Vec3f SphereObject::position() const {
	return position_;
}

MaterialType SphereObject::material_type() const {
	return material_type_;
}

std::optional<float> SphereObject::intersect(const Ray& r) const {
	float a = r.d.dot(r.d),
	      b = 2 * ((r.o - position_).dot(r.d)),
	      c = (r.o - position_).dot(r.o - position_) - (radius_ * radius_);

	float d = b * b - 4 * a * c;
	if (d < 0) return std::nullopt;
	float dsq = std::sqrt(d);

	float t1 = (-b + dsq) / (2 * a),
	      t2 = (-b - dsq) / (2 * a);
	float t = std::min(t1, t2);
	if (t < 0) t = std::max(t1, t2);

	if (t < 0) return std::nullopt;
	return t;
}

Rgb SphereObject::color(const Scene& s, const Ray& r, size_t bounce) const {
	// TODO
	return Rgb(0, 0, 0);
}

ObjectType SphereObject::object_type() const {
	return ObjectType::SPHERE;
}

} // namespace raytracer
