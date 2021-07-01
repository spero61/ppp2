// Right_triangle class
// An octagonal shape with ten(!) Right_triangles
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
    : p{pp}, a{aa}, o{oo}, degrees{degrees_arg}, h{static_cast<int>(sqrt(a * a + o * o))} {
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
    : p{pp}, a{aa}, o{oo}, is_right{is_right_arg}, is_up{is_up_arg} {
    if (a <= 0 || o <= 0)
        error("Bad Right_triangle: length of each side should be positive");

    h = static_cast<int>(sqrt(a * a + o * o));  // by Pythagorean theorem

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
        Simple_window win{x, 600, 400, "Extra01: An octagonal shape with ten(!) Right_triangles"};
        win.wait_for_button();

        Point sp{220, 125};  // starting point to draw octagonal shape using eight Right_triangles
        const int side_base{150};
        const int side_short{static_cast<int>(side_base / sqrt(2))};  // side length for right isosceles triangle
        const int side_long{side_base + side_short * 2};

        // 1) Draw an octagonal shape with ten(!) Right_triangles
        // Right_triangle(Point base point, int adjacent, int opposite, bool is_right, bool is_up);
        Right_triangle rt_small_01{sp, side_short, side_short, false, true};                                         // ← ↑
        Right_triangle rt_small_02{Point{sp.x + side_base, sp.y}, side_short, side_short, true, true};               // → ↑
        Right_triangle rt_small_03{Point{sp.x, sp.y + side_base}, side_short, side_short, false, false};             // ← ↓
        Right_triangle rt_small_04{Point{sp.x + side_base, sp.y + side_base}, side_short, side_short, true, false};  // → ↓

        Right_triangle rt_medium_01{sp, side_short, side_base, false, false};                                          // ← ↓
        Right_triangle rt_medium_02{Point{sp.x - side_short, sp.y + side_base}, side_short, side_base, true, true};    // → ↑
        Right_triangle rt_medium_03{Point{sp.x + side_base + side_short, sp.y}, side_short, side_base, false, false};  // ← ↓
        Right_triangle rt_medium_04{Point{sp.x + side_base, sp.y + side_base}, side_short, side_base, true, true};     // → ↑

        Right_triangle rt_big_01{Point{sp.x, sp.y - side_short}, side_base, side_long, true, false};                          // → ↓
        Right_triangle rt_big_02{Point{sp.x + side_base, sp.y + side_base + side_short}, side_base, side_long, false, true};  // ← ↑

        Graph_lib::Vector_ref<Right_triangle> vrt;
        vrt.push_back(rt_small_01);
        vrt.push_back(rt_small_02);
        vrt.push_back(rt_small_03);
        vrt.push_back(rt_small_04);
        vrt.push_back(rt_medium_01);
        vrt.push_back(rt_medium_02);
        vrt.push_back(rt_medium_03);
        vrt.push_back(rt_medium_04);
        vrt.push_back(rt_big_01);
        vrt.push_back(rt_big_02);

        int idx{122};
        for (int i = 0; i < vrt.size(); ++i) {
            vrt[i].set_color(Color::invisible);
            vrt[i].set_fill_color(Color{i + idx++});
            win.attach(vrt[i]);
            win.wait_for_button();  // display Right_triangle one by one for debugging
        }

        // 2) Rotation madness! (by interval degrees set as below)
        Simple_window win2{Point{x.x + 100, x.y + 100}, 600, 400, "Extra02: Right_triangle rotation madness!"};
        win2.wait_for_button();

        Graph_lib::Vector_ref<Right_triangle> windmill;
        const int interval{7};
        win2.set_label("Right_triangle rotations: interval " + to_string(interval) + " degrees");
        for (int i = 1; i < 150; ++i) {
            windmill.push_back(new Right_triangle{Point{300, 195}, 100, 180, interval * i});
        }
        int idx2{57};
        for (int i = 0; i < windmill.size(); ++i) {
            windmill[i].set_color(Color::invisible);
            windmill[i].set_fill_color(Color{i + idx2++});
            win2.attach(windmill[i]);
            win2.wait_for_button();  // display Right_triangle one by one for debugging
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