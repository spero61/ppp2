// The exceptions defined in the C++ standard library, such as exception, runtime_error,
// and out_of_range (§5.6.3), are organized into a class hierarchy
// (with a useful virtual function what() returning a string supposedly explaining what went wrong).
// Search your information sources for the C++ standard exception class hierarchy
// and draw a class hierarchy diagram of it.

// I used the source as below
// https://stdcxx.apache.org/doc/stdlibug/18-2.html#:~:text=18.2%20The%20Standard%20Exception%20Hierarchy,exceptions%20from%20your%20own%20code.
// because as of now (July 11th, 2021), exception class is way more complicated
// https://en.cppreference.com/w/cpp/error/exception

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// class definition from exercise13_06.cpp
class Box : public Shape {
   public:
    Box(Point xy, int ww, int hh, int rr);             // without a text label
    Box(Point xy, int ww, int hh, int rr, string tt);  // with a text label
    Box(Point xy, int ww, string tt);                  // constructor for box with a text label (default value: height: 35, radius: 12, font size: 20)
    void draw_lines() const;
    int height() const { return h; }
    int width() const { return w; }
    int radius() const { return r; }

    string text() const { return t; }
    void set_font(Font f) { fnt = f; }
    void set_font_size(int s) { fnt_sz = s; }
    int font_size() const { return fnt_sz; }

   private:
    int h;  // height
    int w;  // width
    int r;  // radius

    string t;
    Font fnt{fl_font()};
    int fnt_sz{(14 < fl_size()) ? fl_size() : 14};  // at least 14 point
};

Box::Box(Point xy, int ww, int hh, int rr) : w{ww}, h{hh}, r{rr} {
    if (h <= 0 || w <= 0)
        error("Bad Box: non-positive side");
    if (r <= 0)
        error("Bad Box: radius should have positive value");
    add(xy);
}

Box::Box(Point xy, int ww, int hh, int rr, string tt) : w{ww}, h{hh}, r{rr}, t{tt} {
    if (h <= 0 || w <= 0)
        error("Bad Box: non-positive side");
    if (r <= 0)
        error("Bad Box: radius should have positive value");
    add(xy);
}

Box::Box(Point xy, int ww, string tt) : w{ww}, h{35}, r{12}, t{tt}, fnt{Font::helvetica_bold}, fnt_sz{20} {
    // w=  static_cast<int>(tt.size() * 12 + 25); // this does not fit well, because width of English characters are not identical.
    if (h <= 0 || w <= 0)
        error("Bad Box: non-positive side");
    if (r <= 0)
        error("Bad Box: radius should have positive value");
    add(xy);
}

void Box::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y + r, w, h - r * 2);                              // horizontal
        fl_rectf(point(0).x + r, point(0).y, w - r * 2, h);                              // vertical
        fl_pie(point(0).x, point(0).y, r + r, r + r, 90, 180);                           // top-left corner
        fl_pie(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);                 // top-right corner
        fl_pie(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);              // bottom-left corner
        fl_pie(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);  // bottom-right corner
        fl_color(color().as_int());                                                      // reset color
    }

    if (color().visibility()) {  // edge on top of fill
        fl_color(color().as_int());
        // four sides
        fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);          // side: top
        fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);  // side: down
        fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);          // side: left
        fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);  // side: right

        // four arcs
        fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);                           // top-left corner
        fl_arc(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);                 // top-right corner
        fl_arc(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);              // bottom-left corner
        fl_arc(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);  // bottom-right corner

        // this coefficient is valid where the box has height of 50 pixel and font size equals 20
        const double y_coef{0.3};  // adjustment coefficient for center the text vertically.
        const int x_indent{15};    // x_indentation a text label in the box
        int ofnt = fl_font();
        int osz = fl_size();

        fl_font(fnt.as_int(), fnt_sz);
        fl_draw(t.c_str(), point(0).x + x_indent, point(0).y + height() / 2 + y_coef * font_size());  // center the text horizontally as well as vertically
        fl_font(ofnt, osz);
    }
}

constexpr double PI{3.14159265358979};

struct Arrow : Shape {
    Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd);
    void draw_lines() const;

   private:
    int d;        // size of an arrow
    bool p1_arw;  // is arrow at p1
    bool p2_arw;  // is arrow at p2
};

Arrow::Arrow(Point p1, Point p2, bool p1_arrow, bool p2_arrow, int dd) : p1_arw{p1_arrow}, p2_arw{p2_arrow}, d{dd} {
    if (d <= 0)
        error("Bad Arrow: size of a triangle should have positive value");
    add(p1);
    add(p2);
}

