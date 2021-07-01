// Arc class
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Ellipse_Arc : Shape {
    Ellipse_Arc(Point p, int ww, int hh, int start, int end)
        : w{ww}, h{hh}, a{start}, b{end} {
        add(Point{p.x - ww, p.y - hh});
    }

    void draw_lines() const;

    Point center() const { return {point(0).x + w, point(0).y + h}; }
    Point focus1() const { return {center().x + int(sqrt(double(w * w - h * h))), center().y}; }
    Point focus2() const { return {center().x - int(sqrt(double(w * w - h * h))), center().y}; }

    void set_major(int ww) { w = ww; }
    int major() const { return w; }
    void set_minor(int hh) { h = hh; }
    int minor() const { return h; }

   private:
    int w;  // the distance from the center to a point on the x axis
    int h;  // the distance from the center to a point on the y axis
    int a;  // start point between 0 and 360
    int b;  // end point between 0 and 360
};

void Ellipse_Arc::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, a, b);
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, w + w, h + h, a, b);
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Arc"};
        win.wait_for_button();

        Ellipse_Arc arc{Point{300, 200}, 150, 100, 90, 360};
        arc.set_color(Color::magenta);
        arc.set_style(Line_style{Line_style::solid, 3});
        win.attach(arc);
        win.wait_for_button();

        arc.set_fill_color(Color::magenta);
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
