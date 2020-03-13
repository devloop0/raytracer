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
	float f,
	const Rgb& bg,
	size_t m,
	float b) :
	lights_(ls), objects_(std::move(os)), eye_(e), screen_dims_(sd), fov_(f),
	image_(Image(screen_width(), screen_height())), max_bounce_(m), bias_(b),
	background_color_(bg), bvh_(BVH()) {
	bvh_.construct(objects());
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

size_t Scene::max_bounce() const {
	return max_bounce_;
}

float Scene::bias() const {
	return bias_;
}

Rgb Scene::background_color() const {
	return background_color_;
}

std::optional<BVH::HitInfo> Scene::intersect(const Ray& r) const {
	return bvh_.intersect(r);
}

} // namespace raytracer
