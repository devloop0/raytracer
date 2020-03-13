#include "bvh.h"

#include <iostream>
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
	size_t buckets, bool d) : buckets_(buckets), root_(nullptr), debug_(d) {
	construct(objects);
}

BVH::BVH(size_t buckets, bool d) : buckets_(buckets), root_(nullptr), debug_(d) {

}

void BVH::construct(const std::vector<std::unique_ptr<SceneObject>>& objects) {
	std::vector<const SceneObject*> all_objects;
	for (const auto& object : objects)
		all_objects.push_back(object.get());

	root_ = construct_BVHNode(all_objects, 0, objects.size());
	if (debug_)
		visualize(root_);
}

void BVH::visualize(const std::unique_ptr<BVHNode>& n, size_t indentation) const {
	if (n == nullptr) {
		std::cout << std::endl;
		return;
	}

	constexpr char INDENT_STRING[] = " ";
	std::string indent;
	for (size_t i = 0; i < indentation; i++) indent += INDENT_STRING;

	std::cout << indent << INDENT_STRING << "- BB: [" << n->bounding_box.bottom_left
		<< ", " << n->bounding_box.top_right << "]" << std::endl;

	if (n->is_leaf)
		std::cout << indent << INDENT_STRING << "- LEAF: " << n->objects.size() << std::endl;
	else {
		std::cout << indent << "L:" << std::endl;
		visualize(n->left, indentation + 1);
		std::cout << indent << "R:" << std::endl;
		visualize(n->right, indentation + 1);
	}
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
	if (!n->bounding_box.intersect(r))
		return;
	// TODO
	if (n->is_leaf) {
		for (const auto& object : n->objects) {
			// determine if object intersects with ray
			std::optional<std::vector<float>> hits = object->intersect(r);
			if (hits.has_value() && !hits->empty()) {
				// if object is closer than closest in hit_info, update hit_info
				float closest = (*hits)[0];
				if (!hit_info.has_value() || closest < hit_info->hits[0]) {
					hit_info = HitInfo();
					hit_info->hits = *hits;
					hit_info->object = object;
				}
			}
		}
	}
	else {
		// intersect with left and right
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
	assert(0 <= start_pos && start_pos < objects.size());
	assert(0 <= end_pos && end_pos <= objects.size());

	if (start_pos >= end_pos) return nullptr;
	BoundingBox full_bounds = objects[start_pos]->bounding_box();
	for (size_t i = start_pos; i < end_pos; i++)
		full_bounds = full_bounds.union_with(objects[i]->bounding_box());
	size_t dim = full_bounds.longest_axis();
	size_t mid = (start_pos + end_pos) / 2;
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

	std::vector<BucketInfo> buckets(buckets_);
	std::vector<float> costs(buckets_ - 1);

	for (size_t i = start_pos; i < end_pos; i++) {
		const auto& object = objects[i];
		float which = object->position()[dim];
		size_t bucket_index
			= std::clamp(static_cast<size_t>(which / buckets_),
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

	// find minimum cost partition
	for (size_t i = 0; i < costs.size(); i++) {
		float cost = costs[i];
		if (bucket_split_min_cost > costs[i]) {
			bucket_split_min_cost = costs[i];
			min_cost_split_bucket = i;
		}
	}

	float leaf_cost = end_pos - start_pos;
	if (end_pos - start_pos > MAX_NODES_PER_LEAF || bucket_split_min_cost < leaf_cost) {
		const auto& mid_iter = std::partition(objects.begin() + start_pos, objects.begin() + end_pos,
			[=](const auto& obj) {
				size_t bucket = buckets_ * full_bounds.relative_position(obj->position())[dim];
				if (bucket == buckets_) {
					bucket = buckets_ - 1;
				}
				return bucket <= min_cost_split_bucket;
			});
		mid = std::distance(objects.begin(), mid_iter);
		if (mid == start_pos)
			mid += 1;
		if (mid == end_pos)
			mid -= 1;

		std::unique_ptr<BVHNode> left_node = construct_BVHNode(objects, start_pos, mid);
		std::unique_ptr<BVHNode> right_node = construct_BVHNode(objects, mid, end_pos);

		std::unique_ptr<BVHNode> node = std::make_unique<BVHNode>();
		if (left_node != nullptr)
			left_node->parent = node.get();
		if (right_node != nullptr)
			right_node->parent = node.get();

		node->is_leaf = false;
		node->bounding_box = full_bounds;
		node->left = std::move(left_node);
		node->right = std::move(right_node);

		return node;
	}
	else {
		std::unique_ptr<BVHNode> bvh = std::make_unique<BVHNode>();
		bvh->is_leaf = true;
		bvh->bounding_box = full_bounds;
		for (size_t i = start_pos; i < end_pos; i++)
			bvh->objects.push_back(objects[i]);
		return bvh;
	}
	return nullptr;
}

bool BVH::debug_mode() const {
	return debug_;
}

void BVH::debug_mode(bool d) {
	debug_ = d;
}

} // namespace raytracer
