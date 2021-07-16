// Drill 15 : Function graphing drill with 'Shape's

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

double one(double x) {
    return 1;
}
double slope(double x) {
    return x / 2;
}
double square(double x) {
    return x * x;
}

double sloping_cos(double x) {
    return cos(x) + slope(x);
}

int main() {
    try {
        constexpr int xmax = 600;  // window size
        constexpr int ymax = 600;
        Simple_window win{Point{100, 100}, xmax, ymax, "Function graphs"};
        win.wait_for_button();

        constexpr int xlength = 400;  // length of axes
        constexpr int ylength = 400;
        const Point orig{300, 300};
        Axis x{Axis::x, Point{orig.x - xlength / 2, orig.y}, xlength, xlength / 20, "1 == 20 pixels"};
        x.label.move(-50, 0);
        Axis y{Axis::y, Point{orig.x, orig.y + ylength / 2}, ylength, ylength / 20, "1 == 20 pixels"};
        x.set_color(Color::red);
        y.set_color(Color::red);
        win.attach(x);
        win.attach(y);
        win.wait_for_button();

        constexpr int r_min = -10;  // range [-10:11)
        constexpr int r_max = 11;
        constexpr int n_points = 400;  // number of points used in range
        constexpr int x_scale = 30;    // scaling factors
        constexpr int y_scale = 30;
        // 1)
        Function s1{one, r_min, r_max, orig, n_points};
        win.attach(s1);
        win.wait_for_button();

        // 2)
        win.detach(s1);
        Function s2{one, r_min, r_max, orig, n_points, 20, 20};
        win.attach(s2);
        win.wait_for_button();

        // 4)
        Function s3{slope, r_min, r_max, orig, n_points, 20, 20};
        win.attach(s3);
        win.wait_for_button();

        // 5)
        Text ts3{Point{100, orig.y + orig.y / 2 - 70}, "x/2"};
        win.attach(ts3);
        win.wait_for_button();

        // 6)
        Function s4{square, r_min, r_max, orig, n_points, 20, 20};
        win.attach(s4);
        win.wait_for_button();

        // 7)
        Function s5{cos, r_min, r_max, orig, n_points, 20, 20};
        win.attach(s5);
        win.wait_for_button();

        // 8)
        s5.set_color(Color::blue);
        win.wait_for_button();

        // 9)
        Function s6{sloping_cos, r_min, r_max, orig, n_points, 20, 20};
        win.attach(s6);
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