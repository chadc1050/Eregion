#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GL/glx.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace eregion {
class Window {
  private:
    unsigned long window;
    Display* display;
    int screen;

  public:
    Window();
    void start();
};
} // namespace eregion

#endif