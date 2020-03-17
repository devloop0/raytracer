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
#include "bvh.h"
#include "sample_scenes.h"
#include <iostream>

using namespace raytracer;

int main(int argc, char* argv[]) {
	for (size_t i = 0; i <= 3600; i += 400) {
		Scene s = balls(1920, 1080, i);
		render(s);
		s.image().write("output" + std::to_string(i/400) + ".ppm");
		std::cout << std::to_string(i/400) << std::endl;
	}

	return 0;
}
