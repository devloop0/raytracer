#include <iostream>
#include <optional>

#include "trace.h"
#include "triangle_object.h"
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
	std::vector<std::unique_ptr<SceneObject>> objects;
	std::unique_ptr<SphereObject> s1 = std::make_unique<SphereObject>(Vec3f(0, 2, -20),
		1, ColorProperties{ .diffuse_color = Rgb(0.502, 0.502, 0.502), .reflectivity = 0.5, .glossiness = 0.1 });
	std::unique_ptr<SphereObject> s2 = std::make_unique<SphereObject>(Vec3f(0, -100, -20),
		100, ColorProperties{ .diffuse_color = Rgb(1, 0, 0) });
	objects.push_back(std::move(s1));
	objects.push_back(std::move(s2));

	Scene s(generate_area_light(Light(Vec3f(-20, 20, 30), Rgb(1, 1, 1), 1), 3, 3, 0.5),
		std::move(objects),
		Vec3f(0, 3, 0),
		std::make_pair(1000, 800), 30
	);
	render(s);
	s.image().write("output.ppm");

	return 0;
}
