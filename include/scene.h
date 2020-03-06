#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>
#include <memory>

#include "vec3.h"
#include "scene_object.h"
#include "image.h"

namespace raytracer {

class Scene {
public:
	Scene(const std::vector<Vec3f>& ls,
		std::vector<std::unique_ptr<SceneObject>> os,
		const Vec3f& e,
		const Vec3f& v,
		const std::pair<size_t, size_t>& sd,
		const std::pair<float, float>& nf);

	~Scene();

	Vec3f light(size_t i) const;

	std::vector<Vec3f> lights() const;

	Vec3f eye() const;

	Vec3f view() const;

	float near() const;

	float far() const;

	size_t screen_width() const;

	size_t screen_height() const;

	const std::unique_ptr<SceneObject>& object(size_t i) const;

	const std::vector<std::unique_ptr<SceneObject>>& objects() const;

	Image& image();
private:
	std::vector<Vec3f> lights_;
	std::vector<std::unique_ptr<SceneObject>> objects_;
	Vec3f eye_;
	Vec3f view_;
	std::pair<size_t, size_t> screen_dims_;
	Image image_;
	std::pair<float, float> near_far_;
};

} // namespace raytracer

#endif // SCENE_H
