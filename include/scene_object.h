#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <optional>
#include <vector>

#include "bounding_box.h"
#include "vec3.h"
#include "ray.h"

namespace raytracer {

enum class MaterialType {
	DIFFUSE,
	REFLECTIVE,
	REFRACTIVE
};

enum class ObjectType {
	NONE,
	SPHERE
};

class Scene;

class SceneObject {
public:
	virtual BoundingBox bounding_box() const = 0;

	virtual Vec3f position() const = 0;

	virtual MaterialType material_type() const = 0;

	virtual std::optional<std::vector<float>> intersect(const Ray& r) const = 0;

	virtual Vec3f normal(const Vec3f& p) const = 0;

	virtual ObjectType object_type() const;

	virtual Rgb diffuse_color() const = 0;
};

} // namespace raytracer

#endif // SCENE_OBJECT_H
