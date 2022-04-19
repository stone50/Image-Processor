#include <fstream>

#include "Image.h"
#include "BMP.h"

using namespace std;

Image::Image() :
	frames(vector<Frame>())
{}
Image::Image(string fileName) {
	load(fileName);
}

bool Image::load(string fileName) {
	frames = vector<Frame>();
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
			frames.push_back(Frame{});
			return loadBMP(fileContents, frames[0].pixels);
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
		throw e;
		return false;
	}
}

unsigned char Image::getFrameCount() {
	return (unsigned char)frames.size();
}

Pixel Image::getPixel(unsigned char frameIndex,  unsigned int col, unsigned int row) {
	return frames.size() == 0 ? Pixel{} : frames[frameIndex].pixels[row][col];
}

unsigned int Image::getWidth() {
	return frames.size() == 0 ? 0 : (unsigned int)frames[0].pixels[0].size();
}

unsigned int Image::getHeight() {
	return frames.size() == 0 ? 0 : (unsigned int)frames[0].pixels.size();
}