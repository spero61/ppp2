// Regular_hexagon class
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Regular_hexagon : Shape {
    Regular_hexagon(Point c, int dd);  // Point c: center
    void draw_lines() const;

   private:
    int d;  // a distance from the center which is radius of the circumscribed circle.
};

Regular_hexagon::Regular_hexagon(Point c, int dd) : d{dd} {
    if (d <= 0)
        error("Bad Regular_hexagon: d should have positive value");
    const int x_coef{static_cast<int>(d / 2)};
    const int y_coef{static_cast<int>(d * sqrt(3) / 2)};
    add(Point{c.x - x_coef, c.y - y_coef});
    add(Point{c.x + x_coef, c.y - y_coef});
    add(Point{c.x + d, c.y});
    add(Point{c.x + x_coef, c.y + y_coef});
    add(Point{c.x - x_coef, c.y + y_coef});
    add(Point{c.x - d, c.y});
    add(Point{c.x - x_coef, c.y - y_coef});
}

void Regular_hexagon::draw_lines() const {
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i) {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility())
        Shape::draw_lines();
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Regular_hexagon"};
        win.wait_for_button();

        Regular_hexagon reg_hex01{Point{130, 100}, 80};
        reg_hex01.set_style(Line_style{Line_style::solid, 2});
        reg_hex01.set_color(Color::red);
        win.attach(reg_hex01);
        win.wait_for_button();

        Regular_hexagon reg_hex02{Point{330, 250}, 120};
        reg_hex02.set_style(Line_style{Line_style::solid, 2});
        reg_hex02.set_color(Color::green);
        win.attach(reg_hex02);
        win.wait_for_button();

        Regular_hexagon reg_hex03{Point{480, 80}, 50};
        reg_hex03.set_style(Line_style{Line_style::solid, 2});
        reg_hex03.set_color(Color::blue);
        win.attach(reg_hex03);
        win.wait_for_button();

        reg_hex01.set_fill_color(Color::red);
        reg_hex02.set_fill_color(Color::green);
        reg_hex03.set_fill_color(Color::blue);
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