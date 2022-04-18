#include <fstream>

#include "BMP.h"

using namespace std;

bool loadBMP(const std::vector<unsigned char>& fileContents, std::vector<std::vector<Pixel>>& pixels) {
	unsigned int offset = 2;

	auto twoBytesToInt = [&]() -> unsigned short int {
		offset += 2;
		return (fileContents[(long long int)offset - 1] << 8) | fileContents[(long long int)offset - 2];
	};

	auto fourBytesToInt = [&]() -> unsigned int {
		offset += 4;
		return (fileContents[(long long int)offset - 1] << 24) | (fileContents[(long long int)offset - 2] << 16) | (fileContents[(long long int)offset - 3] << 8) | fileContents[(long long int)offset - 4];
	};

	// Bitmap file header
	unsigned int fileSize = fourBytesToInt();
	offset += 4;	// skip 4 reserved bytes
	unsigned int pixelArrayOffset = fourBytesToInt();

	// DIB header
	unsigned int dibSize = fourBytesToInt();
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned short int planes = 1;
	unsigned short int bitCount = 0;
	unsigned int compression = 0;
	unsigned int dataSize = 0;
	unsigned int xResolution = 0;
	unsigned int yResolution = 0;
	unsigned int colorsUsed = 0;
	unsigned int importantColors = 0;
	unsigned short int units = 0;
	unsigned short int recording = 0;
	unsigned short int rendering = 0;
	unsigned int size1 = 0;
	unsigned int size2 = 0;
	unsigned int colorEncoding = 0;
	unsigned int redMask = 0;
	unsigned int greenMask = 0;
	unsigned int blueMask = 0;
	unsigned int alphaMask = 0;
	unsigned int colorSpace = 0;
	unsigned int endpointRX = 0;	// each of these endpoint components are fixed-points values with a 2-bit integer part and a 30-bit fractional part 
	unsigned int endpointRY = 0;
	unsigned int endpointRZ = 0;
	unsigned int endpointGX = 0;
	unsigned int endpointGY = 0;
	unsigned int endpointGZ = 0;
	unsigned int endpointBX = 0;
	unsigned int endpointBY = 0;
	unsigned int endpointBZ = 0;
	unsigned int gammaRed = 0;
	unsigned int gammaGreen = 0;
	unsigned int gammaBlue = 0;
	unsigned int intent = 0;
	unsigned int profileData = 0;
	unsigned int profileSize = 0;

	// different DIB header sizes indicate different versions
	// data needs to be read differently depending on the version
	switch (dibSize) {
	case 12:	// BITMAPCOREHEADER and OS21XBITMAPHEADER
		width = twoBytesToInt();
		height = twoBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		break;

	case 64:	// OS22XBITMAPHEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();
		units = twoBytesToInt();
		offset += 2;	// skip 2 bytes used for padding to reach 4-byte boundary
		recording = twoBytesToInt();
		rendering = twoBytesToInt();
		size1 = fourBytesToInt();
		size2 = fourBytesToInt();
		colorEncoding = fourBytesToInt();
		offset += 4;	// skip 4 reserved bytes
		break;

	case 16:	// OS22XBITMAPHEADER variation
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		break;

	case 40:	// BITMAPINFOHEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();

		// check for extra bit masks
		switch (compression) {
		case 3:
			redMask = fourBytesToInt();
			greenMask = fourBytesToInt();
			blueMask = fourBytesToInt();
			break;

		case 6:
			redMask = fourBytesToInt();
			greenMask = fourBytesToInt();
			blueMask = fourBytesToInt();
			alphaMask = fourBytesToInt();
			break;
		}
		break;

	case 52:	// BITMAPV2INFOHEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();
		redMask = fourBytesToInt();
		greenMask = fourBytesToInt();
		blueMask = fourBytesToInt();
		break;
	
	case 56:	// BITMAPV3INFOHEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();
		redMask = fourBytesToInt();
		greenMask = fourBytesToInt();
		blueMask = fourBytesToInt();
		alphaMask = fourBytesToInt();
		break;
	
	case 108:	// BITMAPV4HEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();
		redMask = fourBytesToInt();
		greenMask = fourBytesToInt();
		blueMask = fourBytesToInt();
		alphaMask = fourBytesToInt();
		colorSpace = fourBytesToInt();
		endpointRX = fourBytesToInt();
		endpointRY = fourBytesToInt();
		endpointRZ = fourBytesToInt();
		endpointGX = fourBytesToInt();
		endpointGY = fourBytesToInt();
		endpointGZ = fourBytesToInt();
		endpointBX = fourBytesToInt();
		endpointBY = fourBytesToInt();
		endpointBZ = fourBytesToInt();
		gammaRed = fourBytesToInt();
		gammaGreen = fourBytesToInt();
		gammaBlue = fourBytesToInt();
		break;
	
	case 124:	// BITMAPV5HEADER
		width = fourBytesToInt();
		height = fourBytesToInt();
		offset += 2;	// skip 2 bytes indicating the number of planes
		bitCount = twoBytesToInt();
		compression = fourBytesToInt();
		dataSize = fourBytesToInt();
		xResolution = fourBytesToInt();
		yResolution = fourBytesToInt();
		colorsUsed = fourBytesToInt();
		importantColors = fourBytesToInt();
		redMask = fourBytesToInt();
		greenMask = fourBytesToInt();
		blueMask = fourBytesToInt();
		alphaMask = fourBytesToInt();
		colorSpace = fourBytesToInt();
		endpointRX = fourBytesToInt();
		endpointRY = fourBytesToInt();
		endpointRZ = fourBytesToInt();
		endpointGX = fourBytesToInt();
		endpointGY = fourBytesToInt();
		endpointGZ = fourBytesToInt();
		endpointBX = fourBytesToInt();
		endpointBY = fourBytesToInt();
		endpointBZ = fourBytesToInt();
		gammaRed = fourBytesToInt();
		gammaGreen = fourBytesToInt();
		gammaBlue = fourBytesToInt();
		intent = fourBytesToInt();
		profileData = fourBytesToInt();
		profileSize = fourBytesToInt();
		offset += 4;	// skip 4 reserved bytes
		break;

	default:
		return false;
	}

	// check for color table
	vector<Pixel> colorTable;
	if (offset != pixelArrayOffset) {
		unsigned int colorTableEntries = ((colorsUsed == 0) ? (unsigned int)pow(2, bitCount) : colorsUsed);
		for (unsigned int i = 0; i < colorTableEntries; i++) {
			Pixel p{};
			p.blue = fileContents[offset++];
			p.green = fileContents[offset++];
			p.red = fileContents[offset++];
			p.alpha = (dibSize == 12) ? 255 : fileContents[offset++];
			colorTable.push_back(p);
		}
	}

	offset = pixelArrayOffset;

	// apply bit masks
	unsigned char redShift = 0;
	unsigned char greenShift = 0;
	unsigned char blueShift = 0;
	unsigned char alphaShift = 0;
	switch (compression) {
	case 6:
	{
		unsigned int tempAlphaMask = alphaMask;
		while (!(tempAlphaMask & 1)) {
			tempAlphaMask >>= 1;
			alphaShift++;
		}
	}
	case 3:
	{
		unsigned int tempRedMask = redMask;
		while (!(tempRedMask & 1)) {
			tempRedMask >>= 1;
			redShift++;
		}
		unsigned int tempGreenMask = greenMask;
		while (!(tempGreenMask & 1)) {
			tempGreenMask >>= 1;
			greenShift++;
		}
		unsigned int tempBlueMask = blueMask;
		while (!(tempBlueMask & 1)) {
			tempBlueMask >>= 1;
			blueShift++;
		}
		break;
	}
	}

	// read pixel array
	pixels = vector<vector<Pixel>>(height, vector<Pixel>(width, Pixel()));
	unsigned char padding = (unsigned char)(ceil(bitCount * width / 32.0) * 4) - (bitCount * width / 8);
	switch (bitCount) {
	case 1:
	case 2:
	case 4:
	{
		unsigned char compareTo = (unsigned int)pow(2, bitCount) - 1;
		for (unsigned int row = 0; row < height; row++) {
			vector<Pixel> currentRow;
			currentRow.reserve(width);
			unsigned char bitOffset = 0;
			for (unsigned int col = 0; col < width; col++) {
				currentRow.push_back(colorTable[(unsigned short int)((fileContents[offset] >> (7 - bitOffset)) & compareTo)]);
				if ((bitOffset += bitCount) > 7) {
					bitOffset %= 8;
					offset++;
				}
			}
			offset += padding;
			pixels.at((long long int)(height - row - 1)) = currentRow;
		}
		break;
	}

	case 8:
		for (unsigned int row = 0; row < height; row++) {
			vector<Pixel> currentRow;
			currentRow.reserve(width);
			for (unsigned int col = 0; col < width; col++) {
				currentRow.push_back(colorTable[fileContents[offset++]]);
			}
			pixels.at((long long int)(height - row - 1)) = currentRow;
		}
		break;

	case 16:
		for (unsigned int row = 0; row < height; row++) {
			vector<Pixel> currentRow;
			currentRow.reserve(width);
			for (unsigned int col = 0; col < width; col++) {
				unsigned int currentPixelVal = twoBytesToInt();
				currentRow.push_back(Pixel{
					(unsigned char)((currentPixelVal & blueMask) >> blueShift),
					(unsigned char)((currentPixelVal & greenMask) >> greenShift),
					(unsigned char)((currentPixelVal & redMask) >> redShift),
					(unsigned char)((currentPixelVal & alphaMask) >> alphaShift),
				});
			}
			offset += padding;
			pixels.at((long long int)(height - row - 1)) = currentRow;
		}
		break;

	case 24:
		for (unsigned int row = 0; row < height; row++) {
			vector<Pixel> currentRow;
			currentRow.reserve(width);
			for (unsigned int col = 0; col < width; col++) {
				Pixel p{};
				p.blue = fileContents[offset++];
				p.green = fileContents[offset++];
				p.red = fileContents[offset++];
				p.alpha = 255;
				currentRow.push_back(p);
			}
			offset += padding;
			pixels.at((long long int)(height - row - 1)) = currentRow;
		}
		break;

	case 32:
		for (unsigned int row = 0; row < height; row++) {
			vector<Pixel> currentRow;
			currentRow.reserve(width);
			for (unsigned int col = 0; col < width; col++) {
				unsigned int currentPixelVal = fourBytesToInt();
				currentRow.push_back(Pixel{
					(unsigned char)((currentPixelVal & blueMask) >> blueShift),
					(unsigned char)((currentPixelVal & greenMask) >> greenShift),
					(unsigned char)((currentPixelVal & redMask) >> redShift),
					(unsigned char)((currentPixelVal & alphaMask) >> alphaShift),
				});
			}
			offset += padding;
			pixels.at((long long int)(height - row - 1)) = currentRow;
		}
		break;

	default:
		return false;
	}
	
	return true;
}