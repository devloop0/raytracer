#ifndef TRIANGLE_OBJECT_H
#define TRIANGLE_OBJECT_H

#include <optional>

#include "vec3.h"
#include "bounding_box.h"
#include "ray.h"
#include "scene.h"

namespace raytracer {

class TriangleObject : public SceneObject {
public:
	TriangleObject(const Vec3f& one, const Vec3f& two, const Vec3f& three, const ColorProperties& cp);

	~TriangleObject();

	BoundingBox bounding_box() const override;

	Vec3f position() const override;

	std::optional<std::vector<float>> intersect(const Ray& r) const override;

	Vec3f normal(const Vec3f& p) const override;

	ObjectType object_type() const override;

	const ColorProperties color_properties() const override;

	float surface_area() const override;

private:
	Vec3f vertexOne_, vertexTwo_, vertexThree_, position_;
	ColorProperties color_properties_;
};

} // namespace raytracer

#endif // TRIANGLE_OBJECT_H
