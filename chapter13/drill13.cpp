#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        // 1. Make an 800-by-1000 Simple_window
        const Point x{100, 100};
        Simple_window win{x, 800, 1000, "Drill 13_01"};
        win.wait_for_button();

        // 2. Put an 8-by-8 grid on the leftmost 800-by-800 part of that window
        const int x_size = 800;
        const int y_size = 800;
        const int x_grid = x_size / 8;  // 100
        const int y_grid = y_size / 8;  // 100
        Lines grid;
        for (int x = x_grid; x <= x_size; x += x_grid)
            grid.add(Point{x, 0}, Point{x, y_size});  // vertical line
        for (int y = y_grid; y <= y_size; y += y_grid)
            grid.add(Point{0, y}, Point{x_size, y});  // horizontal line

        grid.set_style(Line_style{Line_style::solid, 2});
        win.attach(grid);
        win.set_label("Drill 13_02");
        win.wait_for_button();

        // 3. Make the eight squares on the diagonal starting from the top left corner red
        Graph_lib::Vector_ref<Graph_lib::Rectangle> vr;
        for (int i = 0; i < 8; ++i) {
            vr.push_back(new Graph_lib::Rectangle{Point{i * x_grid, i * y_grid}, x_grid, y_grid});
            vr[vr.size() - 1].set_fill_color(Color::red);
            win.attach(vr[vr.size() - 1]);
        }
        win.set_label("Drill 13_03");
        win.wait_for_button();

        // 4. Find a 200-by-200-pixel image (JPEG or GIF)
        // and place three copies of it on the grid (each image covering four squares)
        // Don't obscure the red squares
        Graph_lib::Vector_ref<Graph_lib::Image> vi;
        for (int i = 0; i < 3; ++i) {
            vi.push_back(new Graph_lib::Image{Point{(x_grid * 2) * i, y_size - (y_grid * 2) * (i + 1)}, "image_drill13.jpg"});
            win.attach(vi[vi.size() - 1]);
        }
        win.set_label("Drill 13_04");
        win.wait_for_button();

        // 5. Add a 100-by-100 image.
        // Have it move around from squares to square when you click the "Next" button.
        random_device rd;                          // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                      // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        uniform_int_distribution<int> x_rd{0, 7};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        uniform_int_distribution<int> y_rd{0, 7};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

        vector<int> x_vals;
        vector<int> y_vals;
        const int x_val{x_grid * x_rd(gen)};
        const int y_val{y_grid * y_rd(gen)};
        Image vt{Point{x_val, y_val}, "valkoinen_tiikeri.jpg"};
        x_vals.push_back(x_val);
        y_vals.push_back(y_val);
        win.attach(vt);
        win.set_label("Drill 13_05 pseudo-randomly move the image 707 times");
        win.wait_for_button();

        uniform_int_distribution<int> x_move_coef{1, 4};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        uniform_int_distribution<int> y_move_coef{1, 4};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        int x_move{0};
        int y_move{0};
        for (int i = 1; i <= 707; ++i) {
            int prev_x_val{x_vals[x_vals.size() - 1]};
            int prev_y_val{y_vals[y_vals.size() - 1]};

            x_move = (prev_x_val < x_size / 2) ? x_move_coef(gen) * x_grid : -x_move_coef(gen) * x_grid;
            y_move = (prev_y_val < y_size / 2) ? y_move_coef(gen) * y_grid : -y_move_coef(gen) * y_grid;

            x_vals.push_back(prev_x_val + x_move);
            y_vals.push_back(prev_y_val + y_move);

            vt.move(x_move, y_move);
            win.set_label("Drill 13_05_" + to_string(i));
            win.wait_for_button();
        }

        win.set_label("Done: Have you clicked 707 times? wow :)");
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