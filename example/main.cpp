#include "eregion/Window/Window.h"

int main() {
    eregion::Window* window = new eregion::Window();
    window->start();
    delete window;
    return 0;
}