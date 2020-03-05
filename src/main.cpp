#include <iostream>
#include <optional>

#include "vec3.h"
#include "ray.h"
#include "scene.h"
#include "bounding_box.h"
#include "sphere_object.h"
#include "scene_object.h"

using namespace raytracer;

int main(int argc, char* argv[]) {
	/* Ray r(
		Vec3f(1, 1, 1),
		Vec3f(-1, -1, -1));
	BoundingBox bb(
		Vec3f(-2, -2, -1),
		Vec3f(-2, -2, 2));
	std::optional<float> o = bb.intersect(r);*/

	Ray r(
		Vec3f(1, 1, 1),
		Vec3f(-1, -1, -1));
	SphereObject s(Vec3f(-1, -1, -1), std::sqrt(3),
		Rgb(0, 0, 0), MaterialType::DIFFUSE);
	std::optional<float> o = s.intersect(r);
	
	if (o) std::cout << "Intersection: " << *o << std::endl;
	else std::cout << "No intersection" << std::endl;

	return 0;
}
