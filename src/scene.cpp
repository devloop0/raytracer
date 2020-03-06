#include "scene.h"

#include <vector>
#include <utility>
#include <cassert>

#include "vec3.h"
#include "image.h"
#include "scene_object.h"

namespace raytracer {

Scene::Scene(const std::vector<Vec3f>& ls,
	std::vector<std::unique_ptr<SceneObject>> os,
	const Vec3f& e,
	const Vec3f& v,
	const std::pair<size_t, size_t>& sd,
	const std::pair<float, float>& nf) :
	lights_(ls), objects_(std::move(os)), eye_(e), view_(v), screen_dims_(sd), near_far_(nf),
	image_(Image(screen_width(), screen_height())) {

}

Scene::~Scene() {

}

Vec3f Scene::light(size_t i) const {
	assert (0 <= i && i < lights_.size());
	return lights_[i];
}

std::vector<Vec3f> Scene::lights() const {
	return lights_;
}

Vec3f Scene::eye() const {
	return eye_;
}

Vec3f Scene::view() const {
	return view_;
}

float Scene::near() const {
	return near_far_.first;
}

float Scene::far() const {
	return near_far_.second;
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
