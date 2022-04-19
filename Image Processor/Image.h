#pragma once

#include <vector>
#include <string>

struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

struct Frame {
	std::vector<std::vector<Pixel>> pixels;
};

class Image {
private:
	std::vector<Frame> frames;

public:
	Image();
	Image(std::string fileName);

	bool load(std::string fileName);

	Pixel getPixel(unsigned char frameIndex, unsigned int col, unsigned int row);

	unsigned int getWidth();

	unsigned int getHeight();
};