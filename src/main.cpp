#include <iostream>
#include <optional>

#include "trace.h"
#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "scene.h"
#include "bounding_box.h"
#include "sphere_object.h"
#include "scene_object.h"

using namespace raytracer;

// TODO:
// 1. Reflection and refraction
// 2. BVH
// 3. Parallelize/Improve performance
// 4. Triangle
// 5. Soften shadows

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
	std::vector<std::unique_ptr<SceneObject>> objects;
	std::unique_ptr<SphereObject> s1 = std::make_unique<SphereObject>(Vec3f(0, 0, -23), 1, Rgb(1, 0, 0), MaterialType::DIFFUSE);
	std::unique_ptr<SphereObject> s2 = std::make_unique<SphereObject>(Vec3f(-1, 1, -19), 1, Rgb(0, 0, 1), MaterialType::DIFFUSE);
	objects.push_back(std::move(s1));
	objects.push_back(std::move(s2));

	Scene s(std::vector<Light>{
		Light(Vec3f(-20, 0, 30), Rgb(1, 1, 1))
	},
		std::move(objects),
		Vec3f(0, 0, 0),
				std::make_pair(640, 480), 30
	);
	render(s);
	s.image().write("output.ppm");

	return 0;
}
