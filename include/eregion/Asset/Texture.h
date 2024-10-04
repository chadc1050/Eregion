#pragma once

#include <string>

namespace eregion {
struct Texture {
    std::string name;
    unsigned char* src;
    int width;
    int height;
    int channels;
};
} // namespace eregion