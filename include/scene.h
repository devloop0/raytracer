#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>

#include "vec3.h"

namespace raytracer {

class Scene {
public:
	Scene(const std::vector<Vec3f>& ls,
		const Vec3f& e,
		const Vec3f& v,
		const std::pair<size_t, size_t>& sd,
		const std::pair<float, float>& nf);

	~Scene();

	Vec3f light(size_t i) const;

	std::vector<Vec3f> lights() const;

	Vec3f eye() const;

	Vec3f view() const;

	float near() const;

	float far() const;

	size_t screen_width() const;

	size_t screen_height() const;

private:
	std::vector<Vec3f> lights_;
	Vec3f eye_;
	Vec3f view_;
	std::pair<size_t, size_t> screen_dims_;
	std::pair<float, float> near_far_;
};

} // namespace raytracer

#endif // SCENE_H
