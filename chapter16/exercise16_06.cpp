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

// #include <stdio.h>
// #include <time.h>
#include <chrono>
#include <cmath>
// #include <iostream>
#include <thread>

constexpr double PI{3.14159265358979};

class Clock_Base : public Shape {
   public:
    Clock_Base(Point center, int radius);
    void draw_lines() const override;
    Point center() { return c; }
    int radius() { return r; }

   private:
    Point c;  // center
    int r;    // radius
    Circle frame;
    Vector_ref<Line> second_lines;  // to depict marks for every seconds and minutes
    Vector_ref<Line> hour_lines;    // to depict marks for every hour
    Vector_ref<Text> hour_labels;   // labels for numerals
};

Clock_Base::Clock_Base(Point center, int radius)
    : c{center}, r{radius}, frame{c, r} {
    if (r < 50) {
        error("error: radius for Clock_Base is too small.\nProvide the radius greater than or equal to 50");
    }

    add(c);
    frame.set_style(Line_style{Line_style::solid, 3});
    frame.set_color(Color::dark_blue);

    for (int i = 0; i < 60; ++i)  // seconds or minutes
    {
        const int d1{static_cast<int>(r * 0.95)};                            // distance from the center of a circle
        const int x1{static_cast<int>(c.x + d1 * sin(6 * i * PI / 180.0))};  // degrees: 6 * i
        const int y1{static_cast<int>(c.y - d1 * cos(6 * i * PI / 180.0))};

        const int d2{r};
        const int x2{static_cast<int>(c.x + d2 * sin(6 * i * PI / 180.0))};  // degrees: 6 * i
        const int y2{static_cast<int>(c.y - d2 * cos(6 * i * PI / 180.0))};
        second_lines.push_back(new Line{Point{x1, y1}, Point{x2, y2}});
        second_lines[second_lines.size() - 1].set_style(Line_style{Line_style::solid, 2});
    }
    int index{1};                 // for hour_lables
    for (int i = 0; i < 12; ++i)  // hours
    {
        // overwrite hour_labels on seconds_labels for simplicity
        const int d1{static_cast<int>(r * 0.9)};                              // distance from the center of a circle
        const int x1{static_cast<int>(c.x + d1 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y1{static_cast<int>(c.y - d1 * cos(30 * i * PI / 180.0))};

        const int d2{r};
        const int x2{static_cast<int>(c.x + d2 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y2{static_cast<int>(c.y - d2 * cos(30 * i * PI / 180.0))};
        hour_lines.push_back(new Line{Point{x1, y1}, Point{x2, y2}});
        hour_lines[hour_lines.size() - 1].set_style(Line_style{Line_style::solid, 7});

        const int d3{static_cast<int>(r * 0.8)};                              // distance from the center of a circle
        const int x3{static_cast<int>(c.x + d3 * sin(30 * i * PI / 180.0))};  // degrees: 30 * i
        const int y3{static_cast<int>(c.y - d3 * cos(30 * i * PI / 180.0))};
        hour_labels.push_back(new Text{Point{x3, y3}, to_string(index++)});
        hour_labels[hour_labels.size() - 1].set_font(Font::times_bold);
        hour_labels[hour_labels.size() - 1].set_font_size(30);
        hour_labels[hour_labels.size() - 1].move(-8, 9);  // to adjust the location caused by narrow casting
    }
}

void Clock_Base::draw_lines() const {
    frame.draw();

    for (int i = 0; i < second_lines.size(); ++i) {
        second_lines[i].draw();
    }

    for (int i = 0; i < hour_lines.size(); ++i) {
        hour_lines[i].draw();
    }

    for (int i = 0; i < hour_labels.size(); ++i) {
        hour_labels[i].draw();
    }
}

class Clock_window : public Window  // Lines_window inherits from Window
{
   public:
    Clock_window(Point xy, int w, int h, const string& title);  // declare constructor

   private:
    // data:
    Clock_Base clock_base;
    // widgets:
    Button quit_button;  // end program

    void quit() { hide(); }  // curious FLTK idiom to delete window
};

Clock_window::Clock_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
      clock_base{Point{x_max() / 2, y_max() / 2}, 100},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Clock_window>(pw).quit(); }} {
    attach(clock_base);
    attach(quit_button);
}

int main() {
    try {
        //time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now()); // https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
        //string now = ctime(&current_time);
        //cout << "The current time: " << now;

        //for (int i = 0; i < now.size(); ++i) {
        //    cout << '[' << i << "]: " << now[i] << endl;
        //}

        // for debugging the Clock_Base class

        Point tl{100, 100};  // top-left
        Simple_window win{tl, 800, 800, "Histogram class"};
        win.wait_for_button();

        Clock_Base clock_base{Point{400, 400}, 200};
        win.attach(clock_base);
        win.wait_for_button();

        //Clock_window win{ Point{100, 100}, 800, 800, "Analog Clock" };
        //return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}