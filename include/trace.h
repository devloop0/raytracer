#ifndef TRACE_H
#define TRACE_H

#include "scene.h"
#include "vec3.h"

namespace raytracer {

void render(Scene& s);
Rgb trace(const Ray& r, Scene& s, size_t bounce = 0);

} // namespace raytracer

#endif // TRACE_H
