#ifndef SAMPLE_SCENES_H
#define SAMPLE_SCENES_H

#include "scene.h"

namespace raytracer {

Scene sample_scene1(size_t width = 1000, size_t height = 800, bool hq = false);
Scene balls(size_t width = 1000, size_t height = 800, size_t num_objects = 0);

} // namespace raytracer

#endif // SAMPLE_SCENES_H
