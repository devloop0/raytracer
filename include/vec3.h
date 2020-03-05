#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

namespace raytracer {

template<class T> struct Vec3 {
	Vec3() {
	
	}

	Vec3(T x, T y, T z) : x(x), y(y), z(z) {

	}

	~Vec3() {

	}

	Vec3<T> operator*(const Vec3<T>& other) const {
		return Vec3<T>(
			x * other.x,
			y * other.y,
			z * other.z);
	}

	Vec3<T> operator*(const T& c) const {
		return Vec3<T>(
			x * c,
			y * c,
			z * c);
	}

	Vec3<T>& operator*=(const Vec3<T>& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3<T>& operator*=(const T& c) {
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	Vec3<T> operator+(const Vec3<T>& other) const {
		return Vec3<T>(
			x + other.x,
			y + other.y,
			z + other.z);
	}

	Vec3<T> operator+(const T& c) const {
		return Vec3<T>(
			x + c,
			y + c,
			z + c);
	}

	Vec3<T>& operator+=(const Vec3<T>& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3<T>& operator+=(const T& c) {
		x += c;
		y += c;
		z += c;
		return *this;
	}

	Vec3<T> operator-(const Vec3<T>& other) const {
		return Vec3<T>(
			x - other.x,
			y - other.y,
			z - other.z);
	}

	Vec3<T> operator-(const T& c) const {
		return Vec3<T>(
			x - c,
			y - c,
			z - c);
	}

	Vec3<T>& operator-=(const Vec3<T>& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3<T>& operator-=(const T& c) {
		x -= c;
		y -= c;
		z -= c;
	}

	Vec3<T> operator/(const Vec3<T>& other) const {
		return Vec3<T>(
			x / other.x,
			y / other.y,
			z / other.z);
	}

	Vec3<T> operator/(const T& c) const {
		return Vec3<T>(
			x / c,
			y / c,
			z / c);
	}

	Vec3<T>& operator/=(const Vec3<T>& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vec3<T>& operator/=(const T& c) {
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	T dot(const Vec3<T>& other) const {
		return x * other.x
			+ y * other.y
			+ z * other.z;
	}

	T norm() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() {
		*this /= norm();
	}

	Vec3<T> cross(const Vec3<T>& other) const {
		return Vec3<T>(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	union {
		T x;
		T r;
	};

	union {
		T y;
		T g;
	};

	union {
		T z;
		T b;
	};
};

template<class T> Vec3<T> operator+(const T& c, const Vec3<T>& other) {
	return Vec3<T>(
		c + other.x,
		c + other.y,
		c + other.z);
}

template<class T> Vec3<T> operator-(const T& c, const Vec3<T>& other) {
	return Vec3<T>(
		c - other.x,
		c - other.y,
		c - other.z);
}

template<class T> Vec3<T> operator*(const T& c, const Vec3<T>& other) {
	return Vec3<T>(
		c * other.x,
		c * other.y,
		c * other.z);
}

template<class T> Vec3<T> operator/(const T& c, const Vec3<T>& other) {
	return Vec3<T>(
		c / other.x,
		c / other.y,
		c / other.z);
}

using Vec3f = Vec3<float>;
using Rgb = Vec3<float>;

template<class T> std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}

} // namespace raytracer

#endif // VEC3_H
