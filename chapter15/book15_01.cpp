// Chapter 15 textbook examples until 15.4

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

double one(double) {
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
        constexpr int ymax = 400;
        constexpr int x_orig = xmax / 2;  // position of (0,0) is center of window
        constexpr int y_orig = ymax / 2;
        const Point orig{x_orig, y_orig};

        constexpr int r_min = -10;  // range [-10:11)
        constexpr int r_max = 11;
        constexpr int n_points = 400;  // number of points used in range
        constexpr int x_scale = 30;    // scaling factors
        constexpr int y_scale = 30;

        Simple_window win{Point{100, 100}, xmax, ymax, "Function graphing"};
        win.wait_for_button();

        Function s{one, r_min, r_max, orig, n_points, x_scale, y_scale};
        Function s2{slope, r_min, r_max, orig, n_points, x_scale, y_scale};
        Function s3{square, r_min, r_max, orig, n_points, x_scale, y_scale};
        Function s4{cos, r_min, r_max, orig, n_points, x_scale, y_scale};
        //Function s5{ sloping_cos, r_min, r_max, orig, n_points, x_scale, y_scale };
        Function s5{[](double x) { return cos(x) + slope(x); }, r_min, r_max, orig, n_points, x_scale, y_scale};  // lambda expression !!
        s5.set_color(Color::green);
        win.attach(s);
        win.wait_for_button();
        win.attach(s2);
        win.wait_for_button();
        win.attach(s3);
        win.wait_for_button();
        win.attach(s4);
        win.wait_for_button();
        win.attach(s5);
        win.wait_for_button();

        Function f1{log, 0.000001, r_max, orig, n_points / 2, x_scale, y_scale};  // log() logarithm, base e
        f1.set_color(Color::cyan);
        Function f2{sin, r_min, r_max, orig, n_points / 2, x_scale, y_scale};  // sin()
        f2.set_color(Color::white);
        Function f3{cos, r_min, r_max, orig, n_points / 2, x_scale, y_scale};  // cos()
        Function f4{exp, r_min, r_max, orig, n_points / 2, x_scale, y_scale};  // exp() exponential e^x
        f4.set_color(Color::magenta);

        win.attach(f1);
        win.wait_for_button();
        win.attach(f2);
        win.wait_for_button();
        win.attach(f3);
        win.wait_for_button();
        win.attach(f4);
        win.wait_for_button();

        Text ts{Point{100, y_orig - 40}, "one"};
        Text ts2{Point{100, y_orig + y_orig / 2 - 20}, "x/2"};
        Text ts3{Point{x_orig - 100, 20}, "x*x"};
        win.attach(ts);
        win.attach(ts2);
        win.attach(ts3);

        constexpr int xlength = xmax - 40;  // make the axis a bit smaller than the window
        constexpr int ylength = ymax - 40;
        Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale, "one notch == 1"};
        Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / y_scale, "one notch == 1"};
        x.set_color(Color::red);
        y.set_color(Color::red);
        win.attach(x);
        win.attach(y);
        x.label.move(-160, 0);
        x.notches.set_color(Color::dark_red);
        win.set_label("Function graphing: more functions");
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