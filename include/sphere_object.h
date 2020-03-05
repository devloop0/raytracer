#ifndef SPHERE_OBJECT_H
#define SPHERE_OBJECT_H

#include <optional>

#include "vec3.h"
#include "bounding_box.h"
#include "ray.h"
#include "scene.h"

namespace raytracer {

class SphereObject : public SceneObject {
public:
	SphereObject(const Vec3f& p, float r, const Rgb& c, MaterialType m);

	~SphereObject();

	BoundingBox bounding_box() const override;

	Vec3f position() const override;

	MaterialType material_type() const override;

	std::optional<float> intersect(const Ray& r) const override;

	Rgb color(const Scene& s, const Ray& r, size_t bounce) const override;

	ObjectType object_type() const override;

private:
	Vec3f position_;
	float radius_;
	Rgb color_;
	MaterialType material_type_;
};

} // namespace raytracer

#endif // SPHERE_OBJECT_H
