#pragma once

#include <vector>
#include <fstream>
#include "Geometry.hpp"

class Picture {
    struct Pixel {
        unsigned char b, g, r;
    };

    int width;
    int height;
    std::vector<Pixel> pixels; // пиксели

    int Clamp(double v) const;
public:
    Picture(int width, int height);
    void SetPixel(int x, int y, const Vec& vec);

    void Save(const std::string& filename);
};

Picture::Picture(int width, int height) {
    this->width = width;
    this->height = height;
    this->pixels.resize(width * height);
}

void Picture::SetPixel(int x, int y, const Vec& vec) {
    Pixel& p = pixels[(height - 1 - y) * width + x];
    p.r = Clamp(vec.x * 255);
    p.g = Clamp(vec.y * 255);
    p.b = Clamp(vec.z * 255);
}

int Picture::Clamp(double v) const {
    if (v < 0)
        return 0;

    if (v > 255)
        return 255;

    return v;
}

void Picture::Save(const std::string& filename) {
    int paddedsize = (width * height) * sizeof(Pixel);

    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };

    bmpfileheader[2] = (unsigned char)(paddedsize);
    bmpfileheader[3] = (unsigned char)(paddedsize >> 8);
    bmpfileheader[4] = (unsigned char)(paddedsize >> 16);
    bmpfileheader[5] = (unsigned char)(paddedsize >> 24);

    bmpinfoheader[4] = (unsigned char)(width);
    bmpinfoheader[5] = (unsigned char)(width >> 8);
    bmpinfoheader[6] = (unsigned char)(width >> 16);
    bmpinfoheader[7] = (unsigned char)(width >> 24);
    bmpinfoheader[8] = (unsigned char)(height);
    bmpinfoheader[9] = (unsigned char)(height >> 8);
    bmpinfoheader[10] = (unsigned char)(height >> 16);
    bmpinfoheader[11] = (unsigned char)(height >> 24);

    std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
    out.write((const char*)bmpfileheader, 14);
    out.write((const char*)bmpinfoheader, 40);
    out.write((const char*)pixels.data(), paddedsize);
    out.flush();
    out.close();
}
