// Arrow class

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

struct Arrow : Shape {
    Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd);
    void draw_lines() const;

   private:
    int d;        // size of an arrow
    bool p1_arw;  // is arrow at p1
    bool p2_arw;  // is arrow at p2
};

Arrow::Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd) : p1_arw{p1_arrow}, p2_arw{p2_arrow}, d{dd} {
    if (d <= 0)
        error("Bad Arrow: size of a triangle should have positive value");
    add(p1);
    add(p2);
}

void Arrow::draw_lines() const {
    const double arrow_angle{PI / 4.0};  // 45 degrees

    if (color().visibility()) {
        fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

        int dy{point(1).y - point(0).y};
        int dx{point(1).x - point(0).x};
        double angle{atan2(dy, dx)};  // https://en.cppreference.com/w/c/numeric/math/atan2

        // fl_line: https://www.fltk.org/doc-1.3/group__fl__drawings.html#gaecc374f163a97ef67c4e58be11c47047
        if (p1_arw) {
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle + arrow_angle), point(0).y + d * sin(angle + arrow_angle));
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle - arrow_angle), point(0).y + d * sin(angle - arrow_angle));
        }
        if (p2_arw) {
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle + arrow_angle), point(1).y - d * sin(angle + arrow_angle));
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle - arrow_angle), point(1).y - d * sin(angle - arrow_angle));
        }
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Arrows"};
        win.wait_for_button();

        // Arrow arrow { Point p1, Point p2, bool p1_arrow, bool p2_arrow, int size_of_an_arrow(dd)};
        Arrow arrow01{Point{110, 100}, Point{200, 100}, true, false, 25};
        arrow01.set_style(Line_style{Line_style::solid, 3});
        arrow01.set_color(Color::cyan);
        win.attach(arrow01);
        win.wait_for_button();

        Arrow arrow02{Point{120, 170}, Point{300, 200}, false, true, 35};
        arrow02.set_style(Line_style{Line_style::solid, 3});
        arrow02.set_color(Color::magenta);
        win.attach(arrow02);
        win.wait_for_button();

        Arrow arrow03{Point{400, 100}, Point{480, 300}, true, true, 40};
        arrow03.set_style(Line_style{Line_style::solid, 3});
        arrow03.set_color(Color::yellow);
        win.attach(arrow03);
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
