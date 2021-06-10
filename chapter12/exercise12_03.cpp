#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 600, 400, "adjust the window size then click next"};
        win.wait_for_button();

        Open_polyline text_one;
        text_one.add(Point(100, 100));
        text_one.add(Point(150, 175));
        text_one.add(Point(200, 100));
        text_one.add(Point(150, 175));
        text_one.add(Point(150, 250));
        text_one.set_style(Line_style(Line_style::solid, 5));
        text_one.set_color(Color::dark_blue);
        win.attach(text_one);

        Open_polyline text_two;
        text_two.add(Point(315, 125));
        text_two.add(Point(275, 100));
        text_two.add(Point(235, 125));
        text_two.add(Point(315, 225));
        text_two.add(Point(275, 250));
        text_two.add(Point(235, 225));
        text_two.set_style(Line_style(Line_style::solid, 5));
        text_two.set_color(Color::dark_cyan);
        win.attach(text_two);

        win.set_label("Ch12 Exercise03");
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