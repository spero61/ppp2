// Drill 16_04 adding a second menu for choosing line styles

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Lines_window : public Window  // Lines_window inherits from Window
{
   public:
    Lines_window(Point xy, int w, int h, const string& title);  // declare constructor

   private:
    // data:
    Open_polyline lines;
    // widgets:
    Button next_button;  // add (next_x, next_y) to lines
    Button quit_button;  // end program

    In_box next_x;
    In_box next_y;
    Out_box xy_out;

    Menu color_menu;
    Menu line_style_menu;
    Button menu_button;

    void change(Color c) { lines.set_color(c); }
    void hide_menu() {
        color_menu.hide();
        menu_button.show();
    }

    // actions invoked by callbacks:
    void red_pressed() {
        change(Color::red);
        hide_menu();
    }
    void blue_pressed() {
        change(Color::blue);
        hide_menu();
    }
    void black_pressed() {
        change(Color::black);
        hide_menu();
    }
    void menu_pressed() {
        menu_button.hide();
        color_menu.show();
    }

    void next();
    void quit();
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      next_button{Point{x_max() - 150, 0}, 70, 20, "Next point", [](Address, Address pw) { reference_to<Lines_window>(pw).next(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }},  // quit button
      next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},                                                                       // io boxes
      next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
      xy_out{Point{100, 0}, 100, 20, "current (x,y):"},
      color_menu{Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color"},
      menu_button{Point{x_max() - 80, 30}, 80, 20, "color menu", [](Address, Address pw) { reference_to<Lines_window>(pw).menu_pressed(); }} {
    attach(next_button);  // attach the parts to the window
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "red", [](Address, Address pw) { reference_to<Lines_window>(pw).red_pressed(); }});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue", [](Address, Address pw) { reference_to<Lines_window>(pw).blue_pressed(); }});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "black", [](Address, Address pw) { reference_to<Lines_window>(pw).black_pressed(); }});
    attach(color_menu);
    attach(menu_button);
    attach(lines);                  // attach the open_polylines to the window
    color_menu.hide();              // default
    xy_out.put("no point");         // default current point label
    lines.set_color(Color::black);  // default color
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