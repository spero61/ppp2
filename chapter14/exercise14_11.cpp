// Define a Binary_tree class derived from Shape.
// Give the number of levels as a parameter (levels==0 means no nodes, levels==1 means one node,
// levels==2 means one top node with two sub-nodes,
// levels==3 means one top node with two sub-nodes each with two sub-nodes, etc.).
// Let a node be represented by a small circle. Connect the nodes by lines (as is conventional).

// Thought: If I have learned "Pointer" I would have solved this problem with recursion (REVIEW)

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Binary_tree : public Shape {
   public:
    Binary_tree(Point rp_arg, int levels_arg);  // levels==0 means no nodes
    void draw_lines() const override;

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

int main() {
    try {
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 1000, 600, "Binary_tree");
        win.wait_for_button();

        const int levels{5};
        Binary_tree b_tree(Point{win.x_max() / 2, 80}, levels);
        b_tree.set_color(Color::dark_blue);
        b_tree.set_fill_color(Color{16 * 13 + 6});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        win.set_label("Binary_tree (levels: " + to_string(levels) + ')');
        win.attach(b_tree);
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
