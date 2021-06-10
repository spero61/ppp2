// case2: When a Window does not fit on the screen.

// It only shows the part that fit on the screen.
// It maintains its over-fitting window size as we move(drag-and-drop) the Window
// (For instance, it is possible to check with dual screen monitors)

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 3840, 1024, "Ch12 Exercise06_case02"};

        win.wait_for_button();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}