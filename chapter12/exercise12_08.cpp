#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        constexpr int x_start{280};
        constexpr int y_start{400};
        constexpr int x_interval{300};
        constexpr int y_interval{130};
        constexpr int ring_size{135};
        constexpr int ring_thickness{20};

        const int x_half_interval{x_interval / 2};  // this must be int

        Point tl{100, 100};
        Simple_window win{tl, 1200, 800, "adjust the window size then click next"};
        win.wait_for_button();

        Graph_lib::Circle ring_europe{Point{x_start, y_start}, ring_size};
        ring_europe.set_color(Color::blue);
        ring_europe.set_style(Line_style(Line_style::solid, ring_thickness));
        win.attach(ring_europe);

        Graph_lib::Circle ring_africa{Point{x_start + x_interval, y_start}, ring_size};
        ring_africa.set_color(Color::black);
        ring_africa.set_style(Line_style(Line_style::solid, ring_thickness));
        win.attach(ring_africa);

        Graph_lib::Circle ring_america{Point{x_start + (2 * x_interval), y_start}, ring_size};
        ring_america.set_color(Color::red);
        ring_america.set_style(Line_style(Line_style::solid, ring_thickness));
        win.attach(ring_america);

        Graph_lib::Circle ring_asia{Point{x_start + x_half_interval, y_start + y_interval}, ring_size};
        ring_asia.set_color(Color::yellow);
        ring_asia.set_style(Line_style(Line_style::solid, ring_thickness));
        win.attach(ring_asia);

        Graph_lib::Circle ring_oceania{Point{x_start + x_half_interval + x_interval, y_start + y_interval}, ring_size};
        ring_oceania.set_color(Color::green);
        ring_oceania.set_style(Line_style(Line_style::solid, ring_thickness));
        win.attach(ring_oceania);

        Text title{Point{x_start + 125, y_start - 225}, "TOKYO 2020"};  // It's in 2021 though.
        title.set_font(Font::helvetica_bold);
        title.set_font_size(61);
        title.set_color(Color::dark_blue);
        win.attach(title);

        ostringstream oss;
        oss << "screen size: " << x_max() << "*" << y_max()
            << "; window size: " << win.x_max() << "*" << win.y_max();
        Text sizes{Point{30, 30}, oss.str()};
        sizes.set_font(Font::helvetica_bold);
        sizes.set_font_size(20);
        win.attach(sizes);

        win.set_label("Ch12 Exercise08");
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