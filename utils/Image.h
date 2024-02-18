#ifndef RAY_TRACING_IMAGE_H
#define RAY_TRACING_IMAGE_H

#include <fstream>
#include <string>
#include <iostream>

class Image {
public:
    int width;
    int height;
    double aspect_ratio;

    Image() = delete;

    Image(int image_width, int image_height)
            : width(image_width),
              height(image_height),
              aspect_ratio(static_cast<double>(image_width) / image_height) {}

    Image(int image_width, double aspect_ratio)
            : width(image_width),
              height(static_cast<int>(image_width / aspect_ratio)),
              aspect_ratio(aspect_ratio) {
        height = (height < 1) ? 1 : height;
    }

    Image(Image &&other) noexcept = default;
    Image& operator=(Image &&other) noexcept = default;
    Image(const Image &other) = default;
    Image& operator=(const Image &other) = default;
};

#endif //RAY_TRACING_IMAGE_H
