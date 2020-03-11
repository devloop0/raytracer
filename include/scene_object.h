#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <optional>
#include <vector>

#include "bounding_box.h"
#include "vec3.h"
#include "ray.h"

namespace raytracer {

enum class ObjectType {
	SPHERE, TRIANGLE
};

class Scene;

struct ColorProperties {
	Rgb diffuse_color = Rgb(0, 0, 0);
	Rgb specular_color = Rgb(0, 0, 0);
	float reflectivity = 0;
	float transparency = 0;
	float glossiness = 0;
	float transparent_glossiness = 0;
	float shininess = 16.0;
};

class SceneObject {
public:
	virtual BoundingBox bounding_box() const = 0;

	virtual Vec3f position() const = 0;

	virtual ObjectType object_type() const = 0;

	virtual std::optional<std::vector<float>> intersect(const Ray& r) const = 0;

	virtual Vec3f normal(const Vec3f& p) const = 0;

	virtual const ColorProperties color_properties() const = 0;

	virtual float surface_area() const = 0;
};

} // namespace raytracer

#endif // SCENE_OBJECT_H
