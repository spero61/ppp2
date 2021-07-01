// Rectangle point functions
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

/*
struct Rectangle : Shape {
    Rectangle(Point xy, int ww, int hh);
    Rectangle(Point x, Point y);
    void draw_lines() const;

    int height() const { return h; }
    int width() const { return w; }

private:
    int h;  // height
    int w;  // width
};
*/

Point nw(const Graph_lib::Rectangle& r) {
    return r.point(0);
}

Point n(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width() / 2, r.point(0).y};
}

Point ne(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width(), r.point(0).y};
}

Point w(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x, r.point(0).y + r.height() / 2};
}

Point center(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2};
}

Point e(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width(), r.point(0).y + r.height() / 2};
}

Point sw(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x, r.point(0).y + r.height()};
}

Point s(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height()};
}

Point se(const Graph_lib::Rectangle& r) {
    return Point{r.point(0).x + r.width(), r.point(0).y + r.height()};
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Rectangle functions"};
        win.wait_for_button();

        Graph_lib::Rectangle r{Point{100, 100}, 300, 200};
        r.set_color(Color::dark_yellow);
        win.attach(r);
        win.wait_for_button();

        Point r_nw{nw(r)};
        Point r_n{n(r)};
        Point r_ne{ne(r)};
        Point r_w{w(r)};
        Point r_center{center(r)};
        Point r_e{e(r)};
        Point r_sw{sw(r)};
        Point r_s{s(r)};
        Point r_se{se(r)};

        Graph_lib::Vector_ref<Graph_lib::Point> vp;
        vp.push_back(r_nw);
        vp.push_back(r_n);
        vp.push_back(r_ne);
        vp.push_back(r_w);
        vp.push_back(r_center);
        vp.push_back(r_e);
        vp.push_back(r_sw);
        vp.push_back(r_s);
        vp.push_back(r_se);

        vector<string> vs{"nw()", "n()", "ne()", "w()", "center()", "e()", "sw()", "s()", "se()"};

        int color_int{1};
        Graph_lib::Vector_ref<Graph_lib::Mark> vm;
        for (int i = 0; i < vp.size(); ++i) {
            vm.push_back(new Graph_lib::Mark{vp[i], 'o'});
            vm[vm.size() - 1].set_color(Color{color_int++});
            win.attach(vm[vm.size() - 1]);
            win.set_label("index[" + to_string(i) + "] : " + vs[i]);
            win.wait_for_button();
        }

        r.set_color(Color::dark_blue);
        win.set_label("nw(), n(), ne(), w(), center(), e(), sw(), s(), and se()");
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
