// Make an "analog clock."
//
// A major part of this exercise is to find the functions
// that give you the time of day and a way of waiting for a short period of time
// and to learn to use them based on the documentation you found.

#define _CRT_SECURE_NO_WARNINGS  // to disable deprecation warning of the Visual Studio 2019

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// #include <chrono>
// #include <thread>

constexpr double PI{3.14159265358979};

class Clock_window : public Window  // Lines_window inherits from Window
{
   public:
    Clock_window(Point xy, int w, int h, const string& title, Point center, int radius);  // declare constructor

    Point center() { return c; }
    int radius() { return r; }

   private:
    // data:
    Point c;  // center
    int r;    // radius
    Circle frame;
    Vector_ref<Graph_lib::Line> second_lines;  // to depict marks for every seconds and minutes
    Vector_ref<Graph_lib::Line> hour_lines;    // to depict marks for every hour
    Vector_ref<Graph_lib::Text> hour_labels;   // labels for numerals
    // widgets:
    Button draw_button;  // draw analog clock
    Button quit_button;  // end program

    void draw_clock_base();  // draw clock base(frame, second_lines, hour_lines, and hour_labels)
    void quit() { hide(); }  // curious FLTK idiom to delete window
};

Clock_window::Clock_window(Point xy, int w, int h, const string& title, Point center, int radius)
    : Window{xy, w, h, title}, c{center}, r{radius}, frame{c, r},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      draw_button{Point{x_max() - 150, 0}, 70, 20, "Draw", [](Address, Address pw) { reference_to<Clock_window>(pw).draw_clock_base(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Clock_window>(pw).quit(); }} {
    attach(draw_button);
    attach(quit_button);
}

void Clock_window::draw_clock_base() {
    if (r < 100) {
        error("error: radius for frame is too small.\nProvide the radius greater than or equal to 100");
    }
    frame.set_style(Line_style{Line_style::solid, 5});
    frame.set_color(Color{8});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
    frame.set_fill_color(Color::black);
    attach(frame);

    for (int i = 0; i < 60; ++i)  // seconds or minutes
    {
        const int d1{static_cast<int>(r * 0.95)};                            // distance from the center of a circle
        const int x1{static_cast<int>(c.x + d1 * sin(6 * i * PI / 180.0))};  // degrees: 6 * i
        const int y1{static_cast<int>(c.y - d1 * cos(6 * i * PI / 180.0))};

        const int d2{r};
        const int x2{static_cast<int>(c.x + d2 * sin(6 * i * PI / 180.0))};  // degrees: 6 * i
        const int y2{static_cast<int>(c.y - d2 * cos(6 * i * PI / 180.0))};

        second_lines.push_back(new Graph_lib::Line{Point{x1, y1}, Point{x2, y2}});
        second_lines[second_lines.size() - 1].set_color(Color{20});
        second_lines[second_lines.size() - 1].set_style(Line_style{Line_style::solid, 2});
        attach(second_lines[second_lines.size() - 1]);
    }
    vector<int> labels{12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};  // for hour_lables
    for (int i = 0; i < 12; ++i)                                // hours
    {
        // overwrite hour_labels on seconds_labels for simplicity
        const int d1{static_cast<int>(r * 0.9)};                              // distance from the center of a circle
        const int x1{static_cast<int>(c.x + d1 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y1{static_cast<int>(c.y - d1 * cos(30 * i * PI / 180.0))};

        const int d2{r};
        const int x2{static_cast<int>(c.x + d2 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y2{static_cast<int>(c.y - d2 * cos(30 * i * PI / 180.0))};
        hour_lines.push_back(new Graph_lib::Line{Point{x1, y1}, Point{x2, y2}});
        hour_lines[hour_lines.size() - 1].set_color(Color{20});
        hour_lines[hour_lines.size() - 1].set_style(Line_style{Line_style::solid, 7});
        attach(hour_lines[hour_lines.size() - 1]);

        const int d3{static_cast<int>(r * 0.8)};                              // distance from the center of a circle
        const int x3{static_cast<int>(c.x + d3 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y3{static_cast<int>(c.y - d3 * cos(30 * i * PI / 180.0))};
        hour_labels.push_back(new Graph_lib::Text{Point{x3, y3}, to_string(labels[i])});
        hour_labels[hour_labels.size() - 1].set_color(Color::white);
        hour_labels[hour_labels.size() - 1].set_font(Font::helvetica_bold);
        hour_labels[hour_labels.size() - 1].set_font_size(35);
        hour_labels[hour_labels.size() - 1].move(-10, 14);  // to adjust the location caused by narrow casting
        attach(hour_labels[hour_labels.size() - 1]);
    }
    // individual adjustment for two characters label
    hour_labels[0].move(-7, -2);   // hour label: 12 hour
    hour_labels[10].move(-4, -2);  // hour label: 10
    hour_labels[11].move(-4, -2);  // hour label: 11
    redraw();
}

int main() {
    try {
        constexpr int width{800};
        constexpr int height{800};
        constexpr int radius{300};

        Clock_window win{Point{100, 100}, width, height, "Analog Clock", Point{width / 2, height / 2}, radius};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}