// Right_triangle class
// An octagonal shape with eight Right_triangles
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;
constexpr double PI{3.14159265358979};

struct Right_triangle : Shape {
    Right_triangle(Point pp, int aa, int oo, int degrees_arg);  // clockwise rotation
    using Shape::Shape;
    void draw_lines() const;

    int adjacent() const { return a; }
    int opposite() const { return o; }
    int hypotenuse() const { return h; }

   private:
    int a;        // adjacent
    int o;        // opposite
    int h;        // hypotenuse: optional (for later use)
    Point p;      // a base point of the Right_triangle where the adjacent and opposite meet
    int degrees;  // used to create clockwise rotated Right_triangle
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
        Simple_window win{x, 600, 400, "An octagonal shape with eight Right_triangles"};
        win.wait_for_button();

        // Right_triangle(Point base point, int adjacent, int opposite, int clockwise degrees);
        Point sp{140, 110};        // starting point to draw octagonal shape using eight Right_triangles
        const int side_base{125};  // length of leg of the rt_small_xx(right isoceles triangles)
        Right_triangle rt_small_01{sp, side_base, side_base, 45};
        Right_triangle rt_small_02{Point{sp.x, sp.y + static_cast<int>(sqrt(2) * side_base)}, side_base, side_base, 45};
        Right_triangle rt_small_03{Point{sp.x + static_cast<int>((side_base / sqrt(2) * 2) + side_base), sp.y}, side_base, side_base, 225};
        Right_triangle rt_small_04{Point{sp.x + static_cast<int>((side_base / sqrt(2) * 2) + side_base), sp.y + static_cast<int>(sqrt(2) * side_base)}, side_base, side_base, 225};
        Right_triangle rt_small_05{Point{sp.x + static_cast<int>(side_base / sqrt(2)), sp.y + static_cast<int>(side_base / sqrt(2))}, side_base, side_base, 225};
        Right_triangle rt_small_06{Point{sp.x + static_cast<int>(side_base / sqrt(2) + side_base), sp.y + static_cast<int>(side_base / sqrt(2))}, side_base, side_base, 45};

        Point top_left{sp.x + static_cast<int>(side_base / sqrt(2)), sp.y - static_cast<int>(side_base / sqrt(2))};
        const int rt_big_opposite{static_cast<int>(2 * sqrt(2) * side_base)};

        Right_triangle rt_big_01{top_left, side_base, rt_big_opposite, 90};
        Right_triangle rt_big_02{Point{top_left.x + side_base, top_left.y + rt_big_opposite}, side_base, rt_big_opposite, 270};

        Graph_lib::Vector_ref<Right_triangle> vrt;
        vrt.push_back(rt_small_01);
        vrt.push_back(rt_small_02);
        vrt.push_back(rt_small_03);
        vrt.push_back(rt_small_04);
        vrt.push_back(rt_small_05);
        vrt.push_back(rt_small_06);
        vrt.push_back(rt_big_01);
        vrt.push_back(rt_big_02);

        int idx{97};
        for (int i = 0; i < vrt.size(); ++i) {
            vrt[i].set_color(Color::invisible);
            vrt[i].set_fill_color(Color{i * 5 + idx++});
            win.attach(vrt[i]);
            win.wait_for_button();  // display right_triangle one by one for debugging
        }

        /*
        //  color combination test code
        int coef{ 97 };
        while (true) {
            int idx{ 0 + coef };
            win.set_label(to_string(idx));
            for (int i = 0; i < vrt.size(); ++i) {
                vrt[i].set_color(Color::invisible);
                vrt[i].set_fill_color(Color{ i*5 + idx++ });
                win.attach(vrt[i]);
            }
            win.wait_for_button();
            coef++;
        }
        */

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}