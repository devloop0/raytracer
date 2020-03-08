#include "light.h"

#include "vec3.h"

namespace raytracer {

Light::Light(const Vec3f& p, const Rgb& c, float i) : position(p), color(c), intensity(i) {

}

Light::~Light() {

}

std::vector<Light> generate_area_light(const Light& center_light,
	float width, float height, float spacing) {
	std::vector<Light> lights;
	for (float x = center_light.position.x - width;
		x <= center_light.position.x + width;
		x += spacing) {
		for (float y = center_light.position.y - height;
			y <= center_light.position.y + height;
			y += spacing) {
			lights.push_back(
				Light(Vec3f(x, y, center_light.position.z),
					center_light.color, center_light.intensity));
		}
	}
	return lights;
}

} // namespace raytracer

