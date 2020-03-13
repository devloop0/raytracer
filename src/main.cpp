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

using namespace raytracer;

int main(int argc, char* argv[]) {
	Scene s = sample_scene1();
	render(s);
	s.image().write("output.ppm");

	return 0;
}
