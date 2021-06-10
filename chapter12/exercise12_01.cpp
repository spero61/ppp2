#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 600, 400, "My window"};
        win.wait_for_button();

        Graph_lib::Rectangle rect{Point{150, 150}, 200, 100};  // top left corner, width, height
        rect.set_color(Color::blue);
        win.attach(rect);

        Closed_polyline poly_rect;
        poly_rect.add(Point{50, 50});
        poly_rect.add(Point{150, 50});
        poly_rect.add(Point{150, 100});
        poly_rect.add(Point{50, 100});
        poly_rect.set_color(Color::red);
        win.attach(poly_rect);

        win.set_label("Ch12 Exercise01");
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