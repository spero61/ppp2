// Color matrix without lines around each color.
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "16 x 16 color matrix w/o lines"};
        win.wait_for_button();

        Graph_lib::Vector_ref<Graph_lib::Rectangle> vr;
        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 16; ++j) {
                vr.push_back(new Graph_lib::Rectangle{Point{i * 20, j * 20}, 20, 20});
                vr[vr.size() - 1].set_color(Color::invisible);
                vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
                win.attach(vr[vr.size() - 1]);
            }
            //win.wait_for_button(); // display color cells line by line (vertically)
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