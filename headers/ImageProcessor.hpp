#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "bitmap_image.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
  Gray-Scaled images.
*/

#define Image bitmap_image

typedef unsigned int u_int32;

class ImageProcessor {
public:
    struct Pair {
        Pair() { }
        Pair(int _first, int _second)
            : first(_first)
            , second(_second)
        {
        }
        int first, second;
    };

    Image applyThreshold(Image image, const int& th);
    Image applyMedianFilter(Image image);
    Image applyErosion(Image image);
    Image applyDilation(Image image);
    Pair hitter(const Image& image, u_int32 x, u_int32 y);
    Pair structuringElement3(const Image& image, u_int32 x, u_int32 y);

    inline static bool validPoint(const Image& image, const u_int32& x, const u_int32& y)
    {
        return x >= 0 && x < image.width() && y >= 0 && y < image.height();
    }

private:
};

#endif
