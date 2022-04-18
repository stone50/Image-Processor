#pragma once

#include "Image.h"

bool loadBMP(const std::vector<unsigned char>& fileContents, std::vector<std::vector<Pixel>>& pixels);