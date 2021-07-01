// Tiling with right triangles
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;
constexpr double PI{3.14159265358979};

struct Right_triangle : Shape {
    Right_triangle(Point pp, int aa, int oo, int degrees_arg);  // clockwise rotation
    Right_triangle(Point pp, int aa, int oo, bool is_right_arg, bool is_up_arg);

    void draw_lines() const;

    int adjacent() const { return a; }
    int opposite() const { return o; }
    int hypotenuse() const { return h; }

   private:
    int a;          // adjacent
    int o;          // opposite
    int h;          // hypotenuse: optional (for later use)
    Point p;        // a base point of the Right_triangle where the adjacent and opposite meet
    bool is_right;  // check if adjacent is defined between base_point and positive_x direction (right from user's point of view)
    bool is_up;     // check if opposite is defined between base_point and negative_x direction (upward from user's point of view)};
    int degrees;    // used to create clockwise rotated Right_triangle
};

Right_triangle::Right_triangle(Point pp, int aa, int oo, int degrees_arg)
    : p{pp}, a{aa}, o{oo}, degrees{degrees_arg}, h{static_cast<int>(sqrt(a * a + o * o))}, is_right{1}, is_up{1} {
    if (a <= 0 || o <= 0)
        error("Bad Right_triangle: length of each side should be positive");
    if (degrees <= 0)
        error("error: degrees should be a positive integer");

    // initialize points below as if using is_right = true, is_up = true.
    Point p_a{Point{p.x + a, p.y}};  // temporary adjacent point before rotation.
    Point p_o{Point{p.x, p.y - o}};  // temporary opposite point before rotation.

    // rotate adjacent point(=point(1))
    int radius = a;                                                    // length of the adjacent
    int x_move{static_cast<int>(radius * sin(degrees * PI / 180.0))};  // range of degrees is from 0 to 359
    int y_move{-static_cast<int>(radius * cos(degrees * PI / 180.0))};
    Point adjacent_point{p.x + x_move, p.y + y_move};

    // rotate opposite point(=point(2))
    radius = o;                                                                    // length of the opposite
    x_move = static_cast<int>(radius * sin(((degrees + 90) % 360) * PI / 180.0));  // range of degrees is from 0 to 359
    y_move = -static_cast<int>(radius * cos(((degrees + 90) % 360) * PI / 180.0));
    Point opposite_point{p.x + x_move, p.y + y_move};

    add(p);  // (base point)

    add(adjacent_point);
    add(opposite_point);

    add(p);  // (base point): add starting point again. Because this class utilizes Open_polygon class
}

Right_triangle::Right_triangle(Point pp, int aa, int oo, bool is_right_arg, bool is_up_arg)
    : p{pp}, a{aa}, o{oo}, h{static_cast<int>(sqrt(a * a + o * o))}, is_right{is_right_arg}, is_up{is_up_arg}, degrees{0} {
    if (a <= 0 || o <= 0)
        error("Bad Right_triangle: length of each side should be positive");

    add(Point{p.x, p.y});  // (base point)

    // Note that I did not reassign the value of a(adjacent) nor o(opposite) to remain them as positive values in case of later use.
    if (is_right)
        add(Point{p.x + a, p.y});  // (adjacent): locate the point to the [right] of the base point
    else
        add(Point{p.x - a, p.y});  // (adjacent): locate the point to the [left] of the base point

    if (is_up)
        add(Point{p.x, p.y - o});  // (opposite): locate the point to the [upward] of the base point
    else
        add(Point{p.x, p.y + o});  // (opposite): locate the point to the [downward] of the base point

    add(Point{p.x, p.y});  // (base point): add starting point again. Because this class utilizes Open_polygon class
}

void Right_triangle::draw_lines() const {
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

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 1200, 800, "Tiling with right triangles"};
        win.wait_for_button();

        Point sp{0, 0};  // starting point to draw octagonal shape using eight Right_triangles
        const int adjacent{40};
        const int opposite{40};

        Graph_lib::Vector_ref<Right_triangle> vrt;
        const int x_axis{win.x_max() / adjacent + 1};  // to fill the entire window
        const int y_axis{win.y_max() / opposite + 1};  // plus 1 in case of truncation occurs

        int idx{0};
        for (int i = 0; i < y_axis; ++i) {
            for (int j = 0; j < x_axis; ++j) {
                vrt.push_back(new Right_triangle{Point{sp.x + j * adjacent, sp.y + i * opposite}, adjacent, opposite, true, false});
                vrt.push_back(new Right_triangle{Point{sp.x + (j + 1) * adjacent, sp.y + (i + 1) * opposite}, adjacent, opposite, false, true});

                vrt[vrt.size() - 2].set_color(Color::invisible);
                vrt[vrt.size() - 2].set_fill_color(Color{(i + idx++) % 256});
                win.attach(vrt[vrt.size() - 2]);

                vrt[vrt.size() - 1].set_color(Color::invisible);
                vrt[vrt.size() - 1].set_fill_color(Color{(i + idx++) % 256});
                win.attach(vrt[vrt.size() - 1]);
            }
        }
        win.set_label("Tiling with right triangles (adjacent: " + to_string(adjacent) + ", opposite: " + to_string(opposite) + " )");
        win.wait_for_button();  // display Right_triangle one by one for debugging
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}