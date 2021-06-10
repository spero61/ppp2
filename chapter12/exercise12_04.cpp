#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 600, 400, "adjust the window size then click next"};
        win.wait_for_button();

        // rect{top left corner, width, height}
        Graph_lib::Rectangle rect01{Point{100, 100}, 50, 50};
        rect01.set_color(Color::white);
        win.attach(rect01);

        Graph_lib::Rectangle rect02{Point{150, 100}, 50, 50};
        rect02.set_color(Color::red);
        win.attach(rect02);

        Graph_lib::Rectangle rect03{Point{200, 100}, 50, 50};
        rect03.set_color(Color::white);
        win.attach(rect03);

        Graph_lib::Rectangle rect04{Point{100, 150}, 50, 50};
        rect04.set_color(Color::red);
        win.attach(rect04);

        Graph_lib::Rectangle rect05{Point{150, 150}, 50, 50};
        rect05.set_color(Color::white);
        win.attach(rect05);

        Graph_lib::Rectangle rect06{Point{200, 150}, 50, 50};
        rect06.set_color(Color::red);
        win.attach(rect06);

        Graph_lib::Rectangle rect07{Point{100, 200}, 50, 50};
        rect07.set_color(Color::white);
        win.attach(rect07);

        Graph_lib::Rectangle rect08{Point{150, 200}, 50, 50};
        rect08.set_color(Color::red);
        win.attach(rect08);

        Graph_lib::Rectangle rect09{Point{200, 200}, 50, 50};
        rect09.set_color(Color::white);
        win.attach(rect09);

        win.set_label("Ch12 Exercise04");
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