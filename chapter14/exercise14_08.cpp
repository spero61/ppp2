// Define a class Octagon to be a regular octagon.
// Write a test that exercises all of its functions
// (as defined by you or inherited from Shape)

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

// Regular_polygon from exercise13_10.cpp
struct Regular_polygon : Shape {
    Regular_polygon() {}
    Regular_polygon(Point cc, int dd, int ss);  // for the implementation detail see exercise13_10.cpp
    void draw_lines() const;
    Point center() { return c; }
    void set_side(int ss) { s = ss; }

   protected:
    Point c;  // center point of the Regular_polygon.
    int d;    // A distance from the center which is radius of the circumscribed circle.
    int s;    // number of side that a Regular_polygon has. (s => 3)
};

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

// regular octagon class
class Octagon : public Regular_polygon {
   public:
    using Regular_polygon::Regular_polygon;
    Octagon(Point cc, int dd);

   private:
    Point c;
    int d;
};

Octagon::Octagon(Point cc, int dd) : c{cc}, d{dd} {
    if (d <= 0)
        error("Bad Octagon: distance should be positive");

    set_side(8);

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
            error("error(Octagon constructor): This should not be reached");
    }

    add(Point{c.x, c.y - d});  // add starting point again. Because this class utilizes Open_polygon class
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Regular octagons"};
        win.wait_for_button();

        Octagon octa01{Point{150, 150}, 100};
        win.attach(octa01);
        win.wait_for_button();

        octa01.set_fill_color(Color::dark_magenta);
        win.wait_for_button();

        octa01.move(75, 80);
        octa01.set_style(Line_style(Line_style::dash, 7));
        octa01.set_fill_color(Color::yellow);
        win.wait_for_button();

        Octagon octa02{Point{500, 300}, 120};
        octa02.set_style(Line_style(Line_style::dashdotdot, 5));
        octa02.set_color(Color::dark_blue);
        octa02.set_fill_color(Color::cyan);
        win.attach(octa02);
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