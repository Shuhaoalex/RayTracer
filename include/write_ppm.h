#ifndef WRITE_PPM_H
#define WRITE_PPM_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// Write an rgb or grayscale image to a .ppm file.
//
// Inputs:
//   filename  path to .ppm file as string
//   data  width*heigh*num_channels array of image intensity data
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   num_channels  number of channels (e.g., for rgb 3, for grayscale 1)
// Returns true on success, false on failure (e.g., can't open file)
bool write_ppm(
    const std::string& filename,
    const std::vector<unsigned char>& data,
    const size_t width,
    const size_t height)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    std::ofstream output(filename.c_str(), std::ios::binary);
    if (!output) {
        return false;
    }
    output << "P6 ";
    output << width << " " << height << " 255\n";
    for (const unsigned char &e: data) {
        output << e;
    }

    if (output.fail()) {
        return false;
    }
    output.close();
    return true;
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void fill_color(
    std::vector<unsigned char>& data,
    const size_t width,
    const size_t height,
    const size_t i,
    const size_t j,
    const color c) {
    size_t curr_idx = (j * width + i) * 3;
    vec3 clamped_c = c.cwiseSqrt().cwiseMax(0.0).cwiseMin(1.0);
    data[curr_idx] = static_cast<unsigned char>(255 * clamped_c[0]);
    data[curr_idx + 1] = static_cast<unsigned char>(255 * clamped_c[1]);
    data[curr_idx + 2] = static_cast<unsigned char>(255 * clamped_c[2]);
}

#endif
