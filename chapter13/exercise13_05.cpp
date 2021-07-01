// Rectangle point functions applied to Circle and Ellipse
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

/*
struct Circle : Shape {
    Circle(Point p, int rr);  // center and radius
    void draw_lines() const;
    Point center() const;
    int radius() const { return r; }
    void set_radius(int rr) {
        set_point(0, Point{center().x - rr, center().y - rr});  // maintain the center
        r = rr;
    }

   private:
    int r; // radius
};

struct Ellipse : Shape {
    Ellipse(Point p, int w, int h);  // center, max and min distance from center
    void draw_lines() const;
    Point center() const;
    Point focus1() const;
    Point focus2() const;
    void set_major(int ww) {
        set_point(0, Point{center().x - ww, center().y - h});  // maintain the center
        w = ww;
    }
    int major() const { return w; }
    void set_minor(int hh) {
        set_point(0, Point{center().x - w, center().y - hh});  // maintain the center
        h = hh;
    }
    int minor() const { return h; }

   private:
    int w;
    int h;
};
*/

// Bounding rectangle Points for Circle
Point nw(const Graph_lib::Circle& c) {
    return c.point(0);
}

Point n(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius(), c.point(0).y};
}

Point ne(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius() * 2, c.point(0).y};
}

Point w(const Graph_lib::Circle& c) {
    return Point{c.point(0).x, c.point(0).y + c.radius()};
}

Point center(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius(), c.point(0).y + c.radius()};
}

Point e(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius() * 2, c.point(0).y + c.radius()};
}

Point sw(const Graph_lib::Circle& c) {
    return Point{c.point(0).x, c.point(0).y + c.radius() * 2};
}

Point s(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius(), c.point(0).y + c.radius() * 2};
}

Point se(const Graph_lib::Circle& c) {
    return Point{c.point(0).x + c.radius() * 2, c.point(0).y + c.radius() * 2};
}

// Bounding rectangle Points for Ellipse
Point nw(const Graph_lib::Ellipse& e) {
    return e.point(0);
}

Point n(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x + e.major(), e.point(0).y};
}

Point ne(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x + e.major() * 2, e.point(0).y};
}

Point w(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x, e.point(0).y + e.minor()};
}

Point center(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x + e.major(), e.point(0).y + e.minor()};
}

Point ee(const Graph_lib::Ellipse& e) {  // name of the function cannot be e, which is the same as argument name
    return Point{e.point(0).x + e.major() * 2, e.point(0).y + e.minor()};
}

Point sw(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x, e.point(0).y + e.minor() * 2};
}

Point s(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x + e.major(), e.point(0).y + e.minor() * 2};
}

Point se(const Graph_lib::Ellipse& e) {
    return Point{e.point(0).x + e.major() * 2, e.point(0).y + e.minor() * 2};
}

int main() {
    try {
        // Circle part
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Rectangle functions for Circle"};
        win.wait_for_button();

        Graph_lib::Circle c{Point{300, 200}, 150};
        c.set_color(Color::dark_green);
        win.attach(c);
        win.wait_for_button();

        Point c_nw{nw(c)};
        Point c_n{n(c)};
        Point c_ne{ne(c)};
        Point c_w{w(c)};
        Point c_center{center(c)};
        Point c_e{e(c)};
        Point c_sw{sw(c)};
        Point c_s{s(c)};
        Point c_se{se(c)};

        Graph_lib::Vector_ref<Graph_lib::Point> vp;
        vp.push_back(c_nw);
        vp.push_back(c_n);
        vp.push_back(c_ne);
        vp.push_back(c_w);
        vp.push_back(c_center);
        vp.push_back(c_e);
        vp.push_back(c_sw);
        vp.push_back(c_s);
        vp.push_back(c_se);

        vector<string> vs{"nw()", "n()", "ne()", "w()", "center()", "e()", "sw()", "s()", "se()"};

        int color_int{1};
        Graph_lib::Vector_ref<Graph_lib::Mark> vm;
        for (int i = 0; i < vp.size(); ++i) {
            vm.push_back(new Graph_lib::Mark{vp[i], 'o'});
            vm[vm.size() - 1].set_color(Color{color_int++});
            win.attach(vm[vm.size() - 1]);
            win.set_label("<Circle> index[" + to_string(i) + "] : " + vs[i]);
            win.wait_for_button();
        }

        c.set_color(Color::dark_blue);
        win.set_label("Circle: nw(), n(), ne(), w(), center(), e(), sw(), s(), and se()");
        win.wait_for_button();

        // Ellipse part
        Simple_window win2{Point{x.x + 100, x.y + 100}, 600, 400, "Rectangle functions for Ellipse"};
        win2.wait_for_button();

        Graph_lib::Ellipse e{Point{300, 200}, 150, 100};
        e.set_color(Color::dark_green);
        win2.attach(e);
        win2.wait_for_button();

        Point e_nw{nw(e)};
        Point e_n{n(e)};
        Point e_ne{ne(e)};
        Point e_w{w(e)};
        Point e_center{center(e)};
        Point e_e{ee(e)};  // e(e) occurs an error
        Point e_sw{sw(e)};
        Point e_s{s(e)};
        Point e_se{se(e)};

        Graph_lib::Vector_ref<Graph_lib::Point> vp2;
        vp2.push_back(e_nw);
        vp2.push_back(e_n);
        vp2.push_back(e_ne);
        vp2.push_back(e_w);
        vp2.push_back(e_center);
        vp2.push_back(e_e);
        vp2.push_back(e_sw);
        vp2.push_back(e_s);
        vp2.push_back(e_se);

        color_int = 1;
        Graph_lib::Vector_ref<Graph_lib::Mark> vm2;
        for (int i = 0; i < vp2.size(); ++i) {
            vm2.push_back(new Graph_lib::Mark{vp2[i], 'o'});
            vm2[vm2.size() - 1].set_color(Color{color_int++});
            win2.attach(vm2[vm2.size() - 1]);
            win2.set_label("<Ellipse> index[" + to_string(i) + "] : " + vs[i]);
            win2.wait_for_button();
        }

        e.set_color(Color::dark_blue);
        win2.set_label("Ellipse: nw(), n(), ne(), w(), center(), e(), sw(), s(), and se()");
        win2.wait_for_button();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
