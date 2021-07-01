// Marks on the Circle
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Marks on the Circle"};
        win.wait_for_button();

        Point p{win.x_max() / 2, win.y_max() / 2};
        const int r{100};
        Graph_lib::Circle c{p, r};
        c.set_color(Color::dark_cyan);
        c.set_style(Line_style{Line_style::solid, 2});
        win.attach(c);
        win.wait_for_button();

        Point focus_point{p.x, p.y - r};
        Mark focus(focus_point, 'o');
        focus.set_color(Color::magenta);
        win.attach(focus);
        win.set_label("Mark the focus on the circle");
        win.wait_for_button();

        // Move the mark each time you hit the "Next" button

        // 1) move the point at constant interval along the circumference of the circle
        const int interval{35};  // in degrees
        const int num_moves_const{12};
        for (int i = 1; i <= num_moves_const; ++i) {
            // reset the point to the center of a circle
            Point tmp{focus.point(0)};   // get the previous Point
            focus.move(-tmp.x, -tmp.y);  // move to the Point(0, 0)
            focus.move(p.x, p.y);        // move to the Point p: center of a circle

            // move to the point on the circle
            const int degrees = interval * i;
            const int x_move{static_cast<int>(r * sin((degrees % 360) * PI / 180.0))};   // since the range of degrees is from 0 to 359
            const int y_move{-static_cast<int>(r * cos((degrees % 360) * PI / 180.0))};  // modulo 360 is required for this loop
            focus.move(x_move, y_move);
            win.set_label("Constant interval Move: " + to_string(i) + " out of: " + to_string(num_moves_const) + " times (interval: " + to_string(interval) + " degrees)");
            win.wait_for_button();
        }

        // 2) move the point at constant interval along the circumference of the circle
        random_device rd;                                  // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                              // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        uniform_int_distribution<int> rd_degrees{1, 359};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        const int num_moves_random{7};
        focus.set_color(Color::cyan);  // change the color of the mark : optional
        for (int i = 1; i <= num_moves_random; ++i) {
            // reset the point to the center of a circle
            Point tmp{focus.point(0)};   // get the previous Point
            focus.move(-tmp.x, -tmp.y);  // move to the Point(0, 0)
            focus.move(p.x, p.y);        // move to the Point p: center of a circle

            // move to the point on the circle
            const int degrees{rd_degrees(gen)};
            const int x_move{static_cast<int>(r * sin(degrees * PI / 180.0))};
            const int y_move{-static_cast<int>(r * cos(degrees * PI / 180.0))};
            focus.move(x_move, y_move);
            win.set_label("Random Move: " + to_string(i) + " out of: " + to_string(num_moves_random) + " times");
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
