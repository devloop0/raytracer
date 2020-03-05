#include "scene.h"

#include <vector>
#include <utility>
#include <cassert>

#include "vec3.h"

namespace raytracer {

Scene::Scene(const std::vector<Vec3f>& ls,
	const Vec3f& e,
	const Vec3f& v,
	const std::pair<size_t, size_t>& sd,
	const std::pair<float, float>& nf) :
	lights_(ls), eye_(e), view_(v), screen_dims_(sd), near_far_(nf) {

}

Scene::~Scene() {

}

Vec3f Scene::light(size_t i) const {
	assert (0 <= i && i <= lights_.size());
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

} // namespace raytracer
