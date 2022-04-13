#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int fourByteToInt(const unsigned char c1, const unsigned char c2, const unsigned char c3, const unsigned char c4) {
	return (c1 * 16777216) + (c2 * 65536) + (c3 * 256) + c4;
}

struct pixel {
	char red;
	char green;
	char blue;
	char alpha;
};

void readColorTypeZero(const string& fileContents, char bitDepth, vector<vector<pixel>>& pixels) {
	int currentIndex = 33;
	while (true) {	// loop through chunks
		int chunkLength = fourByteToInt(fileContents[currentIndex], fileContents[currentIndex + 1], fileContents[currentIndex + 2], fileContents[currentIndex + 3]);
		if (fileContents[currentIndex + 8] == 'I') {
			if (fileContents[currentIndex + 9] == 'E') {
				break;	// end of image data
			}
			// read data from chunk

		}
		currentIndex += chunkLength + 12;
	}
}

int main() {
	//ifstream imageFile("relax.png", ifstream::binary);
	//ifstream imageFile("Bash_112x112.png", ifstream::binary);
	ifstream imageFile("Smug_28x28.png", ifstream::binary);
	string fileContents((std::istreambuf_iterator<char>(imageFile)), istreambuf_iterator<char>());

	int width = fourByteToInt(fileContents[16], fileContents[17], fileContents[18], fileContents[19]);
	int height = fourByteToInt(fileContents[20], fileContents[21], fileContents[22], fileContents[23]);
	char bitDepth = fileContents[24];
	char colorType = fileContents[25];

	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	cout << "Bit Depth: " << (int)bitDepth << endl;
	cout << "Color Type: " << (int)colorType << endl;
	cout << endl;

	int paletteIndex = -1;

	vector<vector<pixel>> pixels = vector<vector<pixel>>(width, vector<pixel>(height, pixel()));

	// Gather chunk data

	switch (colorType) {
	case 0:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	case 6:
		break;
	}


	return 1;
}

