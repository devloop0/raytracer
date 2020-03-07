#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>
#include <memory>

#include "vec3.h"
#include "scene_object.h"
#include "image.h"
#include "light.h"

namespace raytracer {

class Scene {
public:
	Scene(const std::vector<Light>& ls,
		std::vector<std::unique_ptr<SceneObject>> os,
		const Vec3f& e,
		const std::pair<size_t, size_t>& sd,
		float f);

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
private:
	std::vector<Light> lights_;
	std::vector<std::unique_ptr<SceneObject>> objects_;
	Vec3f eye_;
	Vec3f view_;
	std::pair<size_t, size_t> screen_dims_;
	Image image_;
	float fov_;
};

} // namespace raytracer

#endif // SCENE_H
