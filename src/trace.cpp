#include "trace.h"

#include <optional>
#include <cmath>
#include <algorithm>
#include <omp.h>

#include "vec3.h"

namespace raytracer {

void render(Scene& s) {
	float width_step = 1.0f / static_cast<float>(s.screen_width()),
		height_step = 1.0f / static_cast<float>(s.screen_height()),
		aspect_ratio = static_cast<float>(s.screen_width()) / static_cast<float>(s.screen_height()),
		angle = tan(3.1415926535 * s.fov() / 360);
	constexpr size_t BLOCK_SIZE = 8;

	#pragma omp parallel for collapse(2) schedule(static, 1)
	for (size_t h_outer = 0; h_outer < s.screen_height(); h_outer += BLOCK_SIZE) {
		for (size_t w_outer = 0; w_outer < s.screen_width(); w_outer += BLOCK_SIZE) {
			for (float h = h_outer;
				h < std::min(static_cast<float>(h_outer + BLOCK_SIZE), static_cast<float>(s.screen_height()));
				h++) {
				for (float w = w_outer;
					w < std::min(static_cast<float>(w_outer + BLOCK_SIZE), static_cast<float>(s.screen_width())); 
					w++) {
					// apply ratio to normalize
					float ww = (2 * ((w + 0.5) * width_step) - 1) * aspect_ratio * angle;

 					// negation distributed for pinhole camera
					float hh = (1 - 2 * ((h + 0.5) * height_step)) * angle;

					Vec3f dir(ww, hh, -1);
					dir.normalize();

					// shoot ray for each pixel of frame buffer 
					const Rgb& color = trace(Ray(s.eye(), dir), s); 
					s.image()(h, w) = color;
				}
			}
		}
	}
}

Rgb trace(const Ray& r, Scene& s, size_t bounce) {
	if (bounce >= s.max_bounce())
		return Rgb(0, 0, 0);

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
	if (closest_object == nullptr) {
		if (bounce == 0)
			return s.background_color();
		else
			return Rgb(0, 0, 0);
	}

	bool inside = false;
	Vec3f hit_position = r.o + closest_distance * r.d;
	Vec3f surface_normal = closest_object->normal(hit_position);
	if (r.d.dot(surface_normal) > 0) {
		surface_normal = -surface_normal;
		inside = true;
	}
	if (closest_object->object_type() == ObjectType::TRIANGLE) inside = false;

	Rgb color = Vec3f(0, 0, 0);
	Vec3f nudged = hit_position + surface_normal * s.bias(); 
	const ColorProperties& color_properties = closest_object->color_properties();
	for (const auto& l : s.lights()) {
		// avoid back ray hitting the object itself by nudging. 
		Vec3f light_direction = l.position - nudged;
		float light_distance = light_direction.norm();
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

		light_distance = light_distance * light_distance;
		float lambertian = std::max(0.0f, surface_normal.dot(light_direction));
		float specular = 0;

		if (lambertian > 0) {
			Vec3f view_direction = hit_position - s.eye(),
			      half_direction = light_direction + view_direction;
			half_direction.normalize();
			float specular_angle = std::max(half_direction.dot(surface_normal), 0.0f);
			specular = std::pow(specular_angle, color_properties.shininess);
		}

		Vec3f color_linear = color_properties.diffuse_color * lambertian * l.color * l.intensity / light_distance
			+ color_properties.specular_color * specular * l.color * l.intensity / light_distance;
		color_linear.x = std::pow(color_linear.x, 1.0f / 2.2f);
		color_linear.y = std::pow(color_linear.y, 1.0f / 2.2f);
		color_linear.z = std::pow(color_linear.z, 1.0f / 2.2f);
		color += color_linear * (1 - shadow);
	}
	color /= static_cast<float>(s.lights().size());

	if ((color_properties.reflectivity > 0 || color_properties.transparency > 0) && bounce < s.max_bounce()) {
		Vec3f rfl = reflect(r.d, surface_normal);
		rfl += Vec3f::random() * color_properties.glossiness;
		rfl.normalize();
		Ray reflected(nudged, rfl);
		Rgb reflection_color = trace(reflected, s, bounce + 1);

		if (color_properties.transparency > 0) {
			float ni = 1.0, nt = 1.1, nit = ni / nt;
			if (inside) nit = 1 / nit;
			
			float cosi = -surface_normal.dot(r.d),
				k = 1 - nit * nit * (1 - cosi * cosi);
			Vec3f rfr = r.d * nit + surface_normal * (nit * cosi - std::sqrt(k));
			rfr += Vec3f::random() * color_properties.transparent_glossiness;
			rfr.normalize();

			Ray refracted(hit_position - surface_normal * s.bias(), rfr);
			Rgb refraction_color = trace(refracted, s, bounce + 1);
			color = (reflection_color * color_properties.reflectivity)
				+ (refraction_color * color_properties.transparency);
		}
		else {
			color += reflection_color * color_properties.reflectivity;
		}
	}

	return color;
}

}
