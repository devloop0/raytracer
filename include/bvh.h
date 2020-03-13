#ifndef BVH_H
#define BVH_H

#include <memory>
#include <vector>

#include "ray.h"
#include "bounding_box.h"
#include "scene_object.h"

namespace raytracer {

class BVH {
public:
	struct HitInfo {
		const SceneObject* object;
		std::vector<float> hits;
	};

	BVH(size_t buckets = 12, bool d = false);

	BVH(const std::vector<std::unique_ptr<SceneObject>>& objects,
		size_t buckets = 12, bool d = false);

	~BVH();

	void construct(const std::vector<std::unique_ptr<SceneObject>>& objects);

	std::optional<HitInfo> intersect(const Ray& r) const;

	void debug_mode(bool d);

	bool debug_mode() const;

private:
	struct BVHNode {
        	bool is_leaf = false;
		BoundingBox bounding_box = BoundingBox();
		std::unique_ptr<BVHNode> left = nullptr, right = nullptr;
		BVHNode* parent = nullptr;
		std::vector<const SceneObject*> objects = std::vector<const SceneObject*>();
	};

	void intersect(const Ray& r, const std::unique_ptr<BVHNode>& n, std::optional<HitInfo>& hit_info) const;

	std::unique_ptr<BVHNode> construct_BVHNode(std::vector<const SceneObject*> objects,
		size_t start_pos, size_t end_pos);

	void visualize(const std::unique_ptr<BVHNode>& n, size_t indentation = 0) const;

	std::unique_ptr<BVHNode> root_;
	size_t buckets_;
	const size_t MAX_NODES_PER_LEAF = 8;
	bool debug_ = false;
};

} // namespace raytracer

#endif // BVH_H
