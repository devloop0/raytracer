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
	const Vec3f GRAY = Rgb(0.502, 0.502, 0.502),
	      TOPAZ = Rgb(0.0, 0.6, 0.88),
	      BRIGHT_GOLD = Rgb(0.85, 0.85, 0.10),
	      GRASS = Rgb(0.30, 0.74, 0.20),
	      SILVER = Rgb(0.75, 0.75, 0.75),
	      VIOLET_FLOWER = Rgb(0.75, 0.37, 1.0),
	      SIGN_BROWN = Rgb(0.38, 0.2, 0.07);

	std::vector<std::unique_ptr<SceneObject>> objects;
	std::unique_ptr<SphereObject> s1 = std::make_unique<SphereObject>(Vec3f(-1.2, 2, -30),
		1, ColorProperties{ .diffuse_color = GRAY, .specular_color = GRAY, .reflectivity = 0.5, .glossiness = 0.1 });
	std::unique_ptr<SphereObject> s1_2 = std::make_unique<SphereObject>(Vec3f(1.2, 2, -30),
		1, ColorProperties{ .diffuse_color = GRAY, .specular_color = GRAY, .reflectivity = 0.5, .glossiness = 0.1 });

	std::unique_ptr<SphereObject> s2 = std::make_unique<SphereObject>(Vec3f(0, -10000, -20),
		10000, ColorProperties{ .diffuse_color = Rgb(1, 0, 0) });

	std::unique_ptr<SphereObject> s3 = std::make_unique<SphereObject>(Vec3f(0, 3, -20),
		2, ColorProperties{ .transparency = 0.9 });

	std::unique_ptr<SphereObject> s4 = std::make_unique<SphereObject>(Vec3f(-5.2, 1, -25),
		0.5, ColorProperties{ .diffuse_color = BRIGHT_GOLD, .specular_color = BRIGHT_GOLD, .reflectivity = 0.5 });
	std::unique_ptr<SphereObject> s4_2 = std::make_unique<SphereObject>(Vec3f(-4.2, 1, -25),
		0.5, ColorProperties{ .diffuse_color = BRIGHT_GOLD, .specular_color = BRIGHT_GOLD, .reflectivity = 0.5 });
	std::unique_ptr<SphereObject> s4_3 = std::make_unique<SphereObject>(Vec3f(-4.7, 1, -27.5),
		0.5, ColorProperties{ .diffuse_color = BRIGHT_GOLD, .specular_color = BRIGHT_GOLD, .reflectivity = 0.5 });

	std::unique_ptr<SphereObject> s5 = std::make_unique<SphereObject>(Vec3f(-7.5, 5, -40),
		3.0, ColorProperties{ .diffuse_color = TOPAZ, .specular_color = TOPAZ, .reflectivity = 0.5, .shininess = 5 });

	std::unique_ptr<TriangleObject> t1 = std::make_unique<TriangleObject>(Vec3f(10, 1, -35),
		Vec3f(3, 1, -35), Vec3f(3, 4, -35), ColorProperties{ .transparency = 0.5 });
	std::unique_ptr<TriangleObject> t2 = std::make_unique<TriangleObject>(Vec3f(10, 1, -37.5),
		Vec3f(10, 4, -37.5), Vec3f(3, 4, -37.5), ColorProperties{ .transparency = 0.5 });
	std::unique_ptr<SphereObject> s6 = std::make_unique<SphereObject>(Vec3f(7, 3, -40),
		2, ColorProperties{ .diffuse_color = GRASS, .specular_color = GRASS, .reflectivity = 0.5 });

	std::unique_ptr<TriangleObject> t3 = std::make_unique<TriangleObject>(Vec3f(10, 1, -20),
		Vec3f(4, 1, -30), Vec3f(7, 4, -25), ColorProperties{ .diffuse_color = SILVER,
		.specular_color = SILVER, .reflectivity = 0.5 });

	std::unique_ptr<SphereObject> s7 = std::make_unique<SphereObject>(Vec3f(-7, 3, -25),
		1, ColorProperties{ .diffuse_color = VIOLET_FLOWER, .specular_color = VIOLET_FLOWER });
	std::unique_ptr<TriangleObject> t4 = std::make_unique<TriangleObject>(Vec3f(-6, 3, -20),
		Vec3f(-5, 3, -20), Vec3f(-6, 4, -20), ColorProperties{ .diffuse_color = SIGN_BROWN,
		.specular_color = SIGN_BROWN });

	objects.push_back(std::move(s1));
	objects.push_back(std::move(s1_2));
	objects.push_back(std::move(s2));
	objects.push_back(std::move(s3));

	objects.push_back(std::move(s4));
	objects.push_back(std::move(s4_2));
	objects.push_back(std::move(s4_3));

	objects.push_back(std::move(s5));

	objects.push_back(std::move(t1));
	objects.push_back(std::move(t2));
	objects.push_back(std::move(s6));

	objects.push_back(std::move(t3));
	
	objects.push_back(std::move(s7));
	objects.push_back(std::move(t4));

	Scene s(generate_area_light(Light(Vec3f(-20, 20, 30), Rgb(1, 1, 1), 1000), 3, 3, 0.5),
		std::move(objects),
		Vec3f(0, 5, 0),
		std::make_pair(1000, 800), 30
	);
	render(s);
	s.image().write("output.ppm");

	return 0;
}
