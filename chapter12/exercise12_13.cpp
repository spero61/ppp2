#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();

        win.set_label("Ch12 Exercise13");

        const Point center(win.x_max() / 2, win.y_max() / 2);
        constexpr double N{200};
        constexpr double a{N};
        constexpr double b{N};

        const double m_n{0.75};
        win.set_label("Ch12 Exercise13 (m = n = 0.75)");

        Graph_lib::Open_polyline quadrant_01;  //
        quadrant_01.set_color(Color::red);
        quadrant_01.set_style(Line_style(Line_style::solid, 3));
        Graph_lib::Open_polyline quadrant_02;  //
        quadrant_02.set_color(Color::cyan);
        quadrant_02.set_style(Line_style(Line_style::solid, 3));
        Graph_lib::Open_polyline quadrant_03;  //
        quadrant_03.set_color(Color::magenta);
        quadrant_03.set_style(Line_style(Line_style::solid, 3));
        Graph_lib::Open_polyline quadrant_04;  //
        quadrant_04.set_color(Color::green);
        quadrant_04.set_style(Line_style(Line_style::solid, 3));

        // quadrant_01
        for (int x = N; x > 0; x--) {
            int y = -b * pow(1 - pow(abs(x / a), m_n), 1.0 / m_n);
            quadrant_01.add(Point{x + center.x, y + center.y});
        }
        win.attach(quadrant_01);

        // quadrant_02
        for (int x = 0; x < N; x++) {
            int y = b * pow(1 - pow(abs(x / a), m_n), 1.0 / m_n);
            quadrant_02.add(Point{x + center.x, y + center.y});
        }
        win.attach(quadrant_02);

        // quadrant_03
        for (int x = -N; x < 0; x++) {
            int y = b * pow(1 - pow(abs(x / a), m_n), 1.0 / m_n);
            quadrant_03.add(Point{x + center.x, y + center.y});
        }
        win.attach(quadrant_03);

        // quadrant_04
        for (int x = 0; x > -N; x--) {
            int y = -b * pow(1 - pow(abs(x / a), m_n), 1.0 / m_n);
            quadrant_04.add(Point{x + center.x, y + center.y});
        }
        win.attach(quadrant_04);

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