#include <iostream>
#include <optional>

#include "image.h"
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

	/* Ray r(
		Vec3f(1, 1, 1),
		Vec3f(-1, -1, -1));
	SphereObject s(Vec3f(-1, -1, -1), std::sqrt(3),
		Rgb(0, 0, 0), MaterialType::DIFFUSE); */
	/* Ray r(
		Vec3f(1, 0, 0),
		Vec3f(-1, 0, 0));
	SphereObject s(Vec3f(0, 0, -1), 1, Rgb(0, 0, 0), MaterialType::DIFFUSE); */
	/* Ray r(
		Vec3f(1, 0, 0),
		Vec3f(-1, 0, 0));
	SphereObject s(
		Vec3f(0, 0, -2),
		1, Rgb(0, 0, 0), MaterialType::DIFFUSE);
	std::optional<std::vector<float>> o = s.intersect(r);
	
	if (o) {
		std::cout << "Intersection point(s): ";
		for (const auto& f : *o) std::cout << f << " ";
		std::cout << std::endl;
	}
	else std::cout << "No intersection" << std::endl; */

	Image i(400, 300);
	for (size_t j = 0; j < i.height(); j++) {
		for (size_t k = 0; k < i.width(); k++) {
			i(j, k) = Rgb(1, 0, 0);
		}
	}
	for (size_t j = 100; j < 200; j++) {
		for (size_t k = 100; k < 200; k++) {
			i(j, k) = Rgb(0, 1, 0);
		}
	}
	i.write("test.ppm");

	return 0;
}
