#include "scene.h"

#include <vector>
#include <utility>
#include <cassert>

#include "vec3.h"
#include "image.h"
#include "scene_object.h"

namespace raytracer {

Scene::Scene(const std::vector<Light>& ls,
	std::vector<std::unique_ptr<SceneObject>> os,
	const Vec3f& e,
	const std::pair<size_t, size_t>& sd,
	float f) :
	lights_(ls), objects_(std::move(os)), eye_(e), screen_dims_(sd), fov_(f),
	image_(Image(screen_width(), screen_height())) {

}

Scene::~Scene() {

}

Light Scene::light(size_t i) const {
	assert (0 <= i && i < lights_.size());
	return lights_[i];
}

std::vector<Light> Scene::lights() const {
	return lights_;
}

Vec3f Scene::eye() const {
	return eye_;
}

float Scene::fov() const {
	return fov_;
}

size_t Scene::screen_width() const {
	return screen_dims_.first;
}

size_t Scene::screen_height() const {
	return screen_dims_.second;
}

const std::unique_ptr<SceneObject>& Scene::object(size_t i) const {
	assert(0 <= i && i < objects_.size());
	return objects_[i];
}

const std::vector<std::unique_ptr<SceneObject>>& Scene::objects() const {
	return objects_;
}

Image& Scene::image() {
	return image_;
}

} // namespace raytracer
