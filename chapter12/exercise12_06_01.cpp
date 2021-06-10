// case1: When a Shape does not fit inside its window

// Parts of the Shape that does not fit in the window are simple not represented.
// What would have appeared outside the window is clippled away,
// however, if we increase the side of the window, we can see the Shape would have represented.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();

        Graph_lib::Rectangle rect{Point{300, 300}, 800, 600};  // top left corner, width, height
        rect.set_fill_color(Color::dark_cyan);
        win.attach(rect);

        ostringstream oss;
        oss << "screen size: " << x_max() << "*" << y_max()
            << "; window size: " << win.x_max() << "*" << win.y_max();
        Text sizes{Point{30, 30}, oss.str()};
        sizes.set_font(Font::helvetica_bold);
        sizes.set_font_size(20);
        win.attach(sizes);

        win.set_label("Ch12 Exercise06_case01");
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