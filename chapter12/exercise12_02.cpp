#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 600, 400, "My window"};
        win.wait_for_button();

        Graph_lib::Rectangle rect{Point{100, 100}, 100, 30};  // top left corner, width, height
        rect.set_color(Color::blue);
        win.attach(rect);

        Text text{Point{125, 120}, "Howdy!"};
        win.attach(text);

        win.set_label("Ch12 Exercise02");
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