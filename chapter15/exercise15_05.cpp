// "Animate" the Leibniz's series and converges to pi/4

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.1415926535897932384626433};

double term(double x, int n) {  // n th term of the leibniz_series
    if (n == 1)
        return 1;
    else if (n % 2 == 0)
        return -1.0 / (2 * n - 1);
    return 1.0 / (2 * n - 1);
}

double leibniz_series(double x, int n) {
    double sum{0};
    for (int i = 1; i <= n; ++i) {
        sum += term(x, i);
    }
    return sum;
}

double pi_div_four(double x) {
    return PI / 4;
}

// global variable
int global_n{0};

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
        constexpr int x_scale = 90;    // scaling factors
        constexpr int y_scale = 90;

        Simple_window win{Point{100, 100}, xmax, ymax, "Leibniz's series and PI/4"};
        win.wait_for_button();

        constexpr int xlength = xmax - 40;  // make the axis a bit smaller than the window
        constexpr int ylength = ymax - 40;
        Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale, "one notch == 1"};
        Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / y_scale, "one notch == 1"};
        x.set_color(Color{180});
        y.set_color(Color{180});
        win.attach(x);
        win.attach(y);
        x.label.move(-160, 0);
        x.notches.set_color(Color{178});
        y.notches.set_color(Color{178});
        win.wait_for_button();

        Function real_pi_div_four{pi_div_four, r_min, r_max, orig, 200, x_scale, y_scale};
        real_pi_div_four.set_color(Color{242});
        win.attach(real_pi_div_four);
        win.set_label("PI/4 Graph");
        win.wait_for_button();

        for (int n = 1; n <= 50; ++n) {
            ostringstream ss;
            ss << "leibniz_series when n==" << n;
            win.set_label(ss.str());
            // get next approximation:
            global_n = n;  // set global variable is equivalent to n (local variable)
            Function e{[](double x) { return leibniz_series(x, global_n); }, r_min, r_max, orig, 200, x_scale, y_scale};
            e.set_color(Color{87});
            win.attach(e);
            win.wait_for_button();
            win.detach(e);
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
