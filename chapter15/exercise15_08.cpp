// Histogram and read data from a file

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Distribution {
    double height;
    double n_people;
};
istream& operator>>(istream& is, Distribution& d)
// assume format: ( height , n_people )
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Distribution dd;
    if (is >> ch1 >> dd.height >> ch2 >> dd.n_people >> ch3) {
        if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
            is.clear(ios_base::failbit);
            return is;
        }
    } else
        return is;
    d = dd;
    return is;
}

// It is possible to derived class technique of Bar_Graph.
// Here I just reimplement using that code because I did not put all classes
// to the graphics interface library (i.e., Graph.h, Graph.cpp)
class Histogram : public Shape {
   public:
    Histogram(Point orig_arg, int xlength_arg, int ylength_arg, vector<double> values_arg, vector<double> values2_arg, string title_arg = "Histogram");
    void draw_lines() const override;

    // These objects are left public so that a user can manipulate them. (p.529)
    Vector_ref<Graph_lib::Rectangle> rects;
    Vector_ref<Graph_lib::Text> labels;
    Vector_ref<Graph_lib::Text> labels2;
    vector<double> values;
    vector<double> values2;
    string title;

   private:
    Point orig;
    int xlength;
    int ylength;
};

Histogram::Histogram(Point orig_arg, int xlength_arg, int ylength_arg, vector<double> values_arg, vector<double> values2_arg, string title_arg)
    : orig{orig_arg}, xlength{xlength_arg}, ylength{ylength_arg}, values{values_arg}, values2{values2_arg}, title{title_arg} {
    int xinterval = static_cast<int>(xlength / values.size());

    // find min_val and max_val to adjust height of each bar (scaling)
    vector<double> v_tmp{values};      // copy to v_tmp
    sort(v_tmp.begin(), v_tmp.end());  // sort in ascending order to find min and max value
    const double min_val{v_tmp[0]};
    const double max_val{v_tmp[v_tmp.size() - 1]};
    const double height_unit{(ylength * 0.90) / max_val};  // the biggest value's height is 90% of the ylength

    for (int i = 0; i < values.size(); ++i) {  // width, values[i]
        int height = static_cast<int>(values[i] * height_unit);
        rects.push_back(new Graph_lib::Rectangle{Point{orig.x + i * xinterval, orig.y - height}, xinterval, height});
        int color_int{16 * 13 + (i + 1) * 7};  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        if (color_int > 255)
            color_int = ((color_int + 16 * 7) % 255) - 1;
        rects[rects.size() - 1].set_color(Color{color_int});
        rects[rects.size() - 1].set_fill_color(Color{color_int});

        ostringstream ss;
        ss << static_cast<int>(values[i]);  // since I generated pseudo-random values in int, I turn double value to int again for labeling
        labels.push_back(new Graph_lib::Text(Point{orig.x + i * xinterval, orig.y - height - 10}, ss.str()));
        labels[labels.size() - 1].set_color(Color{21});

        ostringstream ss2;
        ss2 << static_cast<int>(values2[i]);  // since I generated pseudo-random values in int, I turn double value to int again for labeling
        labels2.push_back(new Graph_lib::Text(Point{orig.x + i * xinterval, orig.y + 30}, ss2.str()));
        labels2[labels2.size() - 1].set_color(Color{39});
    }
    add(orig);
}

void Histogram::draw_lines() const {
    Shape::draw_lines();  // the line
    for (int i = 0; i < values.size(); ++i) {
        rects[i].draw();
        labels[i].draw();
        labels2[i].draw();
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
        Simple_window win{tl, xmax, ymax, "Histogram class"};
        win.wait_for_button();

        vector<double> value_set;  // heights
        vector<double> heights;

        string file_name = "heights-data.txt";
        ifstream ifs{file_name};
        if (!ifs) error("can't open ", file_name);
        // . . .
        for (Distribution d; ifs >> d;) {
            // basic sanity checks
            if (d.height < 20 || 250 < d.height)
                error("height out of range");
            if (d.n_people < 0)
                error("n_people cannot have negative number");
            value_set.push_back(d.n_people);
            heights.push_back(d.height);
        }

        const int num_of_values{static_cast<int>(value_set.size())};

        Point bp{xoffset, ymax - yoffset};  // base point of Histogram

        Histogram bg{bp, xlength, ylength, value_set, heights, "Histogram of heights"};
        win.attach(bg);

        vector<double> v_tmp{value_set};   // copy to v_tmp
        sort(v_tmp.begin(), v_tmp.end());  // sort in ascending order to find min and max value
        const double min_val{v_tmp[0]};
        const double max_val{v_tmp[v_tmp.size() - 1]};

        int n_value = value_set.size();
        Axis x{Axis::x, Point{xoffset, ymax - yoffset}, xlength, n_value, "height(cm)"};
        Axis y{Axis::y, Point{xoffset, ymax - yoffset}, ylength, 0, "# of people"};  // no notches for y axis
        x.label.set_font(Font::helvetica_bold);
        y.label.set_font(Font::helvetica_bold);
        x.label.move(740, 25);
        y.label.move(-40, -5);
        x.label.set_font_size(18);
        y.label.set_font_size(18);
        x.label.set_color(Color{37});
        y.label.set_color(Color{37});
        win.attach(x);
        win.attach(y);

        // adjust labels using public object (direct access and manipulate them) (p.529)
        for (int i = 0; i < value_set.size(); ++i) {
            bg.labels[i].move(75, 33);
            bg.labels[i].set_font_size(25);
            bg.labels2[i].set_font_size(20);
            bg.labels2[i].move(68, -5);
        }
        bg.labels[2].move(-6, 0);
        bg.labels[3].move(-6, 0);

        ostringstream sslab;
        sslab << "Histogram class (number of values: " << num_of_values << " )";
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