#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
    const std::string& filename,
    const std::vector<unsigned char>& data,
    const size_t width,
    const size_t height,
    const size_t num_channels)
{
    assert(
        (num_channels == 3 || num_channels == 1) &&
        ".ppm only supports RGB or grayscale images");
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    std::ofstream output(filename.c_str(), std::ios::binary);
    if (!output) {
        return false;
    }
    if (num_channels == 3) {
        output << "P6 ";
    }
    else {
        output << "P5 ";
    }
    output << width << " " << height << " 255\n";
    for (size_t i = 0; i < width * height * num_channels; i++) {
        output << data[i];
    }

    if (output.fail()) {
        return false;
    }
    output.close();
    return true;
}