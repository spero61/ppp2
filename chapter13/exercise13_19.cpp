// Star class
//
// Note that I have not learned how to implement inheritance in C++ yet.
// Though the author mentioned a few times the notion of inheritance during this chapter,
// he is going to teach in Chapter 14: Graphics Class Design.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

// Star class
struct Star : Shape {
    Star(Point cc, int dd, int num_of_points);
    void draw_lines() const;
    Point center() { return c; }
    Point calc_outer_point(Point a, Point b, Point c);

   private:
    Point c;  // center point of the Star
    int d;    // a side length of the inner Regular_polygon as well as outer equilateral triangle * np
    int np;   // number of points
};

Point Star::calc_outer_point(Point a, Point b, Point c) {
    /*  Point p1{ static_cast<int>((a.x + b.x + sqrt(3) * (b.y - a.y)) / 2), static_cast<int>((a.y + b.y - sqrt(3) * (b.x - a.x)) / 2) };
    Point p2{ static_cast<int>((a.x + b.x - sqrt(3) * (b.y - a.y)) / 2), static_cast<int>((a.y + b.y + sqrt(3) * (b.x - a.x)) / 2) };*/
    Point p1{static_cast<int>(a.x + b.x + sqrt(3) * (b.y - a.y) / 2), static_cast<int>(a.y + b.y - sqrt(3) * (b.x - a.x) / 2)};
    Point p2{static_cast<int>(a.x + b.x - sqrt(3) * (b.y - a.y) / 2), static_cast<int>(a.y + b.y + sqrt(3) * (b.x - a.x) / 2)};

    const double d1{sqrt(pow(p1.x - c.x, 2) + pow(p1.y - c.y, 2))};
    const double d2{sqrt(pow(p2.x - c.x, 2) + pow(p2.y - c.y, 2))};

    if (d1 > d2)
        return p1;
    else
        return p2;
}

Star::Star(Point cc, int dd, int num_of_points) : c{cc}, d{dd}, np{num_of_points} {
    if (np < 5)
        error("Bad Star: number of points should be greater than or equal to 5");
    if (d <= 0)
        error("Bad Star: d should be a positive integer");

    const double degrees{360.0 / np};  // degrees to draw inner Regular_polygon as well as to calc_outer_point

    // std::sin() https://en.cppreference.com/w/cpp/numeric/math/sin
    // std::cos() https://en.cppreference.com/w/cpp/numeric/math/cos

    // When i == 0 it adds starting point which is equal to Point{c.x, c.y - d} because sin(0) == 0 and cos(0) == 1
    for (int i = 0; i < np; ++i) {
        int x_move{static_cast<int>(d * sin(i * degrees * PI / 180.0))};  // range of degrees is from 0 to 359
        int y_move{static_cast<int>(-d * cos(i * degrees * PI / 180.0))};
        Point current_p{c.x + x_move, c.y + y_move};

        int x_next_move{static_cast<int>(d * sin((i + 1) * degrees * PI / 180.0))};
        int y_next_move{static_cast<int>(-d * cos((i + 1) * degrees * PI / 180.0))};
        Point next_p{c.x + x_next_move, c.y + y_next_move};

        Point outer_p = calc_outer_point(current_p, next_p, c);

        add(current_p);
        add(outer_p);
    }
    add(Point{c.x, c.y - d});  // add starting point again. Because this class utilizes Open_polygon class
}

void Star::draw_lines() const {
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
        Simple_window win{x, 1400, 900, "Star like polygon"};
        win.wait_for_button();

        const int size{70};       // size of Regular_polygons
        const int x_size{10};     // size of Regular_polygons is changing by this value along to x axis
        const int y_size{-15};    // size of Regular_polygons is changing by this value along to y axis
        const int x_coef{350};    // x interval between Regular_polygons
        const int y_coef{300};    // y interval between Regular_polygons
        int number_of_points{5};  // number of sides
        int multiplier{0};
        int idx{16 * multiplier};  // variable for Color(int c): https://www.fltk.org/doc-1.3/group__fl__attributes.html#ga497a7e059e9f5c89feed24ab0b1338f2

        const Point p{150, 150};
        const int x_num{4};  // number of Regular_polygons on the y axis
        const int y_num{3};  // number of Regular_polygons on the x axis

        Graph_lib::Vector_ref<Star> v_reg;

        for (int i = 0; i < y_num; ++i) {
            for (int j = 0; j < x_num; ++j) {
                v_reg.push_back(new Star{Point{p.x + x_coef * j, p.y + y_coef * i}, size + (x_size * j) + (y_size * i), number_of_points++});
                v_reg[v_reg.size() - 1].set_style(Line_style{Line_style::solid, 5});
                v_reg[v_reg.size() - 1].set_color(Color{idx - 5});
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
                v_reg[v_reg.size() - 1].set_style(Line_style{Line_style::solid, 5});
                v_reg[i].set_color(Color{idx - 5});
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