void Arrow::draw_lines() const {
    const double arrow_angle{PI / 6.0};  // 30 degrees

    if (color().visibility()) {
        fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

        int dy{point(1).y - point(0).y};
        int dx{point(1).x - point(0).x};
        double angle{atan2(dy, dx)};  // https://en.cppreference.com/w/c/numeric/math/atan2

        // fl_line: https://www.fltk.org/doc-1.3/group__fl__drawings.html#gaecc374f163a97ef67c4e58be11c47047
        if (p1_arw) {
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle + arrow_angle), point(0).y + d * sin(angle + arrow_angle));
            fl_line(point(0).x, point(0).y, point(0).x + d * cos(angle - arrow_angle), point(0).y + d * sin(angle - arrow_angle));
        }
        if (p2_arw) {
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle + arrow_angle), point(1).y - d * sin(angle + arrow_angle));
            fl_line(point(1).x, point(1).y, point(1).x - d * cos(angle - arrow_angle), point(1).y - d * sin(angle - arrow_angle));
        }
    }
}

Point n(const Box& b) {
    return Point{b.point(0).x + b.width() / 2, b.point(0).y};
}

Point s(const Box& b) {
    return Point{b.point(0).x + b.width() / 2, b.point(0).y + b.height()};
}

int main() {
    try {
        const int height{35};
        const int radius{10};

        const Point x{100, 100};
        Simple_window win{x, 1000, 450, "class diagram of 'exception'"};
        win.wait_for_button();

        Graph_lib::Vector_ref<Box> vb;

        // top layer
        Box box_exception{Point{440, 25}, 120, "exception"};
        // middle layer
        Box box_logic_err{Point{235, 150}, 130, "logic_error"};
        Box box_runtime_err{Point{620, 150}, 160, "runtime_error"};
        // bottom layer
        Box box_domain_err{Point{20, 250}, 160, "domain_error"};
        Box box_invalid_err{Point{100, 350}, 150, "invalid_error"};
        Box box_length_err{Point{280, 350}, 145, "length_error"};
        Box box_out_of_range_err{Point{350, 250}, 155, "out_of_range"};

        Box box_range_err{Point{550, 290}, 140, "range_error"};
        Box box_overflow_err{Point{650, 380}, 170, "overflow_error"};
        Box box_underflow_err{Point{780, 290}, 180, "underflow_error"};

        vb.push_back(box_exception);
        vb.push_back(box_logic_err);
        vb.push_back(box_runtime_err);
        vb.push_back(box_domain_err);
        vb.push_back(box_invalid_err);
        vb.push_back(box_length_err);
        vb.push_back(box_out_of_range_err);
        vb.push_back(box_range_err);
        vb.push_back(box_overflow_err);
        vb.push_back(box_underflow_err);

        for (int i = 0; i < vb.size(); ++i) {
            vb[i].set_fill_color(Color{16 * 13 + 5});
            win.attach(vb[i]);
        }

        Arrow mid01_top{s(box_exception), n(box_logic_err), true, false, 7};
        Arrow mid02_top{s(box_exception), n(box_runtime_err), true, false, 7};

        Point mid01{s(box_logic_err)};
        Arrow bot01_mid01{n(box_domain_err), Point{mid01.x - 6, mid01.y + 2}, false, true, 6};
        Arrow bot02_mid01{n(box_invalid_err), Point{mid01.x - 2, mid01.y + 1}, false, true, 6};
        Arrow bot03_mid01{n(box_length_err), Point{mid01.x + 2, mid01.y + 1}, false, true, 6};
        Arrow bot04_mid01{n(box_out_of_range_err), Point{mid01.x + 6, mid01.y + 2}, false, true, 6};

        Point mid02{s(box_runtime_err)};
        Arrow bot05_mid02{n(box_range_err), Point{mid02.x - 4, mid02.y + 2}, false, true, 8};
        Arrow bot06_mid02{n(box_overflow_err), mid02, false, true, 8};
        Arrow bot07_mid02{n(box_underflow_err), Point{mid02.x + 4, mid02.y + 2}, false, true, 8};

        Graph_lib::Vector_ref<Arrow> va;

        va.push_back(mid01_top);
        va.push_back(mid02_top);
        va.push_back(bot01_mid01);
        va.push_back(bot02_mid01);
        va.push_back(bot03_mid01);
        va.push_back(bot04_mid01);
        va.push_back(bot05_mid02);
        va.push_back(bot06_mid02);
        va.push_back(bot07_mid02);

        for (int i = 0; i < va.size(); ++i) {
            va[i].set_style(Line_style{Line_style::solid, 2});
            va[i].set_color(Color{16 * 11 + 4});
            win.attach(va[i]);
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
