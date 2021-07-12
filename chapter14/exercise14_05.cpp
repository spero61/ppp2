// Define a Striped_rectangle where instead of fill,
// the rectangle is “filled” by drawing one-pixel-wide horizontal lines
// across the inside of the rectangle (say, draw every second line like that).
// You may have to play with the width of lines and the line spacing to get a pattern you like.

// Note: that I commented out of a custom pattern stripe in the function implementation

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Striped_rectangle : public Rectangle {
   public:
    using Rectangle::Rectangle;
    void draw_lines() const override;
};

void Striped_rectangle::draw_lines() const {
    const int w{width()};
    const int h{height()};

    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());

        for (int i = 0; i < w - 1; i += 2) {
            fl_line(point(0).x + i + 1, point(0).y + 1, point(0).x + i + 1, point(0).y + h - 1);
        }

        //// custom pattern
        //for (int i = 0; i < w-1; i += 8) {
        //    fl_line(point(0).x + i+1, point(0).y+1, point(0).x + i+1, point(0). y + h-1);
        //    fl_line(point(0).x + i+2, point(0).y+1, point(0).x + i+2, point(0).y + h-1);
        //    fl_line(point(0).x + i+3, point(0).y+1, point(0).x + i+3, point(0).y + h-1);
        //    fl_line(point(0).x + i+7, point(0).y+1, point(0).x + i+7, point(0).y + h-1);
        //}

        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {  // edge on top of fill
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, w, h);
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Striped_rectangle"};
        win.wait_for_button();

        const int width{600};
        const int height{400};

        Striped_rectangle rect = {x, width, height};
        win.attach(rect);
        win.wait_for_button();

        rect.set_fill_color(Color::dark_cyan);
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