#include "bvh.h"

#include <optional>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

#include "ray.h"
#include "scene_object.h"
#include "bounding_box.h"

namespace raytracer {

BVH::BVH(const std::vector<std::unique_ptr<SceneObject>>& objects,
	size_t buckets) : buckets_(buckets), root_(nullptr) {
	std::vector<const SceneObject*> all_objects;
	for (const auto& object : objects)
		all_objects.push_back(object.get());

	root_ = construct_BVHNode(all_objects, 0, objects.size());
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

std::unique_ptr<BVH::BVHNode> BVH::construct_BVHNode(std::vector<const SceneObject*> objects,
	size_t start_pos, size_t end_pos) {
	if (start_pos == end_pos) return nullptr;
	BoundingBox full_bounds = objects[start_pos]->bounding_box();
	for (size_t i = start_pos; i < end_pos; i++)
		full_bounds = full_bounds.union_with(objects[i]->bounding_box());

	std::vector<std::pair<float, float>> axes_bounds = {
		{ full_bounds.bottom_left.x, full_bounds.top_right.x },
		{ full_bounds.bottom_left.y, full_bounds.top_right.y },
		{ full_bounds.bottom_left.z, full_bounds.top_right.z }
	};

	struct BucketInfo {
		size_t count = 0;
		BoundingBox bounds = BoundingBox();
	};

	float bucket_split_min_cost = INFINITY;
	size_t min_cost_split_bucket = 0;

	size_t dim_counter = 0;
	for (const auto& [axis_start, axis_end] : axes_bounds) {
		std::vector<BucketInfo> buckets(buckets_);
		std::vector<float> costs(buckets_ - 1);

		for (size_t i = start_pos; i < end_pos; i++) {
			const auto& object = objects[i];
			float dim = dim_counter == 0 ? object->position().x
				: dim_counter == 1 ? object->position().y
				: object->position().z;
			size_t bucket_index
				= std::clamp(static_cast<size_t>(dim / buckets_),
					static_cast<size_t>(0), buckets_ - 1);
			if (buckets[bucket_index].count == 0)
				buckets[bucket_index].bounds = object->bounding_box();
			else
				buckets[bucket_index].bounds = buckets[bucket_index].bounds.union_with(object->bounding_box());
			buckets[bucket_index].count++;
		}

		for (size_t i = 0; i < buckets_ - 1; i++) {
			BoundingBox b0 = buckets[0].bounds;
			size_t count0 = 0;
			for (size_t j = 0; j <= i; j++) {
				b0 = b0.union_with(buckets[j].bounds);
				count0 += buckets[j].count;
			}

			BoundingBox b1 = buckets[i + 1].bounds;
			size_t count1 = 0;
			for (size_t j = i + 1; j < buckets_; j++) {
				b1 = b1.union_with(buckets[j].bounds);
				count1 += buckets[j].count;
			}

			costs[i] = 0.125f + (count0 * b0.surface_area() + count1 * b1.surface_area()) / full_bounds.surface_area();
		}

		for (size_t i = 0; i < costs.size(); i++) {
			float cost = costs[i];
			if (bucket_split_min_cost > costs[i]) {
				bucket_split_min_cost = costs[i];
				min_cost_split_bucket = i;
			}
		}

		dim_counter++;
	}

	float leaf_cost = end_pos - start_pos;
	if (end_pos - start_pos > MAX_NODES_PER_LEAF || bucket_split_min_cost < leaf_cost) {
		// TODO
	}
	else {
		std::unique_ptr<BVHNode> bvh = std::make_unique<BVHNode>();
		bvh->bounding_box = full_bounds;
		for (size_t i = start_pos; i < end_pos; i++)
			bvh->objects.push_back(objects[i]);
		return bvh;
	}
	return nullptr;
}

} // namespace raytracer
