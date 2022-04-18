#include <iostream>

#include "Image.h"

using namespace std;

int main() {
	string fileName("bitmap.bmp");
	Image bmp;
	bool success = bmp.load(fileName);
	if (success) {
		cout << fileName << " loaded successfully!" << endl;
	}
	else {
		cout << fileName << " did not load" << endl;
	}
	return 1;
}