#include "bvh.h"

#include <optional>
#include <memory>
#include <vector>

#include "ray.h"
#include "scene_object.h"
#include "bounding_box.h"

namespace raytracer {

BVH::BVH(const std::vector<std::unique_ptr<SceneObject>>& objects,
	size_t buckets) : buckets_(buckets), root_(nullptr) {
	std::vector<const SceneObject*> all_objects;
	for (const auto& object : objects)
		all_objects.push_back(object.get());

	root_ = construct_BVHNode(all_objects);
}

BVH::~BVH() {

}

std::optional<BVH::HitInfo> BVH::intersect(const Ray& r) const {
	std::optional<HitInfo> hit_info = std::nullopt;
	intersect(r, root_, hit_info);
	return hit_info;
}

void BVH::intersect(const Ray& r, const std::unique_ptr<BVHNode>& n, std::optional<HitInfo>& hit_info) const {
	if (n == nullptr)
		return;
	// TODO
	if (n->is_leaf) {
		for (const auto& object : n->objects) {
			std::optional<std::vector<float>> hits = object->intersect(r);
			if (hits.has_value() && !hits->empty()) {
				float closest = (*hits)[0];
				if (!hit_info.has_value() || closest < hit_info->hits[0]) {
					hit_info->hits = *hits;
					hit_info->object = object;
				}
			}
		}
	}
	else {
		std::optional<std::vector<float>> hits1
			= n->left == nullptr ? std::nullopt : n->left->bounding_box.intersect(r);
		std::optional<std::vector<float>> hits2
			= n->right == nullptr ? std::nullopt : n->right->bounding_box.intersect(r);

		if (hits1.has_value() && hits2.has_value()) {
			if ((*hits1)[0] <= (*hits2)[0]) {
				intersect(r, n->left, hit_info);
				if (!hit_info.has_value() || hit_info->hits[0] > (*hits2)[0])
					intersect(r, n->right, hit_info);
			}
			else {
				intersect(r, n->right, hit_info);
				if (!hit_info.has_value() || hit_info->hits[0] > (*hits1)[0])
					intersect(r, n->left, hit_info);
			}
		}
		else if (hits1.has_value()) { // doesn't hit right
			intersect(r, n->left, hit_info);
		}
		else if (hits2.has_value()) { // doesn't hit left
			intersect(r, n->right, hit_info);
		}
	}
}

std::unique_ptr<BVH::BVHNode> BVH::construct_BVHNode(std::vector<const SceneObject*> objects) {
	// TODO
	return nullptr;
}

} // namespace raytracer
