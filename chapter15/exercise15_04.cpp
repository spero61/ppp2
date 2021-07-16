// Draw some graphs

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

double sin_plus_cos(double x) {
    return sin(x) + cos(x);
}

double sinsin_plus_coscos(double x) {
    return sin(x) * sin(x) + cos(x) * cos(x);
}

int main() {
    try {
        constexpr int xmax = 600;  // window size
        constexpr int ymax = 600;
        Simple_window win{Point{100, 100}, xmax, ymax, "Trigonometric function graphs"};
        win.wait_for_button();

        constexpr int xlength = 400;  // length of axes
        constexpr int ylength = 400;
        const Point orig{300, 300};
        Axis x{Axis::x, Point{orig.x - xlength / 2, orig.y}, xlength, xlength / 20, "1 == 20 pixels"};
        x.label.move(-120, 0);
        Axis y{Axis::y, Point{orig.x, orig.y + ylength / 2}, ylength, ylength / 20, "1 == 20 pixels"};
        x.set_color(Color::dark_red);
        y.set_color(Color::dark_red);
        win.attach(x);
        win.attach(y);
        win.wait_for_button();

        constexpr int r_min = -10;  // range [-10:11)
        constexpr int r_max = 11;
        constexpr int n_points = 400;  // number of points used in range
        constexpr int x_scale = 30;    // scaling factors
        constexpr int y_scale = 30;

        Function f1{sin, r_min, r_max, orig, n_points, 20, 20};
        Function f2{cos, r_min, r_max, orig, n_points, 20, 20};
        Function f3{sin_plus_cos, r_min, r_max, orig, n_points, 20, 20};
        Function f4{sinsin_plus_coscos, r_min, r_max, orig, n_points, 20, 20};

        Point lp{50, 50};  // label base point
        Text tf1{lp, "y = sin(x)"};
        Text tf2{Point{lp.x, lp.y + 40 * 1}, "y = cos(x)"};
        Text tf3{Point{lp.x, lp.y + 40 * 2}, "y = sin(x) + cos(x)"};
        Text tf4{Point{lp.x, lp.y + 40 * 3}, "y = sin(x)*sin(x) + cos(x)*cos(x)"};

        constexpr int f1_color{87};
        constexpr int f2_color{130};
        constexpr int f3_color{181};
        constexpr int f4_color{117};

        f1.set_color(Color{f1_color});
        tf1.set_color(Color{f1_color});
        f2.set_color(Color{f2_color});
        tf2.set_color(Color{f2_color});
        f3.set_color(Color{f3_color});
        tf3.set_color(Color{f3_color});
        f4.set_color(Color{f4_color});
        tf4.set_color(Color{f4_color});

        win.attach(f1);
        win.attach(tf1);
        win.wait_for_button();

        win.attach(f2);
        win.attach(tf2);
        win.wait_for_button();

        win.attach(f3);
        win.attach(tf3);
        win.wait_for_button();

        win.attach(f4);
        win.attach(tf4);
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