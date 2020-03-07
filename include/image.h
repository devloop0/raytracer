#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "vec3.h"

namespace raytracer {

class Image {
public:
	Image(size_t w, size_t h);

	~Image();

	const Rgb& operator()(size_t x, size_t y) const;

	Rgb& operator() (size_t x, size_t y);

	size_t width() const;

	size_t height() const;

	size_t size() const;

	void write(const std::string& file_name) const;
private:
	size_t width_;
	size_t height_;
	std::vector<Rgb> image_;
};
 
} // namespace raytracer

#endif // IMAGE_H
