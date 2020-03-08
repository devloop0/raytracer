#include "light.h"

#include "vec3.h"

namespace raytracer {

Light::Light(const Vec3f& p, const Rgb& c, float i) : position(p), color(c), intensity(i) {

}

Light::~Light() {

}

} // namespace raytracer

