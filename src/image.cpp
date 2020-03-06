#include "image.h"

#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "vec3.h"

namespace raytracer {

Image::Image(size_t w, size_t h) : width_(w), height_(h),
	image_(std::vector<Rgb>(width_ * height_)) {
}

Image::~Image() {

}

size_t Image::width() const {
	return width_;
}

size_t Image::height() const {
	return height_;
}

size_t Image::size() const {
	return image_.size();
}

const Rgb& Image::operator()(size_t x, size_t y) const {
	assert(0 <= x && x < height());
	assert(0 <= y && y < width());
	size_t index = x * width_ + y;
	assert (0 <= index && index < size());
	return image_[index];
}

Rgb& Image::operator()(size_t x, size_t y) {
	assert(0 <= x && x < height());
	assert(0 <= y && y < width());
	size_t index = x * width_ + y;
	assert (0 <= index && index < size());
	return image_[index];
}

void Image::write(const std::string& file_name) const {
	std::ofstream o(file_name);
	o << "P3\n"
		<< std::to_string(width()) << " " << std::to_string(height()) << "\n"
		<< "255\n";
	for (const auto& p : image_) {
		o << std::to_string((size_t) (255 * p.r)) << " "
			<< std::to_string((size_t) (255 * p.g)) << " "
			<< std::to_string((size_t) (255 * p.b)) << "\n";
	}
	o.close();
}

} // namespace raytracer
