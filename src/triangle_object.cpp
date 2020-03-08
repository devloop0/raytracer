#include "triangle_object.h"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "vec3.h"
#include "trace.h"

namespace raytracer {

TriangleObject::TriangleObject(const Vec3f& one, const Vec3f& two, const Vec3f& three, const ColorProperties& c) :
	vertexOne_(one), vertexTwo_(two), vertexThree_(three), color_properties_(c) {
        position_ = (1.0f / 3.0f) * (one + two + three);
}

TriangleObject::~TriangleObject() {

}

BoundingBox TriangleObject::bounding_box() const {
    // bottom left is min of all x,y,z; top right is max of all x,y,z 

    Vec3f bottomLeft = Vec3f(
        std::min({vertexOne_.x, vertexTwo_.x, vertexThree_.x}), 
        std::min({vertexOne_.y, vertexTwo_.y, vertexThree_.y}), 
        std::min({vertexOne_.z, vertexTwo_.z, vertexThree_.z})
    );

    Vec3f topRight = Vec3f(
        std::max({vertexOne_.x, vertexTwo_.x, vertexThree_.x}), 
        std::max({vertexOne_.y, vertexTwo_.y, vertexThree_.y}), 
        std::max({vertexOne_.z, vertexTwo_.z, vertexThree_.z})
    );

    return BoundingBox(bottomLeft, topRight);
}

Vec3f TriangleObject::position() const {
	return position_;
}

std::optional<std::vector<float>> TriangleObject::intersect(const Ray& r) const {
    Vec3f N = normal(vertexOne_); 

    if (N.dot(r.d) == 0) {
        // if dot(ray, normal) == 0, plane of triangle and ray are parallel
        // thus, no intersection. 
        return std::nullopt;
    } 

    // First Test
    float d = N.dot(vertexOne_); 	
    float t = (N.dot(r.o) + d) / N.dot(r.d);

    if (t < 0) return std::nullopt; // triangle behind ray origin
    
    // Inside-Triangle test
    Vec3f intersectionPoint = r.o + t * r.d; 

    Vec3f edgeOne = vertexTwo_ - vertexOne_;
    Vec3f intersectionOne = intersectionPoint - vertexOne_;
    if (N.dot(edgeOne.cross(intersectionOne)) < 0) {
        return std::nullopt; 
    }

    Vec3f edgeTwo = vertexThree_ - vertexTwo_;
    Vec3f intersectionTwo = intersectionPoint - vertexTwo_;
    if (N.dot(edgeTwo.cross(intersectionTwo)) < 0) {
        return std::nullopt;
    }

    Vec3f edgeThree = vertexOne_ - vertexThree_;
    Vec3f intersectionThree = intersectionPoint - vertexThree_;

    if (N.dot(edgeThree.cross(intersectionThree)) < 0) {
        return std::nullopt;
    }
    return std::vector<float>{t};
}

ObjectType TriangleObject::object_type() const {
	return ObjectType::TRIANGLE;
}

Vec3f TriangleObject::normal(const Vec3f& p) const {
    // surface normal invariant wrt p
	Vec3f edgeOne = vertexTwo_ - vertexOne_;
    Vec3f edgeTwo = vertexThree_ - vertexOne_;
	Vec3f temp = (edgeOne.cross(edgeTwo));
	assert(temp.dot(edgeOne) == 0);
	assert(temp.dot(edgeTwo) == 0);
	temp.normalize();
	return temp;
}

const ColorProperties TriangleObject::color_properties() const {
    return color_properties_;
}

} // namespace raytracer
