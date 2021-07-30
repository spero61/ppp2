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
#include <ctime>
#include <thread>

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
    Vector_ref<Graph_lib::Line> second_hands;
    Vector_ref<Graph_lib::Line> minute_hands;
    Vector_ref<Graph_lib::Line> hour_hands;
    Circle pin;  // a pin to hide hands' intersection
    int seconds;
    int minutes;
    int hours;
    string current_time;
    // widget:
    Button quit_button;  // end program

    void draw_clock_base();  // draw clock base(frame, second_lines, hour_lines, and hour_labels)
    void start();            // start draw clock hands and refresh(using Fl::wait(), redraw() and sleep_for()) every seconds
    void quit() { hide(); }  // https://www.fltk.org/doc-1.3/classFl__Window.html#acd69a335bdc69f5624301f267ca7f94e
};

Clock_window::Clock_window(Point xy, int w, int h, const string& title, Point center, int radius)
    : Window{xy, w, h, title}, c{center}, r{radius}, frame{c, r}, pin{c, 8},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Clock_window>(pw).quit(); }} {
    attach(quit_button);

    // get local time from the system
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);  // https://www.cplusplus.com/reference/ctime/localtime/
    current_time = asctime(timeinfo);
    // cout << current_time;  // current local time when the program is executed. (eg., Fri Jul 30 16:40:14 2021)

    // initialize variables related to the current time
    hours = stoi(current_time.substr(11, 2));    // std::stoi https://www.cplusplus.com/reference/string/stoi/
    minutes = stoi(current_time.substr(14, 2));  // std::string::substr https://www.cplusplus.com/reference/string/string/substr/
    seconds = stoi(current_time.substr(17, 2));

    draw_clock_base();
    start();
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

    // TMI: Grand Central Station, NYC and Orsay Museum , Paris uses IIII to mark 4 o'clock,
    // while the Big Ben relies on the numeral IV.
    // See details: https://monochrome-watches.com/why-do-clocks-and-watches-use-roman-numeral-iiii-instead-of-iv/
    // vector<string> labels{ "XII", "I", "II", "III", "IIII", "V", "VI", "VII", "VIII", "IX", "X", "XI" };  // for hour_lables: Roman numerals

    vector<string> labels{"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};  // for hour_lables: Arabic numerals
    for (int i = 0; i < 12; ++i)                                                           // hours
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
        hour_labels.push_back(new Graph_lib::Text{Point{x3, y3}, labels[i]});
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

void Clock_window::start() {
    while (true) {
        if (seconds >= 60) {
            seconds %= 60;
            minutes++;
        }
        if (minutes >= 60) {
            minutes %= 60;
            hours++;
        }
        if (hours >= 12) {
            hours %= 12;
        }
        const int d1{static_cast<int>(r * 0.8)};                                   // distance from the center of a circle
        const int x1{static_cast<int>(c.x + d1 * sin(6 * seconds * PI / 180.0))};  // degrees: 30 * i
        const int y1{static_cast<int>(c.y - d1 * cos(6 * seconds * PI / 180.0))};
        second_hands.push_back(new Graph_lib::Line{c, Point{x1, y1}});
        second_hands[second_hands.size() - 1].set_color(Color::magenta);
        second_hands[second_hands.size() - 1].set_style(Line_style{Line_style::solid, 1});
        attach(second_hands[second_hands.size() - 1]);

        const int d2{static_cast<int>(r * 0.7)};                                                      // distance from the center of a circle
        const int x2{static_cast<int>(c.x + d2 * sin(6 * (minutes + seconds / 60.0) * PI / 180.0))};  // degrees: 30 * i
        const int y2{static_cast<int>(c.y - d2 * cos(6 * (minutes + seconds / 60.0) * PI / 180.0))};
        minute_hands.push_back(new Graph_lib::Line{c, Point{x2, y2}});
        minute_hands[minute_hands.size() - 1].set_color(Color::cyan);
        minute_hands[minute_hands.size() - 1].set_style(Line_style{Line_style::solid, 3});
        attach(minute_hands[minute_hands.size() - 1]);

        const int d3{static_cast<int>(r * 0.45)};                                                      // distance from the center of a circle
        const int x3{static_cast<int>(c.x + d3 * sin((30 * (hours + minutes / 60.0)) * PI / 180.0))};  // degrees: 30 * i
        const int y3{static_cast<int>(c.y - d3 * cos((30 * (hours + minutes / 60.0)) * PI / 180.0))};
        hour_hands.push_back(new Graph_lib::Line{c, Point{x3, y3}});
        hour_hands[hour_hands.size() - 1].set_color(Color::yellow);
        hour_hands[hour_hands.size() - 1].set_style(Line_style{Line_style::solid, 5});
        attach(hour_hands[hour_hands.size() - 1]);

        pin.set_color(Color{8});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        pin.set_fill_color(Color{8});
        attach(pin);

        redraw();    // Fl_Widget::redraw(); // https://www.fltk.org/doc-1.3/classFl__Widget.html#aa63ce68cbf4620cf8750b868368ea02b
        Fl::wait();  // https://www.fltk.org/doc-1.3/classFl.html#a108a84216f0b3fa1cb0c46ab7449a312

        // REVIEW: which one is better?
        std::this_thread::sleep_for(1000ms);  // https://en.cppreference.com/w/cpp/thread/sleep_for
        // std::this_thread::sleep_for(std::chrono::seconds(1));  // https://www.cplusplus.com/reference/thread/this_thread/sleep_for/

        //// REVIEW: if I use delete, FLTK reports an error after a few seconds, why?
        //// fl_line_style(): Could not create GDI pen object.
        //// http://www.cplusplus.com/reference/new/operator%20delete/
        //delete &second_hands[second_hands.size() - 1];
        //delete &minute_hands[minute_hands.size() - 1];
        //delete &hour_hands[hour_hands.size() - 1];

        // This is not efficient way as "Vector_ref"s keep growing. see comments right above
        detach(second_hands[second_hands.size() - 1]);
        detach(minute_hands[minute_hands.size() - 1]);
        detach(hour_hands[hour_hands.size() - 1]);
        seconds++;
    }
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