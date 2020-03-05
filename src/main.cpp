#include <iostream>
#include <optional>

#include "vec3.h"
#include "scene.h"
#include "bounding_box.h"

using namespace raytracer;

int main(int argc, char* argv[]) {
	Ray r(
		Vec3f(1, 1, 1),
		Vec3f(-1, -1, -1));
	BoundingBox bb(
		Vec3f(-2, -2, -1),
		Vec3f(-2, -2, 2));

	std::optional<float> o = bb.intersect(r);
	if (o) std::cout << "Intersection: " << *o << std::endl;
	else std::cout << "No intersection" << std::endl;

	return 0;
}
