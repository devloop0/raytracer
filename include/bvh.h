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

	BVH(const std::vector<std::unique_ptr<SceneObject>>& objects,
		size_t buckets = 12);

	~BVH();

	std::optional<HitInfo> intersect(const Ray& r) const;

private:
	struct BVHNode {
        bool is_leaf = false;
		BoundingBox bounding_box = BoundingBox();
		std::unique_ptr<BVHNode> left = nullptr, right = nullptr, parent = nullptr;
		std::vector<const SceneObject*> objects = std::vector<const SceneObject*>();
	};

	void intersect(const Ray& r, const std::unique_ptr<BVHNode>& n, std::optional<HitInfo>& hit_info) const;

	std::unique_ptr<BVHNode> construct_BVHNode(std::vector<const SceneObject*> objects);

	std::unique_ptr<BVHNode> root_;
	size_t buckets_;
};

} // namespace raytracer

#endif // BVH_H