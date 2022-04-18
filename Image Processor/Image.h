#pragma once

#include <vector>
#include <string>

struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

class Image {
private:
	std::vector<std::vector<Pixel>> pixels;

public:
	Image();
	Image(std::string fileName);

	bool load(std::string fileName);

	Pixel getPixel(int col, int row);

	int getWidth();

	int getHeight();
};