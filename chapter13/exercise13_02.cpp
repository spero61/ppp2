// Box class
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Box : Shape {
    Box(Point xy, int ww, int hh, int rr);
    void draw_lines() const;

    int height() const { return h; }
    int width() const { return w; }
    int radius() const { return r; }

   private:
    int h;  // height
    int w;  // width
    int r;  // radius
};

Box::Box(Point xy, int ww, int hh, int rr) : w{ww}, h{hh}, r{rr} {
    if (h <= 0 || w <= 0)
        error("Bad Box: non-positive side");
    if (r <= 0)
        error("Bad Box: radius should have positive value");
    add(xy);
}

void Box::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y + r, w, h - r * 2);                              // horizontal
        fl_rectf(point(0).x + r, point(0).y, w - r * 2, h);                              // vertical
        fl_pie(point(0).x, point(0).y, r + r, r + r, 90, 180);                           // top-left corner
        fl_pie(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);                 // top-right corner
        fl_pie(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);              // bottom-left corner
        fl_pie(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);  // bottom-right corner
        fl_color(color().as_int());                                                      // reset color
    }

    if (color().visibility()) {  // edge on top of fill
        fl_color(color().as_int());
        // four sides
        fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);          // side: top
        fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);  // side: down
        fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);          // side: left
        fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);  // side: right
        // four arcs
        fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);                           // top-left corner
        fl_arc(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);                 // top-right corner
        fl_arc(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);              // bottom-left corner
        fl_arc(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);  // bottom-right corner
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "A box with rounded corners"};
        win.wait_for_button();

        Box box01{Point{50, 50}, 250, 100, 40};
        box01.set_style(Line_style{Line_style::solid, 3});
        box01.set_color(Color::cyan);
        win.attach(box01);
        win.wait_for_button();

        Box box02{Point{325, 100}, 180, 250, 80};
        box02.set_style(Line_style{Line_style::solid, 3});
        box02.set_color(Color::magenta);
        win.attach(box02);
        win.wait_for_button();

        box01.set_fill_color(Color::cyan);
        box02.set_fill_color(Color::magenta);
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
