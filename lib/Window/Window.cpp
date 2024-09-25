#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {
Window::Window() {

    GLint majorGLX, minorGLX = 0;
    glXQueryVersion(display, &majorGLX, &minorGLX);

    std::cout << "GLX Version: " << majorGLX << "." << minorGLX << "\n";

    display = XOpenDisplay(NULL);

    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    // Create a simple window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 600, 1, BlackPixel(display, screen),
                                 WhitePixel(display, screen));
}

void Window::start() {

    XEvent event;

    // Select input events for the window (here we want exposure events and key
    // press events)
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map (show) the window on the screen
    XMapWindow(display, window);

    // Event loop
    while (1) {
        XNextEvent(display, &event); // Get the next event from the queue

        // Handle the event types
        if (event.type == Expose) {
            // Expose event - the window is ready to be drawn on
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
        }

        if (event.type == KeyPress) {
            // Key press event - exit when a key is pressed
            break;
        }
    }

    // Close the connection to the X server
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
} // namespace eregion
