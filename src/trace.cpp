#include "trace.h"

#include <cmath>
#include <algorithm>

namespace raytracer {

void render(Scene& s) {
	float width_step = 1.0f / static_cast<float>(s.screen_width()),
		height_step = 1.0f / static_cast<float>(s.screen_height()),
		aspect_ratio = static_cast<float>(s.screen_width()) / static_cast<float>(s.screen_height()),
		angle = tan(3.1415926535 * s.fov() / 360);
	for (float h = 0; h < s.screen_height(); h++) {
		for (float w = 0; w < s.screen_width(); w++) {
			float ww = (2 * ((w + 0.5) * width_step) - 1) * aspect_ratio * angle; // apply ratio to normalize
			float hh = (1 - 2 * ((h + 0.5) * height_step)) * angle; // negation distributed for pinhole camera
			Vec3f dir(ww, hh, -1);
			dir.normalize();
			const Rgb& color = trace(Ray(s.eye(), dir), s); // shoot ray for each pixel of frame buffer 
			s.image()(h, w) = color;
		}
	}
}

Rgb trace(const Ray& r, Scene& s, size_t bounce) {
	// TODO: BVH
	float closest_distance = INFINITY;
	SceneObject* closest_object = nullptr;
	for (size_t i = 0; i < s.objects().size(); i++) {
		const std::unique_ptr<SceneObject>& so = s.object(i);
		std::optional<std::vector<float>> o = so->intersect(r);
		if (o) {
			const std::vector<float> v = *o;
			if (closest_distance > v[0]) {
				closest_distance = v[0];
				closest_object = so.get();
			}
		}
	}

	// No intersection
	if (closest_object == nullptr) return Rgb(1, 1, 1);
	Vec3f hit_position = r.o + closest_distance * r.d;
	Vec3f surface_normal = closest_object->normal(hit_position);
	if (r.o.dot(surface_normal) > 0) surface_normal = 0.0f - surface_normal;

	Rgb color = Vec3f(0, 0, 0);
	if (closest_object->material_type() == MaterialType::DIFFUSE) {
		for (const auto& l : s.lights()) {
			// avoid back ray hitting the object itself by nudging. 
			Vec3f nudged = hit_position + surface_normal * 0.0001; 
			Vec3f light_direction = l.position - nudged;
			light_direction.normalize();
			// now check if intersections in light direction
			Ray back(
				nudged,
				light_direction
			);
			float shadow = 0;

			// TODO: BVH
			for (const std::unique_ptr<SceneObject>& so : s.objects()) {
				if (so->intersect(back)) {
					// occluded, so in shadow
					shadow = 1;
					break;
				}
			}
			color += l.color * (1 - shadow) * closest_object->diffuse_color() * std::max(0.0f, surface_normal.dot(light_direction));
		}
	}
	else {
		// TODO: Handle reflection and refraction
	}
	return color;
}

}
