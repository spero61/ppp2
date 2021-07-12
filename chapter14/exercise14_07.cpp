// Define a Striped_closed_polyline using the technique from Striped_rectangle
// (this requires some algorithmic inventiveness)

// Note: This solution does not consider when the lines are intersect!
// I'll be back to fix that problem later. (Probably after study some algorithms)

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Striped_closed_polyline : public Closed_polyline {
   public:
    using Closed_polyline::Closed_polyline;
    void draw_lines() const override;
};

int calc_y(int x1, int y1, int x2, int y2, int x) {
    double result = ((y2 - y1) / ((x2 - x1 * 1.0))) * (x - x1) + y1;  // for the accuracy, first calculated value is saved to double
    return static_cast<int>(result);
}

double calc_slope(int x1, int y1, int x2, int y2) {
    return ((y2 - y1) / (x2 - x1));
}

int calc_prev_p(int current_point, int last_point) {
    if (current_point == 0)
        return last_point;
    else
        return current_point - 1;
}

int calc_next_p(int current_point, int last_point) {
    if (current_point == last_point)
        return 0;
    else
        return current_point + 1;
}

void Striped_closed_polyline::draw_lines() const {
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());

        const int not_min{9999};
        const int not_max{-9999};

        int p_x_min{0};
        int p_x_max{0};
        int last_p{number_of_points() - 1};

        int x_min{not_min};
        int x_max{not_max};
        for (int i = 0; i < number_of_points(); ++i) {
            if (point(i).x < x_min) {
                x_min = point(i).x;
                p_x_min = i;
            }
            if (point(i).x > x_max) {
                x_max = point(i).x;
                p_x_max = i;
            }
        }

        int y_min{not_min};
        int y_max{not_max};
        for (int i = 0; i < number_of_points(); ++i) {
            if (point(i).y < y_min)
                y_min = point(i).y;
            if (point(i).y > y_max)
                y_max = point(i).y;
        }

        // vector<int> point(?).y using line of equation
        // upward from the x_min_point
        vector<int> upward_y;
        int curr_p_up{p_x_min};
        int next_p{calc_next_p(curr_p_up, last_p)};
        for (int x = x_min; x < x_max; ++x) {
            int x1 = point(curr_p_up).x;
            int y1 = point(curr_p_up).y;
            int x2 = point(next_p).x;
            int y2 = point(next_p).y;

            if (x == x2) {  // when x coordinate reaches at the vertex
                curr_p_up = next_p;
                next_p = calc_next_p(next_p, last_p);
                --x;
            } else {
                upward_y.push_back(calc_y(x1, y1, x2, y2, x));
            }
        }

        // vector<int> point(?).y using line of equation
        // downward from the x_min_point
        vector<int> downward_y;
        int curr_p_down{p_x_min};
        int prev_p{calc_prev_p(curr_p_down, last_p)};
        for (int x = x_min; x < x_max; ++x) {
            int x1 = point(curr_p_down).x;
            int y1 = point(curr_p_down).y;
            int x2 = point(prev_p).x;
            int y2 = point(prev_p).y;
            if (x == x2) {  // when x coordinate reaches at the vertex
                curr_p_down = prev_p;
                prev_p = calc_prev_p(prev_p, last_p);
                --x;
            } else
                downward_y.push_back(calc_y(x1, y1, x2, y2, x));
        }

        const int itv{3};  // stripe interval
        for (int x = x_min, i = 0; x < x_max; x += itv, i += itv) {
            fl_line(x, downward_y[i], x, upward_y[i]);
        }

        fl_color(color().as_int());  // reset color
    }

    if (color().visibility())
        Shape::draw_lines();

    if (color().visibility())  // draw closing line:
        fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Striped_closed_polyline"};
        win.wait_for_button();

        const int radius{200};

        Striped_closed_polyline scp;
        scp.add(Point{130, 100});  // point(0)
        scp.add(Point{230, 150});  //  point(1)
        scp.add(Point{330, 170});  //  point(2)
        scp.add(Point{350, 250});  //  point(3)
        scp.add(Point{180, 390});  //  point(4)
        scp.add(Point{50, 200});   //  point(5)
        scp.set_color(Color{16 * 11 + 12});
        win.attach(scp);
        win.wait_for_button();
        scp.set_fill_color(Color{16 * 11 + 12});
        win.wait_for_button();

        Point p{550, 220};
        const int m{25};  //  (size) multiplier

        vector<Point> vp;
        vp.push_back(Point{p.x, p.y});                  // top_center
        vp.push_back(Point{p.x + 2 * m, p.y - 2 * m});  // rhs point 01
        vp.push_back(Point{p.x + 5 * m, p.y - 3 * m});  // rhs point 02
        vp.push_back(Point{p.x + 6 * m, p.y - 1 * m});  // rhs point 03
        vp.push_back(Point{p.x + 4 * m, p.y + 4 * m});  // rhs point 04
        vp.push_back(Point{p.x, p.y + 7 * m});          // bottom_center
        vp.push_back(Point{p.x - 4 * m, p.y + 4 * m});  // lhs point 04
        vp.push_back(Point{p.x - 6 * m, p.y - 1 * m});  // lhs point 03
        vp.push_back(Point{p.x - 5 * m, p.y - 3 * m});  // lhs point 02
        vp.push_back(Point{p.x - 2 * m, p.y - 2 * m});  // lhs point 01

        Striped_closed_polyline heart;
        for (Point p : vp) {
            heart.add(p);
        }

        win.attach(heart);
        heart.set_color(Color{129});
        win.wait_for_button();
        heart.set_fill_color(Color{129});
        win.wait_for_button();

        //// This solution does not work for Closed_polyline that has lines intersect.
        //// Need to solve the problem later
        //Striped_closed_polyline intersect;
        //intersect.add(Point{ 50, 200 });
        //intersect.add(Point{ 300, 200 });
        //intersect.add(Point{ 270, 500 });
        //intersect.add(Point{ 650, 500 });
        //win.attach(intersect);
        //win.wait_for_button();
        //intersect.set_color(Color::magenta);
        //intersect.set_fill_color(Color::magenta);
        //win.wait_for_button();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}