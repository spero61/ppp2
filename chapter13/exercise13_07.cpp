// RGB color charts
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

int main() {
    try {
        constexpr int side{256};
        const int size{2};  // size of a square

        int rgb_min{0};
        int rgb_max{255};

        const Point x{100, 100};
        Simple_window win{x, side * size * 2 * 2, side * size * 2, "RGB color charts"};
        win.wait_for_button();
        /* RGB color chart presentation order
          1     2       5       6

          3     4       7       8

          vr    vb      vrgb_2  vb_2

          vg    vrgb    vg_2    vr_2

        */

        // RGB color chart : https://www.rapidtables.com/web/color/RGB_Color.html#color-chart
        // The red, green and blue use 8 bits each, which have integer values from 0 to 255.
        // This makes 256*256*256 = 16777216 possible colors. (4096 * 4096)

        // Note that it is unnecessary to create eight different Vector_ref objects.
        // However, it might be helpful to see which part is in charge of
        // drawing a specific RGB color chart by differentiating their names.

        // fl_rgb_color() documentation link: https://www.fltk.org/doc-1.3/Enumerations_8H.html#a7c5acc4633fbab7016bce2fb69046494
        // fl_rgb_color (uchar r, uchar g, uchar b): Returns the 24 - bit color value closest to r, g, b.
        Graph_lib::Vector_ref<Graph_lib::Rectangle> vr;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vr.push_back(new Graph_lib::Rectangle{Point{i * size, j * size}, size, size});
                vr[vr.size() - 1].set_fill_color(Color(fl_rgb_color(rgb_min++, i, j)));
                vr[vr.size() - 1].set_color(Color::invisible);
                win.attach(vr[vr.size() - 1]);
            }
        }
        rgb_min = 0;  // re-initialization for later use (in case)

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vg;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vg.push_back(new Graph_lib::Rectangle{Point{i * size, j * size + (side * size)}, size, size});
                vg[vg.size() - 1].set_fill_color(Color(fl_rgb_color(i, rgb_min++, j)));
                vg[vg.size() - 1].set_color(Color::invisible);
                win.attach(vg[vg.size() - 1]);
            }
        }
        rgb_min = 0;

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vb;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vb.push_back(new Graph_lib::Rectangle{Point{i * size + (side * size), j * size}, size, size});
                vb[vb.size() - 1].set_fill_color(Color(fl_rgb_color(i, j, rgb_max--)));
                vb[vb.size() - 1].set_color(Color::invisible);
                win.attach(vb[vb.size() - 1]);
            }
        }
        rgb_max = 255;

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vrgb;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vrgb.push_back(new Graph_lib::Rectangle{Point{i * size + (side * size), j * size + (side * size)}, size, size});
                vrgb[vrgb.size() - 1].set_fill_color(Color(fl_rgb_color(rgb_max--, i, j)));
                vrgb[vrgb.size() - 1].set_color(Color::invisible);
                win.attach(vrgb[vrgb.size() - 1]);
            }
        }
        rgb_max = 255;

        // Right hand side RGB color charts
        // this charts are created by swap the i, j index values of for loops (e.g., fl_rgb_color(i, green++, j) -> fl_rgb_color(j, green++, i))
        // except for vr_2, the last one. (See comments right above the vr_2's implementation code)
        const int rhs_x{win.x_max() / 2};  // x coordinate starting point for right hand side RGB color charts

        // this is the closest to the RGB chart we are familiar with
        Graph_lib::Vector_ref<Graph_lib::Rectangle> vrgb_2;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vrgb_2.push_back(new Graph_lib::Rectangle{Point{(i * size) + rhs_x, j * size}, size, size});
                vrgb_2[vrgb_2.size() - 1].set_fill_color(Color(fl_rgb_color(rgb_max--, j, i)));
                vrgb_2[vrgb_2.size() - 1].set_color(Color::invisible);
                win.attach(vrgb_2[vrgb_2.size() - 1]);
            }
        }
        rgb_max = 255;

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vb_2;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vb_2.push_back(new Graph_lib::Rectangle{Point{i * size + (side * size) + rhs_x, j * size}, size, size});
                vb_2[vb_2.size() - 1].set_fill_color(Color(fl_rgb_color(j, i, rgb_max--)));
                vb_2[vb_2.size() - 1].set_color(Color::invisible);
                win.attach(vb_2[vb_2.size() - 1]);
            }
        }
        rgb_max = 255;

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vg_2;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vg.push_back(new Graph_lib::Rectangle{Point{i * size + rhs_x, j * size + (side * size)}, size, size});
                vg[vg.size() - 1].set_fill_color(Color(fl_rgb_color(j, rgb_min++, i)));
                vg[vg.size() - 1].set_color(Color::invisible);
                win.attach(vg[vg.size() - 1]);
            }
        }
        rgb_min = 0;

        // this is created using pseudo-random variables

        random_device rd;                         // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                     // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        normal_distribution<> norm_dist{128, 1};  // https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
        Graph_lib::Vector_ref<Graph_lib::Rectangle> vr_2;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                vr_2.push_back(new Graph_lib::Rectangle{Point{i * size + (side * size) + rhs_x, j * size + (side * size)}, size, size});
                vr_2[vr_2.size() - 1].set_fill_color(Color(fl_rgb_color(norm_dist(gen), i, j)));
                vr_2[vr_2.size() - 1].set_color(Color::invisible);
                win.attach(vr_2[vr_2.size() - 1]);
            }
        }
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