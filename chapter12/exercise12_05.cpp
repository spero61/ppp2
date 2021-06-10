// my screen resolution is 2560 x 1440 (QHD)

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{0, 0};
        Simple_window win{tl, 2560, 1440, "this label is invisible"};
        win.wait_for_button();

        Graph_lib::Rectangle rect{Point{427, 180}, 1707, 1080};  // top left corner, width, height
        rect.set_color(Color::red);
        rect.set_style(Line_style(Line_style::solid, 24));
        rect.set_fill_color(Color::cyan);
        win.attach(rect);

        win.set_label("Ch12 Exercise05");
        win.wait_for_button();

        // alternatively we can draw a frame using polygon instead.
        /*
        Closed_polyline poly_rect;
        poly_rect.add(Point{ 427,180 });
        poly_rect.add(Point{ 2134,180 });
        poly_rect.add(Point{ 2134,1260 });
        poly_rect.add(Point{ 427,1260 });
        poly_rect.set_color(Color::red);
        poly_rect.set_style(Line_style(Line_style::solid, 24));
        win.attach(poly_rect);

        win.set_label("Ch12 Exercise05_alter");
        win.wait_for_button();
        */

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}