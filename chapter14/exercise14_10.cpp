// Define a class Pseudo_window that looks as much like a Window as you can make it without heroic efforts.
// It should have rounded corners, a label, and control icons. Maybe you could add some fake “contents,” such as an image.
// It need not actually do anything. It is acceptable (and indeed recommended) to have it appear within a Simple_window.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// from exercise13_02.cpp
class Pseudo_window : public Shape {
   public:
    Pseudo_window(Point xy, int ww, int hh, string ll);
    void draw_lines() const override;

    int height() const { return h; }
    int width() const { return w; }

   private:
    int w;  // width
    int h;  // height
    string l;
};

Pseudo_window::Pseudo_window(Point xy, int ww, int hh, string ll) : w{ww}, h{hh}, l{ll} {
    if (h <= 0 || w <= 0)
        error("Bad Pseudo_window: non-positive side");
    add(xy);
}

void Pseudo_window::draw_lines() const {
    const int r{30};  // radius to draw rounded corners

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

    if (color().visibility()) {
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

        // borderline for label
        fl_line(point(0).x, point(0).y + 30, point(0).x + w, point(0).y + 30);

        // label
        fl_draw(l.c_str(), point(0).x + 20, point(0).y + 20);

        // Pseudo_window icons
        fl_line(point(0).x + w - 80, point(0).y + 15, point(0).x + w - 70, point(0).y + 15);
        fl_rect(point(0).x + w - 60, point(0).y + 10, 10, 10);
        fl_line(point(0).x + w - 40, point(0).y + 10, point(0).x + w - 30, point(0).y + 20);
        fl_line(point(0).x + w - 40, point(0).y + 20, point(0).x + w - 30, point(0).y + 10);

        // next_btn
        fl_rect(point(0).x + w - 60, point(0).y + 30, 60, 20);
        fl_draw("Next", point(0).x + w - 45, point(0).y + 45);
    }
}

int main() {
    try {
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 800, 600, "Pseudo_window in Simple_window");
        win.wait_for_button();

        Pseudo_window pseudo_win(tl, 500, 400, "Pseudo_window!");
        win.attach(pseudo_win);
        win.wait_for_button();

        Image lion(Point{200, 200}, "lion.jpg");
        win.attach(lion);
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
