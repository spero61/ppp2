// Class Diagram using Box(13_02) and Arrow(13_03)
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Box : Shape {
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
        Simple_window win{x, 800, 400, "#12.6 class diagram of 'Shape'"};
        win.wait_for_button();

        Graph_lib::Vector_ref<Box> vb;

        Box box_window{Point{190, 50}, 105, "Window"};
        Box box_line_style{Point{320, 50}, 128, "Line_style"};
        Box box_color{Point{475, 50}, 80, "Color"};

        Box box_simple_window{Point{150, 150}, 175, "Simple_window"};
        Box box_shape{Point{360, 120}, 90, "Shape"};
        Box box_point{Point{500, 150}, 80, "Point"};

        const int axis_x{370};
        const int axis_y{300};
        Box box_line{Point{axis_x - 110 - 85 - 70, axis_y}, 65, "Line"};
        Box box_lines{Point{axis_x - 110 - 85, axis_y}, 80, "Lines"};
        Box box_polygon{Point{axis_x - 110, axis_y}, 105, "Polygon"};
        Box box_axis{Point{axis_x, axis_y}, 65, "Axis"};
        Box box_rectangle{Point{axis_x + 70, axis_y}, 120, "Rectangle"};
        Box box_text{Point{axis_x + 70 + 125, axis_y}, 70, "Text"};
        Box box_image{Point{axis_x + 70 + 125 + 75, axis_y}, 85, "Image"};

        vb.push_back(box_window);
        vb.push_back(box_line_style);
        vb.push_back(box_color);

        vb.push_back(box_simple_window);
        vb.push_back(box_shape);
        vb.push_back(box_point);

        vb.push_back(box_line);
        vb.push_back(box_lines);
        vb.push_back(box_polygon);
        vb.push_back(box_axis);
        vb.push_back(box_rectangle);
        vb.push_back(box_text);
        vb.push_back(box_image);

        for (int i = 0; i < vb.size(); ++i) {
            vb[i].set_fill_color(Color{14});
            win.attach(vb[i]);
        }

        Graph_lib::Vector_ref<Arrow> va;

        // Arrow arrow { Point p1, Point p2, bool p1_arrow, bool p2_arrow, int size_of_an_arrow(dd)};
        Arrow arrow01{s(box_window), Point{s(box_window).x, n(box_simple_window).y}, true, false, 7};

        Point shape_s{s(box_shape)};
        Arrow arrow02{shape_s, Point{shape_s.x, n(box_axis).y}, true, false, 7};
        Arrow arrow03{Point{shape_s.x - 8 * 3, shape_s.y}, n(box_line), true, false, 7};
        Arrow arrow04{Point{shape_s.x - 8 * 2, shape_s.y}, n(box_lines), true, false, 7};
        Arrow arrow05{Point{shape_s.x - 8, shape_s.y}, n(box_polygon), true, false, 7};
        Arrow arrow06{Point{shape_s.x + 8, shape_s.y}, n(box_rectangle), true, false, 7};
        Arrow arrow07{Point{shape_s.x + 8 * 2, shape_s.y}, n(box_text), true, false, 7};
        Arrow arrow08{Point{shape_s.x + 8 * 3, shape_s.y}, n(box_image), true, false, 7};

        va.push_back(arrow01);
        va.push_back(arrow02);
        va.push_back(arrow03);
        va.push_back(arrow04);
        va.push_back(arrow05);
        va.push_back(arrow06);
        va.push_back(arrow07);
        va.push_back(arrow08);

        for (int i = 0; i < va.size(); ++i) {
            va[i].set_style(Line_style{Line_style::solid, 2});
            va[i].set_fill_color(Color::black);
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
