// Modify Binary_tree to draw its nodes using a virtual function.
// Then, derive a new class from Binary_tree that overrides that virtual function
// to use a different representation for a node (e.g., a triangle).

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// Regular_polygon class from exercise13_10.cpp
constexpr double PI{3.14159265358979};
class Regular_polygon : public Shape {
   public:
    Regular_polygon(Point cc, int dd, int ss);
    void draw_lines() const;
    Point center() { return c; }

   private:
    Point c;  // center point of the Regular_polygon.
    int d;    // A distance from the center which is radius of the circumscribed circle.
    int s;    // number of side that a Regular_polygon has. (s => 3)
};

Regular_polygon::Regular_polygon(Point cc, int dd, int ss) : c{cc}, d{dd}, s{ss} {
    if (d <= 0)
        error("Bad Regular_polygon: distance should be positive");
    if (s <= 2)
        error("Bad Regular_polygon: number of sides should be greater than 2");

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
            error("error(Regular_polygon constructor): This should not be reached");
    }

    add(Point{c.x, c.y - d});  // add starting point again. Because this class utilizes Open_polygon class
}

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

class Binary_tree : public Shape {
   public:
    Binary_tree() {}
    Binary_tree(Point rp_arg, int levels_arg);  // levels==0 means no nodes
    virtual void draw_lines() const;

   private:
    Point rp;
    int levels;
};

Binary_tree::Binary_tree(Point rp_arg, int levels_arg) : rp{rp_arg}, levels{levels_arg} {
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

        // lines
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
}

class Binary_tree_polygon_node : public Binary_tree {
   public:
    Binary_tree_polygon_node(Point rp_arg, int levels_arg, int ss);  // levels==0 means no nodes
    void draw_lines() const override;

   private:
    Point rp;
    int levels;
    int s;  // number of side that a node has
};

Binary_tree_polygon_node::Binary_tree_polygon_node(Point rp_arg, int levels_arg, int ss) : rp{rp_arg}, levels{levels_arg}, s{ss} {
    if (levels < 0)
        error("Bad Binary_tree_polygon_node: levels must have greater than or equal to 0");
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

void Binary_tree_polygon_node::draw_lines() const {
    const int r{10};  // radius of the node

    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());

        // node fill
        for (int i = 0; i < number_of_points(); ++i) {
            //Regular_polygon(Point cc, int dd, int ss);
            Regular_polygon tmp{point(i), r, s};
            fl_begin_complex_polygon();
            for (int j = 0; j < tmp.number_of_points(); ++j) {
                fl_vertex(tmp.point(j).x, tmp.point(j).y);
            }
            fl_end_complex_polygon();
        }
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        for (int i = 0; i < number_of_points(); ++i) {
            //Regular_polygon(Point cc, int dd, int ss);
            Regular_polygon(point(i), r, s).draw();  // node
        }
        // lines
        int count{0};
        for (int i = 0; i < levels; ++i) {
            int first{static_cast<int>(pow(2, i) - 1)};
            int next{static_cast<int>(first + pow(2, i))};
            for (int j = first; j < next; ++j) {
                count++;
                Line{Point{point(j).x, point(j).y + r}, Point{point(j + count).x, point(j + count).y - r}}.draw();
                Line{Point{point(j).x, point(j).y + r}, Point{point(j + count + 1).x, point(j + count + 1).y - r}}.draw();
            }
        }
        count = 0;  // reset
    }
}

int main() {
    try {
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 1000, 600, "Binary_tree");
        win.wait_for_button();

        const int levels{5};
        const int node_polygon{4};
        Binary_tree_polygon_node b_tree_square(Point{win.x_max() / 2, 80}, levels, node_polygon);
        b_tree_square.set_color(Color::dark_magenta);
        b_tree_square.set_fill_color(Color::cyan);
        win.set_label("Binary_tree (levels: " + to_string(levels) + " node_polyon: " + to_string(node_polygon) + ')');
        win.attach(b_tree_square);
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
