#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {
Window::Window() { printf("%s\n", glGetString(GL_VERSION)); }
} // namespace eregion
