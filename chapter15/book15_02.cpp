// Chapter 15 textbook examples until 15.5: Approximation

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// change return type the fac() from int to double
// can fix the problem mentioned in the textbook
int fac(int n) {  // factorial(n); n! : iterative (see exercise15_01.cpp for recursive version)
    int r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

double term(double x, int n) {
    return pow(x, n) / fac(n);  // nth term of series
}

double expe(double x, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += term(x, i);
    }
    return sum;
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
        constexpr int x_scale = 30;    // scaling factors
        constexpr int y_scale = 30;

        Simple_window win{Point{100, 100}, xmax, ymax, "Approximation"};
        win.wait_for_button();

        Function real_exp{exp, r_min, r_max, orig, 200, x_scale, y_scale};
        real_exp.set_color(Color::blue);
        win.attach(real_exp);

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
        win.wait_for_button();

        // HUOM!
        // unfortunately the code shown below (from the textbook) produces compile error!
        // so, as for now I just had to use global variable instead of capturing a local variable n in lambda function.
        // (source : [https://groups.google.com/g/ppp-public/c/WBHYlwS6m3g](https://groups.google.com/g/ppp-public/c/WBHYlwS6m3g))
        // This is because the lambda expression can be converted to address of function only if it doesn't have capture arguments.
        // And probably it is a editorial mistake taken place when 1st edition of the book is revised to 2nd edition... I assume.

        //for (int n = 0; n < 50; ++n) {
        //    ostringstream ss;
        //    ss << "exp approximation; n==" << n;
        //    win.set_label(ss.str());
        //    // get next approximation:
        //    Function e { [n](double x) { return expe(x, n); }, r_min, r_max, orig, 200, x_scale, y_scale };
        //    win.attach(e);
        //    win.wait_for_button();
        //    win.detach(e);
        //}

        for (int n = 0; n < 50; ++n) {
            ostringstream ss;
            ss << "exp approximation; n==" << n;
            win.set_label(ss.str());
            // get next approximation:
            global_n = n;  // set global variable is equivalent to n (local variable)
            Function e{[](double x) { return expe(x, global_n); }, r_min, r_max, orig, 200, x_scale, y_scale};
            e.set_color(Color::green);
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
