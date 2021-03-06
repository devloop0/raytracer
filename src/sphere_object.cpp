#include "sphere_object.h"

#include <cmath>
#include <algorithm>

#include "vec3.h"
#include "trace.h"

namespace raytracer {

SphereObject::SphereObject(const Vec3f& p, float r, ColorProperties cp) :
	position_(p), radius_(r), color_properties_(cp) {

}

SphereObject::~SphereObject() {

}

BoundingBox SphereObject::bounding_box() const {
	return BoundingBox(position_ - radius_, position_ + radius_);
}

Vec3f SphereObject::position() const {
	return position_;
}

std::optional<std::vector<float>> SphereObject::intersect(const Ray& r) const {
	float a = r.d.dot(r.d),
	      b = 2 * ((r.o - position_).dot(r.d)),
	      c = (r.o - position_).dot(r.o - position_) - (radius_ * radius_);

	float d = b * b - 4 * a * c;
	if (d < 0) return std::nullopt;
	float dsq = std::sqrt(d);

	float t1 = (-b + dsq) / (2 * a),
	      t2 = (-b - dsq) / (2 * a);
	float tmin = std::min(t1, t2),
	      tmax = std::max(t1, t2);

	if (tmax < 0) return std::nullopt;
	if (tmin < 0) return std::vector<float>{ tmax };
	else if (tmin == tmax) return std::vector<float>{ tmax };
	else return std::vector<float>{tmin, tmax};
}

ObjectType SphereObject::object_type() const {
	return ObjectType::SPHERE;
}

Vec3f SphereObject::normal(const Vec3f& p) const {
	Vec3f n = p - position_;
	n.normalize();
	return n;
}

const ColorProperties SphereObject::color_properties() const {
	return color_properties_;
}


float SphereObject::surface_area() const {
	return 4 * 3.14159265358979 * std::pow(radius_, 2);
}

} // namespace raytracer
