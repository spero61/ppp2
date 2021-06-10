#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        const int body_top{400};

        Point tl{100, 100};
        Simple_window win{tl, 1200, 800, "adjust the window size then click next"};
        win.wait_for_button();

        Graph_lib::Rectangle body{Point{400, body_top}, 400, 300};  // top left corner, width, height
        body.set_fill_color(Color::dark_blue);
        win.attach(body);

        Closed_polyline roof;
        roof.add(Point{300, body_top});
        roof.add(Point{340, body_top - 40});
        roof.add(Point{600, body_top - 120});  // 600 is body midpoint x
        roof.add(Point{840, body_top - 40});
        roof.add(Point{900, body_top});
        roof.set_fill_color(Color::dark_cyan);
        win.attach(roof);

        Closed_polyline chimney;
        chimney.add(Point{700, body_top - 87});
        chimney.add(Point{700, body_top - 180});
        chimney.add(Point{800, body_top - 180});
        chimney.add(Point{800, body_top - 54});
        chimney.set_fill_color(Color::dark_yellow);
        win.attach(chimney);

        Closed_polyline door;
        door.add(Point{650, body_top + 50});
        door.add(Point{750, body_top + 50});
        door.add(Point{750, body_top + 250});
        door.add(Point{650, body_top + 250});
        door.set_fill_color(Color::dark_magenta);
        win.attach(door);

        Graph_lib::Circle handle{Point{680, body_top + 150}, 7};
        handle.set_fill_color(Color::yellow);
        win.attach(handle);

        Graph_lib::Circle window_one{Point{470, body_top + 75}, 45};
        window_one.set_fill_color(Color::cyan);
        win.attach(window_one);

        Graph_lib::Circle window_two{Point{575, body_top + 75}, 45};
        window_two.set_fill_color(Color::cyan);
        win.attach(window_two);

        Open_polyline frame_one_x;
        frame_one_x.add(Point(425, body_top + 75));
        frame_one_x.add(Point(515, body_top + 75));
        frame_one_x.set_style(Line_style(Line_style::solid, 5));
        frame_one_x.set_color(Color::dark_blue);
        win.attach(frame_one_x);

        Open_polyline frame_one_y;
        frame_one_y.add(Point(470, body_top + 30));
        frame_one_y.add(Point(470, body_top + 120));
        frame_one_y.set_style(Line_style(Line_style::solid, 5));
        frame_one_y.set_color(Color::dark_blue);
        win.attach(frame_one_y);

        Open_polyline frame_two_x;
        frame_two_x.add(Point(530, body_top + 75));
        frame_two_x.add(Point(620, body_top + 75));
        frame_two_x.set_style(Line_style(Line_style::solid, 5));
        frame_two_x.set_color(Color::dark_blue);
        win.attach(frame_two_x);

        Open_polyline frame_two_y;
        frame_two_y.add(Point(575, body_top + 30));
        frame_two_y.add(Point(575, body_top + 120));
        frame_two_y.set_style(Line_style(Line_style::solid, 5));
        frame_two_y.set_color(Color::dark_blue);
        win.attach(frame_two_y);

        Graph_lib::Ellipse cloud_one{Point{680, body_top - 250}, 70, 30};
        cloud_one.set_fill_color(Color::white);
        win.attach(cloud_one);

        Graph_lib::Ellipse cloud_two{Point{570, body_top - 300}, 50, 25};
        cloud_two.set_fill_color(Color::white);
        win.attach(cloud_two);

        Graph_lib::Ellipse cloud_three{Point{500, body_top - 350}, 30, 15};
        cloud_three.set_fill_color(Color::white);
        win.attach(cloud_three);

        ostringstream oss;
        oss << "screen size: " << x_max() << "*" << y_max()
            << "; window size: " << win.x_max() << "*" << win.y_max();
        Text sizes{Point{30, 30}, oss.str()};
        sizes.set_font(Font::helvetica_bold);
        sizes.set_font_size(20);
        win.attach(sizes);

        win.set_label("Ch12 Exercise07");
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