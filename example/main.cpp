#include "eregion/Window/Window.h"

int main() {
    printf("Starting...\n");

    eregion::Window* window = new eregion::Window();
    delete window;
    return 0;
}