// Modify Binary_tree to take a parameter (or parameters) to indicate
// what kind of line to use to connect the nodes
// (e.g., an arrow pointing down or a red arrow pointing up).
// Note how this exercise and the last use two alternative ways of making a class hierarchy more flexible and useful.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// Arrow class from exercise13_03.cpp
constexpr double PI{3.14159265358979};
struct Arrow : Shape {
    Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd);
    Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow);
    void draw_lines() const;

   private:
    int d;        // size of an arrow
    bool p1_arw;  // is arrow at p1
    bool p2_arw;  // is arrow at p2
};

Arrow::Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd) : p1_arw{p1_arrow}, p2_arw{p2_arrow}, d{dd} {
    if (d <= 0)
        error("Bad Arrow: size of a triangle should have positive value");
    add(p1);
    add(p2);
}

Arrow::Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow) : p1_arw{p1_arrow}, p2_arw{p2_arrow}, d{7} {
    if (d <= 0)
        error("Bad Arrow: size of a triangle should have positive value");
    add(p1);
    add(p2);
}

void Arrow::draw_lines() const {
    const double arrow_angle{PI / 6.0};  // 30 degrees

    if (color().visibility()) {
        fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

        int dy{point(1).y - point(0).y};
        int dx{point(1).x - point(0).x};
        double angle{atan2(dy, dx)};  // https://en.cppreference.com/w/c/numeric/math/atan2

        // fl_line: https://www.fltk.org/doc-1.3/group__fl__drawings.html#gaecc374f163a97ef67c4e58be11c47047
        if (p1_arw) {
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle + arrow_angle), point(0).y + d * sin(angle + arrow_angle));
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle - arrow_angle), point(0).y + d * sin(angle - arrow_angle));
        }
        if (p2_arw) {
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle + arrow_angle), point(1).y - d * sin(angle + arrow_angle));
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle - arrow_angle), point(1).y - d * sin(angle - arrow_angle));
        }
    }
}

class Binary_tree : public Shape {
   public:
    Binary_tree(Point rp_arg, int levels_arg);  // levels==0 means no nodes
    Binary_tree(Point rp_arg, int levels_arg, bool up_arrow_arg, bool down_arrow_arg);
    void draw_lines() const override;

   private:
    Point rp;
    int levels;
    bool up_arrow;
    bool down_arrow;
};

Binary_tree::Binary_tree(Point rp_arg, int levels_arg) : rp{rp_arg}, levels{levels_arg}, up_arrow{false}, down_arrow{false} {
    if (levels < 0)
        error("Bad Binary_tree: levels must have greater than or equal to 0");
    const int vertical{80};    // vertical distance between nodes
    const int horizontal{30};  // horizontal distance between nodes

    for (int i = 1; i <= levels + 1; ++i) {
        const int dy{(i - 1) * vertical};
        for (int j = 0; j < pow(2, i - 1); ++j) {
            int dx{static_cast<int>(((pow(2, i - 1) - 1) / 2 - j) * pow(2, levels - i + 1) * horizontal)};
            add(Point{rp.x + dx, rp.y + dy});
        }
    }
}

Binary_tree::Binary_tree(Point rp_arg, int levels_arg, bool up_arrow_arg, bool down_arrow_arg) : rp{rp_arg}, levels{levels_arg}, up_arrow{up_arrow_arg}, down_arrow{down_arrow_arg} {
    if (levels < 0)
        error("Bad Binary_tree: levels must have greater than or equal to 0");
    const int vertical{80};    // vertical distance between nodes
    const int horizontal{30};  // horizontal distance between nodes

    for (int i = 1; i <= levels + 1; ++i) {
        const int dy{(i - 1) * vertical};
        for (int j = 0; j < pow(2, i - 1); ++j) {
            int dx{static_cast<int>(((pow(2, i - 1) - 1) / 2 - j) * pow(2, levels - i + 1) * horizontal)};
            add(Point{rp.x + dx, rp.y + dy});
        }
    }
}

void Binary_tree::draw_lines() const {
    const int r{10};                  // radius of the node
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        for (int i = 0; i < number_of_points(); ++i) {
            fl_pie(point(i).x, point(i).y, r + r - 1, r + r - 1, 0, 360);  // node fill
        }
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        for (int i = 0; i < number_of_points(); ++i) {
            fl_arc(point(i).x, point(i).y, r + r, r + r, 0, 360);  // node
        }

        // lines without arrows
        if (up_arrow == false && down_arrow == false) {
            int count{0};
            for (int i = 0; i < levels; ++i) {
                int first{static_cast<int>(pow(2, i) - 1)};
                int next{static_cast<int>(first + pow(2, i))};
                for (int j = first; j < next; ++j) {
                    count++;
                    Line{Point{point(j).x + r, point(j).y + r + r}, Point{point(j + count).x + r, point(j + count).y}}.draw();
                    Line{Point{point(j).x + r, point(j).y + r + r}, Point{point(j + count + 1).x + r, point(j + count + 1).y}}.draw();
                }
            }
            count = 0;  // reset
        }

        // line with an arrow or arrows
        else {
            int count{0};
            for (int i = 0; i < levels; ++i) {
                int first{static_cast<int>(pow(2, i) - 1)};
                int next{static_cast<int>(first + pow(2, i))};
                for (int j = first; j < next; ++j) {
                    count++;
                    Arrow{Point{point(j).x + r + 2, point(j).y + r + r}, Point{point(j + count).x + r, point(j + count).y}, up_arrow, down_arrow}.draw();
                    Arrow{Point{point(j).x + r - 2, point(j).y + r + r}, Point{point(j + count + 1).x + r, point(j + count + 1).y}, up_arrow, down_arrow}.draw();
                }
            }
            count = 0;  // reset
        }
    }
}

int main() {
    try {
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 1000, 600, "Binary_tree");
        win.wait_for_button();

        const int levels{5};
        Binary_tree b_tree_arrow(Point{win.x_max() / 2, 80}, levels, false, true);
        b_tree_arrow.set_color(Color{16 * 6 + 2});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        b_tree_arrow.set_fill_color(Color{16 * 6 + 7});
        win.set_label("Binary_tree (levels: " + to_string(levels) + ')');
        win.attach(b_tree_arrow);
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
