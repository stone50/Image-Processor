#include<windows.h>
#include<iostream>

#include "Image.h"

using namespace std;

int main() {
    Image img("bitmap.bmp");

    //Get a console handle
    HWND myconsole = GetConsoleWindow();

    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    //Draw pixels
    for (unsigned int row = 0; row < img.getHeight(); row++) {
        for (unsigned int col = 0; col < img.getWidth(); col++) {
            SetPixel(mydc, col, row, RGB(img.getPixel(col, row).red, img.getPixel(col, row).green, img.getPixel(col, row).blue));
        }
    }

    img.~Image();
    ReleaseDC(myconsole, mydc);
    cin.ignore();
    return 0;
}