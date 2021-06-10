#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

vector<Point> superellipse_point(double a, double b, double m, double n, int N, Point center) {
    vector<Point> points;

    // + part
    for (int x = -N; x <= N; x++) {
        int y = b * pow(1 - pow(abs(x / a), m), 1 / n);
        points.push_back(Point{x + center.x, y + center.y});
    }

    // - part
    for (int x = N; x >= -N; x--) {
        int y = -b * pow(1 - pow(abs(x / a), m), 1 / n);
        points.push_back(Point{x + center.x, y + center.y});
    }

    return points;
}

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();

        win.set_label("Ch12 Exercise12");

        const Point center(win.x_max() / 2, win.y_max() / 2);
        constexpr int N{200};
        constexpr int a{N};
        constexpr int b{N - 70};

        double m_n{5};
        win.set_label("Ch12 Exercise12 (m = n = 5)");
        vector<Point> points_01;
        Graph_lib::Open_polyline superellipse_01;  //
        superellipse_01.set_color(Color::dark_magenta);
        points_01 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_01) {
            superellipse_01.add(p);
        }
        win.attach(superellipse_01);

        Text text_01{Point{50, 100}, "m = n = 5"};
        text_01.set_color(Color::dark_magenta);
        text_01.set_font_size(20);
        text_01.set_font(Font::helvetica_bold);
        win.attach(text_01);

        win.wait_for_button();

        m_n = 3;
        win.set_label("Ch12 Exercise12 (m = n = 3)");
        vector<Point> points_02;
        Graph_lib::Open_polyline superellipse_02;
        superellipse_02.set_color(Color::dark_blue);
        points_02 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_02) {
            superellipse_02.add(p);
        }
        win.attach(superellipse_02);

        Text text_02{Point{50, 150}, "m = n = 3"};
        text_02.set_color(Color::dark_blue);
        text_02.set_font_size(20);
        text_02.set_font(Font::helvetica_bold);
        win.attach(text_02);

        win.wait_for_button();

        m_n = 2;
        win.set_label("Ch12 Exercise12 (m = n = 2)");
        vector<Point> points_03;
        Graph_lib::Open_polyline superellipse_03;
        superellipse_03.set_color(Color::dark_yellow);
        points_03 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_03) {
            superellipse_03.add(p);
        }
        win.attach(superellipse_03);

        Text text_03{Point{50, 200}, "m = n = 2"};
        text_03.set_color(Color::dark_yellow);
        text_03.set_font_size(20);
        text_03.set_font(Font::helvetica_bold);
        win.attach(text_03);

        win.wait_for_button();

        m_n = 1.5;
        win.set_label("Ch12 Exercise12 (m = n = 1.5)");
        vector<Point> points_04;
        Graph_lib::Open_polyline superellipse_04;
        superellipse_04.set_color(Color::dark_green);
        points_04 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_04) {
            superellipse_04.add(p);
        }
        win.attach(superellipse_04);

        Text text_04{Point{50, 250}, "m = n = 1.5"};
        text_04.set_color(Color::dark_green);
        text_04.set_font_size(20);
        text_04.set_font(Font::helvetica_bold);
        win.attach(text_04);

        win.wait_for_button();

        m_n = 1;
        win.set_label("Ch12 Exercise12 (m = n = 1)");
        vector<Point> points_05;
        Graph_lib::Open_polyline superellipse_05;
        superellipse_05.set_color(Color::cyan);
        points_05 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_05) {
            superellipse_05.add(p);
        }
        win.attach(superellipse_05);

        Text text_05{Point{50, 300}, "m = n = 1"};
        text_05.set_color(Color::cyan);
        text_05.set_font_size(20);
        text_05.set_font(Font::helvetica_bold);
        win.attach(text_05);

        win.wait_for_button();

        m_n = 0.7;
        win.set_label("Ch12 Exercise12 (m = n = 0.7)");
        vector<Point> points_06;
        Graph_lib::Open_polyline superellipse_06;
        superellipse_06.set_color(Color::yellow);
        points_06 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_06) {
            superellipse_06.add(p);
        }
        win.attach(superellipse_06);

        Text text_06{Point{50, 350}, "m = n = 0.7"};
        text_06.set_color(Color::yellow);
        text_06.set_font_size(20);
        text_06.set_font(Font::helvetica_bold);
        win.attach(text_06);

        win.wait_for_button();

        m_n = 0.5;
        win.set_label("Ch12 Exercise12 (m = n = 0.5)");
        vector<Point> points_07;
        Graph_lib::Open_polyline superellipse_07;
        superellipse_07.set_color(Color::red);
        points_07 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_07) {
            superellipse_07.add(p);
        }
        win.attach(superellipse_07);

        Text text_07{Point{50, 400}, "m = n = 0.5"};
        text_07.set_color(Color::red);
        text_07.set_font_size(20);
        text_07.set_font(Font::helvetica_bold);
        win.attach(text_07);

        win.wait_for_button();

        m_n = 0.3;
        win.set_label("Ch12 Exercise12 (m = n = 0.3)");
        vector<Point> points_08;
        Graph_lib::Open_polyline superellipse_08;
        superellipse_08.set_color(Color::green);
        points_08 = superellipse_point(a, b, m_n, m_n, N, center);  // a, b, m, n, N
        for (Point p : points_08) {
            superellipse_08.add(p);
        }
        win.attach(superellipse_08);

        Text text_08{Point{50, 450}, "m = n = 0.3"};
        text_08.set_color(Color::green);
        text_08.set_font_size(20);
        text_08.set_font(Font::helvetica_bold);
        win.attach(text_08);

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