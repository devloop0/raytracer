#ifndef TRACE_H
#define TRACE_H

#include "scene.h"

namespace raytracer {

void trace(Scene& s, size_t bounce = 0);

} // namespace raytracer

#endif // TRACE_H
