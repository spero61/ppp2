// Tiling with regular_hexagons of a few different colors
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Regular_hexagon : Shape {
    Regular_hexagon(Point c, int dd);
    void draw_lines() const;
    Point center() { return c; }

   private:
    int d;    // a distance from the center which is radius of the circumscribed circle.
    Point c;  // center point
};

Regular_hexagon::Regular_hexagon(Point cc, int dd) : c{cc}, d{dd} {
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
        Simple_window win{x, 1200, 800, "Tiling with regular_hexagons of a few different colors"};
        win.wait_for_button();

        const int size{20};                                     // d
        const int x_below{static_cast<int>(size * (3.0 / 2))};  // HUOM! int / int is equal to int. (e.g., 3/2 equal to 1 not 1.5)
        const int y_below{static_cast<int>(size * sqrt(3) / 2)};

        const int x_axis{21};
        const int y_axis{48};

        Graph_lib::Vector_ref<Regular_hexagon> v_hex;
        const Point origin{0, 0};

        vector<int> v_color_int;
        for (int i = 1; i <= 9; ++i) {
            v_color_int.push_back(16 * 10 + i * 5);
        }

        int idx{1};
        for (int i = 0; i < y_axis; ++i) {
            for (int j = 0; j < x_axis; ++j) {
                if (i == 0)
                    v_hex.push_back(new Regular_hexagon{Point{origin.x + size * 3 * j, origin.y}, size});
                else if (i % 2 == 1)
                    v_hex.push_back(new Regular_hexagon{Point{v_hex[v_hex.size() - x_axis].center().x - x_below, origin.y + y_below * i}, size});
                else  // else if (i % 2 == 0)
                    v_hex.push_back(new Regular_hexagon{Point{v_hex[v_hex.size() - x_axis].center().x + x_below, origin.y + y_below * i}, size});
                v_hex[v_hex.size() - 1].set_color(Color{Color::dark_blue});
                v_hex[v_hex.size() - 1].set_fill_color(Color{v_color_int[(idx++) % v_color_int.size()]});
                win.attach(v_hex[v_hex.size() - 1]);
            }
            // win.wait_for_button(); // to draw line by line
        }
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