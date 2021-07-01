// Regular_polygon class
// Since Point only takes integers as arguments, some lines or color_fill might not be looking smooth.
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

struct Regular_polygon : Shape {
    Regular_polygon(Point cc, int dd, int ss);
    void draw_lines() const;
    Point center() { return c; }

   private:
    Point c;  // center point of the Regular_polygon.
    int d;    // A distance from the center which is radius of the circumscribed circle.
    int s;    // number of side that a Regular_polygon has. (s => 3)
};

Regular_polygon::Regular_polygon(Point cc, int dd, int ss) : c{cc}, d{dd}, s{ss} {
    if (d <= 0)
        error("Bad Regular_polygon: distance should be positive");
    if (s <= 2)
        error("Bad Regular_polygon: number of sides should be greater than 2");

    const double x{360.0 / s};  // degrees for tmp_x. Then add Points to draw a Regular_polygon

    // std::sin() https://en.cppreference.com/w/cpp/numeric/math/sin
    // std::cos() https://en.cppreference.com/w/cpp/numeric/math/cos

    // Note that FLTK coordinate's (0,0) is located at the Top-left corner.
    // quadrant 1,2,3, and 4 is based on Point c that is Point{c.x, c.y}
    for (int i = 0; i < s; ++i) {
        double tmp_x{i * x};
        if (tmp_x == 0 || tmp_x == 360)    // north
            add(Point{c.x, c.y - d});      // starting point
        else if (tmp_x > 0 && tmp_x < 90)  // quadrant 1
            add(Point{c.x + static_cast<int>(d * sin(tmp_x * PI / 180.0)), c.y - static_cast<int>(d * cos(tmp_x * PI / 180.0))});
        else if (tmp_x == 90)  // east
            add(Point{c.x + d, c.y});
        else if (tmp_x > 90 && tmp_x < 180)  // quadrant 4
            add(Point{c.x + static_cast<int>(d * cos((tmp_x - 90) * PI / 180.0)), c.y + static_cast<int>(d * sin((tmp_x - 90) * PI / 180.0))});
        else if (tmp_x == 180)  // south
            add(Point{c.x, c.y + d});
        else if (tmp_x > 180 && tmp_x < 270)  // quadrant 3
            add(Point{c.x - static_cast<int>(d * sin((tmp_x - 180) * PI / 180.0)), c.y + static_cast<int>(d * cos((tmp_x - 180) * PI / 180.0))});
        else if (tmp_x == 270)  // west
            add(Point{c.x - d, c.y});
        else if (tmp_x > 270 && tmp_x < 360)  // quadrant 2
            add(Point{c.x - static_cast<int>(d * cos((tmp_x - 270) * PI / 180.0)), c.y - static_cast<int>(d * sin((tmp_x - 270) * PI / 180.0))});
        else
            error("error(Regular_polygon constructor): This should not be reached");
    }

    add(Point{c.x, c.y - d});  // add starting point again. Because this class utilizes Open_polygon class
}

void Regular_polygon::draw_lines() const {
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
        Simple_window win{x, 1400, 900, "Regular_polygon"};
        win.wait_for_button();

        const int size{100};    // size of Regular_polygons
        const int x_size{10};   // size of Regular_polygons is changing by this value along to x axis
        const int y_size{-15};  // size of Regular_polygons is changing by this value along to y axis
        const int x_coef{350};  // x interval between Regular_polygons
        const int y_coef{300};  // y interval between Regular_polygons
        int polygon{3};         // number of sides
        int multiplier{0};
        int idx{16 * multiplier};  // variable for Color(int c): https://www.fltk.org/doc-1.3/group__fl__attributes.html#ga497a7e059e9f5c89feed24ab0b1338f2

        const Point p{150, 150};
        const int x_num{4};  // number of Regular_polygons on the y axis
        const int y_num{3};  // number of Regular_polygons on the x axis

        Graph_lib::Vector_ref<Regular_polygon> v_reg;

        for (int i = 0; i < y_num; ++i) {
            for (int j = 0; j < x_num; ++j) {
                v_reg.push_back(new Regular_polygon{Point{p.x + x_coef * j, p.y + y_coef * i}, size + (x_size * j) + (y_size * i), polygon++});
                v_reg[v_reg.size() - 1].set_color(Color{idx});
                v_reg[v_reg.size() - 1].set_fill_color(Color{idx++});
                win.attach(v_reg[v_reg.size() - 1]);
                // win.wait_for_button();
            }
        }
        win.wait_for_button();

        const int num_of_times{15};  // number of times changing(= overwriting) color of Regular_polygons
        for (int n = 0; n < num_of_times; ++n) {
            idx = 16 * multiplier++;
            for (int i = 0; i < v_reg.size(); ++i) {
                v_reg[i].set_color(Color{idx});
                v_reg[i].set_fill_color(Color{idx++});
            }
            win.wait_for_button();
        }

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}