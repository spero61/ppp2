// Chapter 15 textbook examples until 15.6: Graphing data 1960 ~ 2040

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Distribution {
    int year, young, middle, old;
};
istream& operator>>(istream& is, Distribution& d)
// assume format: ( year : young middle old )
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Distribution dd;
    if (is >> ch1 >> dd.year >> ch2 >> dd.young >> dd.middle >> dd.old >> ch3) {
        if (ch1 != '(' || ch2 != ':' || ch3 != ')') {
            is.clear(ios_base::failbit);
            return is;
        }
    } else
        return is;
    d = dd;
    return is;
}

class Scale {   // data value to coordinate conversion
    int cbase;  // coordinate base
    int vbase;  // base of values
    double scale;

   public:
    Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} {}
    int operator()(int v) const {  // see 21.4 Function objects
        return cbase + (v - vbase) * scale;
    }
};

int main() {
    try {
        constexpr int xmax = 600;  // window size
        constexpr int ymax = 400;

        constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
        constexpr int yoffset = 60;   // distance from bottom of window to x axis

        constexpr int xspace = 40;  // space beyond axis
        constexpr int yspace = 40;

        constexpr int xlength = xmax - xoffset - xspace;  // length of axes
        constexpr int ylength = ymax - yoffset - yspace;

        constexpr int base_year = 1960;
        constexpr int end_year = 2040;

        constexpr double xscale = double(xlength) / (end_year - base_year);
        constexpr double yscale = double(ylength) / 100;

        Scale xs{xoffset, base_year, xscale};
        Scale ys{ymax - yoffset, 0, -yscale};

        Simple_window win{Point{100, 100}, xmax, ymax, "Aging Japan"};
        win.wait_for_button();

        // Adjacent string literals are concatenated by the compiler.
        // This can be a useful "trick" for laying out long string literals to make our code more readable.
        Axis x{Axis::x, Point{xoffset, ymax - yoffset}, xlength, (end_year - base_year) / 10,
               "year  1960     1970      1980      1990       "
               "2000      2010       2020      2030      2040"};
        x.label.move(-100, 0);
        Axis y{Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10, "% of population"};
        // http://www.stat.go.jp/data/jinsui/2019np/pdf/2019np.pdf
        Line current_year{Point{xs(2019), ys(0)}, Point{xs(2019), ys(100)}};
        current_year.set_style(Line_style::dash);
        win.attach(x);
        win.attach(y);
        win.attach(current_year);  // as of 2021
        win.wait_for_button();

        Open_polyline children;
        Open_polyline adults;
        Open_polyline aged;

        string file_name = "japanese-age-data.txt";
        ifstream ifs{file_name};
        if (!ifs) error("can't open ", file_name);
        // . . .
        for (Distribution d; ifs >> d;) {
            // basic sanity checks
            if (d.year < base_year || end_year < d.year)
                error("year out of range");
            if (d.young + d.middle + d.old != 100)
                error("percentages don't add up");
            const int x = xs(d.year);
            children.add(Point{x, ys(d.young)});
            adults.add(Point{x, ys(d.middle)});
            aged.add(Point{x, ys(d.old)});
        }

        Text children_label{Point{20, children.point(0).y}, "age 0-14"};
        children.set_color(Color::red);
        children_label.set_color(Color::red);

        Text adults_label{Point{20, adults.point(0).y}, "age 15-64"};
        adults.set_color(Color::blue);
        adults_label.set_color(Color::blue);

        Text aged_label{Point{20, aged.point(0).y}, "age 65+"};
        aged.set_color(Color::dark_green);
        aged_label.set_color(Color::dark_green);

        win.attach(children);
        win.attach(adults);
        win.attach(aged);

        win.attach(children_label);
        win.attach(adults_label);
        win.attach(aged_label);

        // gui_main();

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