// Drill 16_02 (Chapter 16.5: An example)

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Lines_window : Window  // Lines_window inherits from Window
{
    Lines_window(Point xy, int w, int h, const string& title);  // declare constructor
    Open_polyline lines;

   private:
    Button next_button;  // declare some buttons – type Button
    Button quit_button;
    In_box next_x;  // declare some i/o boxes
    In_box next_y;
    Out_box xy_out;

    void next();  // what to do when next_button is pushed
    void quit();  // what to do when quit_botton is pushed
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
      // construct/initialize the parts of the window:
      // location	        size          name            action
      next_button{Point{x_max() - 150, 0}, 70, 20, "Next point", [](Address, Address pw) { reference_to<Lines_window>(pw).next(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }},  // quit button
      next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},                                                                       // io boxes
      next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
      xy_out{Point{100, 0}, 100, 20, "current (x,y):"} {
    attach(next_button);  // attach the parts to the window
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    attach(lines);  // attach the open_polylines to the window
    xy_out.put("no point");
    lines.set_color(Color::dark_blue);  // set default color to dark_blue
}

void Lines_window::quit() {
    hide();  // curious FLTK idiom to delete window
}

void Lines_window::next() {
    int x = next_x.get_int();
    int y = next_y.get_int();
    lines.add(Point{x, y});

    // update current position readout:
    ostringstream ss;
    ss << '(' << x << ", " << y << ')';
    xy_out.put(ss.str());
    redraw();
}

int main() {
    try {
        Lines_window win{Point{100, 100}, 600, 400, "lines"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}