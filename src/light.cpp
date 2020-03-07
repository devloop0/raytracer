#include "light.h"

#include "vec3.h"

namespace raytracer {

Light::Light(const Vec3f& p, const Rgb& c) : position(p), color(c) {

}

Light::~Light() {

}

} // namespace raytracer

