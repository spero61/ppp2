// Marks on the Ellipse
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Marks on the Ellipse"};
        win.wait_for_button();
        Point p{win.x_max() / 2, (win.y_max() / 2) + 50};

        const int horizontal{150};  // width of an Ellipse is horizontal * 2
        const int vertical{100};    // height of an Ellipse is vertical * 2
        Graph_lib::Ellipse e{p, horizontal, vertical};
        e.set_color(Color::dark_cyan);
        e.set_style(Line_style{Line_style::solid, 3});
        win.attach(e);
        //win.wait_for_button();
        // e01.set_fill_color(Color::dark_cyan);

        // Axis::x means horizontal starting at Point{p.x - horizontal, p.y}
        // 400 pixels long 40 “notches” label the axis "x axis"
        Axis xa{Axis::x, Point{p.x - horizontal, p.y}, 400, 40, "x axis"};

        xa.set_color(Color::dark_blue);
        xa.label.set_color(Color::dark_blue);
        win.attach(xa);

        Axis ya{Axis::y, Point{p.x, p.y + vertical}, 300, 30, "y axis"};
        ya.set_color(Color::dark_magenta);        // choose a color
        ya.label.set_color(Color::dark_magenta);  // choose a color for the text
        win.attach(ya);
        win.wait_for_button();

        Point p01{p.x + 50, p.y - 70};
        Mark focus01(p01, 'o');
        focus01.set_color(Color::dark_red);
        win.attach(focus01);
        win.wait_for_button();

        Point p02{p.x - 30, p.y + 50};
        Mark focus02(p02, 'o');
        focus02.set_color(Color::dark_red);
        win.attach(focus02);
        win.wait_for_button();

        const double degrees{123};
        const double trigo_arg{degrees * PI / 180.0};
        Point p_e{e.center().x + static_cast<int>(e.major() * sin(trigo_arg)), e.center().y - static_cast<int>(e.minor() * cos(trigo_arg))};
        Mark focus03(p_e, 'o');
        focus03.set_color(Color::dark_red);
        win.attach(focus03);
        win.wait_for_button();

        Lines ln;
        ln.add(p01, p_e);
        ln.add(p02, p_e);
        ln.set_color(Color::yellow);
        win.attach(ln);
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
