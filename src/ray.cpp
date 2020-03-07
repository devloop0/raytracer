#include "ray.h"

namespace raytracer {

Ray::Ray(const Vec3f& o, const Vec3f& d) : o(o), d(d) {
	this->d.normalize();
}

Ray::~Ray() {

}

} // namespace raytracer
