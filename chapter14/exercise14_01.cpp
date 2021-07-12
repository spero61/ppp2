// Define two classes Smiley and Frowny, which are both derived from class Circle and have two eyes and a mouth.
// Next, derive classes from Smiley and Frowny which add an appropriate hat to each.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Ellipse_Arc : Shape {
    Ellipse_Arc(Point p, int ww, int hh, int start, int end)
        : w{ww}, h{hh}, a{start}, b{end} {
        add(Point{p.x - ww, p.y - hh});
    }

    void draw_lines() const override;

    Point center() const { return {point(0).x + w, point(0).y + h}; }
    Point focus1() const { return {center().x + int(sqrt(double(w * w - h * h))), center().y}; }
    Point focus2() const { return {center().x - int(sqrt(double(w * w - h * h))), center().y}; }

    void set_major(int ww) { w = ww; }
    int major() const { return w; }
    void set_minor(int hh) { h = hh; }
    int minor() const { return h; }

   private:
    int w;  // the distance from the center to a point on the x axis
    int h;  // the distance from the center to a point on the y axis
    int a;  // start point between 0 and 360
    int b;  // end point between 0 and 360
};

void Ellipse_Arc::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, a, b);
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, w + w, h + h, a, b);
    }
}

class Smiley : public Graph_lib::Circle {
   public:
    Smiley(Point p, int rr);  // center and radius
    void draw_lines() const override;
    Point center() const { return {point(0).x + r, point(0).y + r}; }
    int radius() const { return r; }

   private:
    int r;  // radius
    int adjust_p{static_cast<int>(r * 0.3)};
    int adjust_r{static_cast<int>(r * 0.15)};
    Graph_lib::Ellipse left_eye;
    Graph_lib::Ellipse right_eye;
    Ellipse_Arc mouth;
};

Smiley::Smiley(Point p, int rr)  // center and radius
    : r{rr},
      left_eye{Point{p.x - adjust_p, p.y - adjust_p}, adjust_r, adjust_r * 2},
      right_eye{Point{p.x + adjust_p, p.y - adjust_p}, adjust_r, adjust_r * 2},
      mouth{Point{p.x, p.y + adjust_p}, adjust_r * 3, adjust_r * 3, 225, 315} {
    add(Point{p.x - r, p.y - r});
}

void Smiley::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
    }

    // Circle::draw_lines(); // REVIEW: did not work, because class Circle is in different file
    left_eye.draw();
    right_eye.draw();
    mouth.draw();
}

class Frowny : public Graph_lib::Circle {
   public:
    Frowny(Point p, int rr);  // center and radius
    void draw_lines() const override;
    Point center() const { return {point(0).x + r, point(0).y + r}; }
    int radius() const { return r; }

   private:
    int r;  // radius
    int adjust_p{static_cast<int>(r * 0.3)};
    int adjust_r{static_cast<int>(r * 0.15)};
    Graph_lib::Ellipse left_eye;
    Graph_lib::Ellipse right_eye;
    Ellipse_Arc mouth;
};

Frowny::Frowny(Point p, int rr)  // center and radius
    : r{rr},
      left_eye{Point{p.x - adjust_p, p.y - adjust_p}, adjust_r, adjust_r * 2},
      right_eye{Point{p.x + adjust_p, p.y - adjust_p}, adjust_r, adjust_r * 2},
      mouth{Point{p.x, p.y + adjust_p * 3}, adjust_r * 3, adjust_r * 3, 45, 135} {
    add(Point{p.x - r, p.y - r});
}

void Frowny::draw_lines() const {
    if (fill_color().visibility()) {  // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
    }

    // Circle::draw_lines();  // REVIEW: did not work, because class Circle is in different file
    left_eye.draw();
    right_eye.draw();
    mouth.draw();
}

class Smiley_hat : public Smiley {
   public:
    using Smiley::Smiley;
    void draw_lines() const override;
};

void Smiley_hat::draw_lines() const {
    Smiley::draw_lines();

    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i) {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());  // reset color
    }

    Point c{center()};
    const int r{radius()};

    if (color().visibility()) {
        // bottom line of the hat
        fl_line(c.x - r * 2, c.y - r, c.x + r * 2, c.y - r);

        // left side of the hat
        fl_line(c.x - r * 2, c.y - r, c.x - r * 2, c.y - r - r * 0.5);
        fl_line(c.x - r * 2, c.y - r - r * 0.5, c.x - r * 2 + r, c.y - r - r * 0.5);
        fl_line(c.x - r * 2 + r, c.y - r - r * 0.5, c.x - r * 2 + r, c.y - r - r * 1.5);

        // right side of the hat
        fl_line(c.x + r * 2, c.y - r, c.x + r * 2, c.y - r - r * 0.5);
        fl_line(c.x + r * 2, c.y - r - r * 0.5, c.x + r * 2 - r, c.y - r - r * 0.5);
        fl_line(c.x + r * 2 - r, c.y - r - r * 0.5, c.x + r * 2 - r, c.y - r - r * 1.5);

        // top line of the hat
        fl_line(c.x - r * 2 + r, c.y - r - r * 1.5, c.x + r * 2 - r, c.y - r - r * 1.5);
    }
}

class Frowny_hat : public Frowny {
   public:
    using Frowny::Frowny;
    void draw_lines() const override;
};

void Frowny_hat::draw_lines() const {
    Frowny::draw_lines();

    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i) {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());  // reset color
    }

    Point c{center()};
    const int r{radius()};

    if (color().visibility()) {
        // bottom line of the hat
        fl_line(c.x - r * 2, c.y - r, c.x + r * 2, c.y - r);

        // left side of the hat
        fl_line(c.x - r * 2, c.y - r, c.x - r * 2, c.y - r - r * 0.5);
        fl_line(c.x - r * 2, c.y - r - r * 0.5, c.x - r * 2 + r, c.y - r - r * 0.5);
        fl_line(c.x - r * 2 + r, c.y - r - r * 0.5, c.x - r * 2 + r, c.y - r - r * 1.5);

        // right side of the hat
        fl_line(c.x + r * 2, c.y - r, c.x + r * 2, c.y - r - r * 0.5);
        fl_line(c.x + r * 2, c.y - r - r * 0.5, c.x + r * 2 - r, c.y - r - r * 0.5);
        fl_line(c.x + r * 2 - r, c.y - r - r * 0.5, c.x + r * 2 - r, c.y - r - r * 1.5);

        // top line of the hat
        fl_line(c.x - r * 2 + r, c.y - r - r * 1.5, c.x + r * 2 - r, c.y - r - r * 1.5);
    }
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Smiley and Frowny"};
        win.wait_for_button();

        const int radius{70};

        Smiley happy = {Point{200, 150}, radius};
        Frowny unhappy = {Point{550, 150}, radius};

        win.attach(happy);
        win.attach(unhappy);
        win.wait_for_button();

        Smiley_hat happy_hat = {Point{200, 450}, radius};
        Frowny_hat unhappy_hat = {Point{550, 450}, radius};

        win.attach(happy_hat);
        win.attach(unhappy_hat);
        win.set_label("Smiley and Frowny (w/ and w/o hat)");
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