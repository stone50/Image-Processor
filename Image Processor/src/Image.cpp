#include <fstream>

#include "Image.h"
#include "BMP.h"

using namespace std;

Image::Image() :
	pixels(std::vector<std::vector<Pixel>>())
{}
Image::Image(std::string fileName) {
	load(fileName);
}

bool Image::load(std::string fileName) {
	try {
		// load file into string fileContents
		ifstream imageFile(fileName, ifstream::binary);
		vector<unsigned char> fileContents;
		char byte;
		while (imageFile.get(byte)) {
			fileContents.push_back(byte);
		}

		// determine file format
		
		// check for BMP
		if (
			(fileContents[0] == 'B' && fileContents[1] == 'M') ||
			(fileContents[0] == 'B' && fileContents[1] == 'A') ||
			(fileContents[0] == 'C' && fileContents[1] == 'I') ||
			(fileContents[0] == 'C' && fileContents[1] == 'P') ||
			(fileContents[0] == 'I' && fileContents[1] == 'C') ||
			(fileContents[0] == 'P' && fileContents[1] == 'T') 
			) {
			return loadBMP(fileContents, pixels);
		}

		// check for another file format
		else if (false) {

		}

		// no supported file format was found
		else {
			return false;
		}

		return true;
	}
	catch (exception& e) {
		return false;
	}
}

Pixel Image::getPixel(unsigned int col, unsigned int row) {
	return pixels[row][col];
}

unsigned int Image::getWidth() {
	return pixels.size() > 0 ? (unsigned int)pixels[0].size() : 0;
}

unsigned int Image::getHeight() {
	return (unsigned int)pixels.size();
}