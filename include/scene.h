#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>
#include <memory>

#include "bvh.h"
#include "vec3.h"
#include "scene_object.h"
#include "image.h"
#include "light.h"
#include "ray.h"

namespace raytracer {

class Scene {
public:
	Scene(const std::vector<Light>& ls,
		std::vector<std::unique_ptr<SceneObject>> os,
		const Vec3f& e,
		const std::pair<size_t, size_t>& sd,
		float f,
		const Rgb& bg = Rgb(1, 1, 1),
		size_t m = 5,
		float b = 0.001);

	~Scene();

	Light light(size_t i) const;

	std::vector<Light> lights() const;

	Vec3f eye() const;

	float fov() const;

	size_t screen_width() const;

	size_t screen_height() const;

	const std::unique_ptr<SceneObject>& object(size_t i) const;

	const std::vector<std::unique_ptr<SceneObject>>& objects() const;

	Image& image();

	size_t max_bounce() const;

	float bias() const;

	Rgb background_color() const;

	std::optional<BVH::HitInfo> intersect(const Ray& r) const;
private:
	std::vector<Light> lights_;
	std::vector<std::unique_ptr<SceneObject>> objects_;
	Vec3f eye_;
	Vec3f view_;
	std::pair<size_t, size_t> screen_dims_;
	Image image_;
	float fov_;
	size_t max_bounce_;
	float bias_;
	Rgb background_color_;
	BVH bvh_;
};

} // namespace raytracer

#endif // SCENE_H
