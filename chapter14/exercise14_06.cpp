// Define a Striped_circle using the technique from Striped_rectangle.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Striped_circle : public Circle {
   public:
    using Circle::Circle;
    void draw_lines() const override;
};

void Striped_circle::draw_lines() const {
    const int r{radius()};

    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        // fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);

        for (int i = point(0).x + 1; i < point(0).x + r + r - 1; i += 2) {
            const int tmp{static_cast<int>(sqrt(r * r - pow(i - (point(0).x + r), 2)))};  // from the equation of a circle
            fl_line(i, tmp + point(0).y + r, i, -tmp + point(0).y + r);
        }

        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Striped_circle"};
        win.wait_for_button();

        const int radius{200};

        Striped_circle sc = {Point{win.x_max() / 2, win.y_max() / 2}, radius};
        win.attach(sc);
        win.wait_for_button();

        sc.set_fill_color(Color::dark_cyan);
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