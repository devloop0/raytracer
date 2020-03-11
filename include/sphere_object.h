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
	SphereObject(const Vec3f& p, float r, ColorProperties cp);

	~SphereObject();

	BoundingBox bounding_box() const override;

	Vec3f position() const override;

	std::optional<std::vector<float>> intersect(const Ray& r) const override;

	Vec3f normal(const Vec3f& p) const override;

	ObjectType object_type() const override;

	const ColorProperties color_properties() const override;

	float surface_area() const override;

private:
	Vec3f position_;
	float radius_;
	ColorProperties color_properties_;
};

} // namespace raytracer

#endif // SPHERE_OBJECT_H
