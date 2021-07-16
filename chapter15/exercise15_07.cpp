// Elaborate the Bar_Graph class with labeling

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Bar_Graph : public Shape {
   public:
    Bar_Graph(Point orig_arg, int xlength_arg, int ylength_arg, vector<double> values_arg, int width_arg, string title_arg = "Bar_Graph");
    void draw_lines() const override;

    // These objects are left public so that a user can manipulate them. (p.529)
    Vector_ref<Graph_lib::Rectangle> rects;
    Vector_ref<Graph_lib::Text> labels;
    vector<double> values;
    string title;

   private:
    Point orig;
    int width;  // width of each bar rectangle
    int xlength;
    int ylength;
};

Bar_Graph::Bar_Graph(Point orig_arg, int xlength_arg, int ylength_arg, vector<double> values_arg, int width_arg, string title_arg)
    : orig{orig_arg}, xlength{xlength_arg}, ylength{ylength_arg}, values{values_arg}, width{width_arg}, title{title_arg} {
    int xinterval = static_cast<int>(xlength / values.size());
    int xoffset = (xinterval - width) / 2;

    // find min_val and max_val to adjust height of each bar (scaling)
    vector<double> v_tmp{values};      // copy to v_tmp
    sort(v_tmp.begin(), v_tmp.end());  // sort in ascending order to find min and max value
    const double min_val{v_tmp[0]};
    const double max_val{v_tmp[v_tmp.size() - 1]};
    const double height_unit{(ylength * 0.90) / max_val};  // the biggest value's height is 90% of the ylength

    for (int i = 0; i < values.size(); ++i) {  // width, values[i]
        int height = static_cast<int>(values[i] * height_unit);
        rects.push_back(new Graph_lib::Rectangle{Point{orig.x + i * xinterval + xoffset, orig.y - height}, width, height});
        int color_int{16 * 7 + (i * 3)};  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        if (color_int > 255)
            color_int = ((color_int + 16 * 7) % 255) - 1;
        rects[rects.size() - 1].set_color(Color{color_int});
        rects[rects.size() - 1].set_fill_color(Color{color_int});

        ostringstream ss;
        ss << static_cast<int>(values[i]);  // since I generated pseudo-random values in int, I turn double value to int again for labeling
        labels.push_back(new Graph_lib::Text(Point{orig.x + i * xinterval, orig.y - height - 10}, ss.str()));
        labels[labels.size() - 1].set_color(Color{37});  // grey color
    }
    add(orig);
}

void Bar_Graph::draw_lines() const {
    Shape::draw_lines();  // the line
    for (int i = 0; i < values.size(); ++i) {
        rects[i].draw();
        labels[i].draw();
    }
    // since Shape type does not support "copy" I implemented as below.
    Text title_label{Point{orig.x + xlength - 285, orig.y - ylength + 15}, title};
    title_label.set_color(Color{35});
    title_label.set_font(Font::helvetica_bold);
    title_label.set_font_size(27);
    title_label.draw();
}

int main() {
    try {
        constexpr int xmax = 1200;  // window size
        constexpr int ymax = 800;

        constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
        constexpr int yoffset = 60;   // distance from bottom of window to x axis

        constexpr int xspace = 40;  // space beyond axis
        constexpr int yspace = 40;

        constexpr int xlength = xmax - xoffset - xspace;  // length of axes
        constexpr int ylength = ymax - yoffset - yspace;

        Point tl{100, 100};  // top-left
        Simple_window win{tl, xmax, ymax, "Bar Graph class"};
        win.wait_for_button();

        // vector<double> value_set{ 20, 21, 7, 15, 20, 52};
        vector<double> value_set;
        // generate pseudo-random numbers to test various number of values
        random_device rd;                                        // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                                    // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        uniform_int_distribution<int> rd_value{100, 999};        // for simplicity I used integer values
        uniform_int_distribution<int> rd_num_of_values{30, 50};  // number of bars
        const int num_of_values{rd_num_of_values(gen)};
        for (int i = 0; i < num_of_values; ++i) {
            value_set.push_back(rd_value(gen));  // assign pseudo-random value
        }

        const int bar_width{static_cast<int>((xlength / num_of_values) * 0.70)};  // bar width is 70%
        Point bp{xoffset, ymax - yoffset};                                        // base point of Bar_Graph

        Bar_Graph bg{bp, xlength, ylength, value_set, bar_width, "Pseudorandom values"};
        win.attach(bg);

        int n_value = value_set.size();
        Axis x{Axis::x, Point{xoffset, ymax - yoffset}, xlength, n_value, "x legend"};
        Axis y{Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10, "y legend"};
        x.label.set_font(Font::helvetica_bold);
        y.label.set_font(Font::helvetica_bold);
        x.label.move(240, 0);
        y.label.move(-15, 0);
        x.label.set_color(Color{37});
        y.label.set_color(Color{37});
        y.notches.set_color(Color::invisible);
        win.attach(x);
        win.attach(y);

        ostringstream sslab;
        sslab << "Bar Graph class (number of values: " << num_of_values << " )";
        win.set_label(sslab.str());
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