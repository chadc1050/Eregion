#ifndef EREGION_CAMERA_H
#define EREGION_CAMERA_H

#include "linmath.h"

#include <array>

namespace eregion {

class Camera {
  public:
    Camera(std::array<float, 2> pos);

  private:
    std::array<float, 2> pos;
    mat4x4 proj;
    mat4x4 inverseProj;
    mat4x4 view;
    mat4x4 inverseView;
};
} // namespace eregion

#endif