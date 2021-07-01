// Poly class
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

struct Poly : Polygon {  // closed sequence of non-intersecting lines
    using Polygon::Polygon;
    Poly(vector<Point> vp_arg);
    void add(Point p);
    void draw_lines() const;

   private:
    vector<Point> vp;
};

Poly::Poly(vector<Point> vp_arg) : vp{vp_arg} {
    for (int i = 0; i < vp.size(); ++i) {
        add(vp[i]);
    }
}

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) {
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    if (denom == 0) {
        parallel = true;
        return pair<double, double>(0, 0);
    }
    parallel = false;
    return pair<double, double>(((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
                                ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom);
}

//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection) {
    bool parallel;
    pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
    if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
    intersection.x = p1.x + u.first * (p2.x - p1.x);
    intersection.y = p1.y + u.first * (p2.y - p1.y);
    return true;
}

void Poly::add(Point p) {
    int np = number_of_points();

    if (1 < np) {  // check that the new line isn't parallel to the previous one
        if (p == point(np - 1)) error("polygon point equal to previous point");
        bool parallel;
        line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
        if (parallel)
            error("two polygon points lie in a straight line");
    }

    for (int i = 1; i < np - 1; ++i) {  // check that new segment doesn't intersect and old point
        Point ignore(0, 0);
        if (line_segment_intersect(point(np - 1), p, point(i - 1), point(i), ignore))
            error("intersect in polygon");
    }

    Polygon::add(p);
}

void Poly::draw_lines() const {
    if (number_of_points() < 3) error("less than 3 points in a Polygon");
    Closed_polyline::draw_lines();
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 600, 400, "Polygon: heart"};
        win.wait_for_button();

        Point p{300, 140};
        const int m{10};  //  (size) multiplier

        vector<Point> vp;
        vp.push_back(Point{p.x, p.y});                  // top_center
        vp.push_back(Point{p.x + 2 * m, p.y - 2 * m});  // rhs point 01
        vp.push_back(Point{p.x + 5 * m, p.y - 3 * m});  // rhs point 02
        vp.push_back(Point{p.x + 6 * m, p.y - 1 * m});  // rhs point 03
        vp.push_back(Point{p.x + 4 * m, p.y + 4 * m});  // rhs point 04
        vp.push_back(Point{p.x, p.y + 7 * m});          // bottom_center
        vp.push_back(Point{p.x - 4 * m, p.y + 4 * m});  // lhs point 04
        vp.push_back(Point{p.x - 6 * m, p.y - 1 * m});  // lhs point 03
        vp.push_back(Point{p.x - 5 * m, p.y - 3 * m});  // lhs point 02
        vp.push_back(Point{p.x - 2 * m, p.y - 2 * m});  // lhs point 01

        Poly heart{vp};
        win.attach(heart);

        heart.set_style(Line_style{Line_style::solid, 3});
        heart.set_color(Color{129});
        win.wait_for_button();
        heart.set_fill_color(Color{129});
        win.wait_for_button();

        //// This is not a polygon
        //vector<Point> napoly;
        //napoly.push_back(Point{ 0, 0 });
        //napoly.push_back(Point{ 200, 0 });
        //napoly.push_back(Point{ 200, 200 });
        //napoly.push_back(Point{ 100, 100 });
        //napoly.push_back(Point{ 300, 150 }); // Poly's constructor would not accept this point

        //Poly not_poly{ napoly };
        //win.attach(not_poly);
        //not_poly.set_color(Color::blue);
        //not_poly.set_fill_color(Color::yellow);
        //win.wait_for_button();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}