// Define a class Controller with four virtual functions on(), off(), set_level(int), and show().
// Derive at least two classes from Controller.
// One should be a simple test class where show() prints out whether the class is set to on or off and what is the current level.
// The second derived class should somehow control the line color of a Shape; the exact meaning of “level” is up to you.
// Try to find a third “thing” to control with such a Controller class.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Controller {
   public:
    Controller() : lvl{0}, is_on{false} {}  // default constructor for Controller and its derived classes
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void set_level(int lvl_arg) = 0;
    virtual void show() = 0;

   protected:
    int lvl;
    bool is_on;
};

class Speaker : public Controller {
   public:
    void on() { is_on = true; }
    void off() { is_on = false; }
    void show() {
        if (is_on == true)
            cout << "Speaker is ON\nVolumn: " + to_string(lvl) + '\n';
        else
            cout << "Speaker is OFF\nVolumn: " + to_string(lvl) + '\n';
    }
    void set_level(int lvl_arg) { lvl = lvl_arg; }
};

// I used "(*var)." notation here instead of "var->" notation.
class Shape_Controller : public Controller {
   public:
    Shape_Controller(Shape& shape_arg);
    void on() {
        is_on = true;
        (*shape).set_color(Color{color_int});
    }
    void off() {
        is_on = false;
        (*shape).set_color(Color::invisible);
    }
    void show() {}  // do nothing
    void set_level(int lvl_arg);
    int level() { return lvl; }

   private:
    Shape* shape;
    int color_int;
};

Shape_Controller::Shape_Controller(Shape& shape_arg) : shape{&shape_arg}, color_int{16 * 13 + 7} {
    is_on = true;                                          // default state is "on"
    (*shape).set_style(Line_style{Line_style::solid, 5});  // default line thinkness is 5
    (*shape).set_color(Color{color_int});
}

// Color of the Shape_Controller is light yellow(lvl == 0) to hot pink(lvl == 7)
void Shape_Controller::set_level(int lvl_arg) {
    if (lvl_arg < 0 || lvl_arg > 7)
        error("error: lvl_arg of set_level() should be in range between 0 and 7");
    lvl = lvl_arg;
    (*shape).set_color(Color{color_int - lvl});
}

int main() {
    try {
        //Test a Speaker class
        Speaker eris;
        eris.show();
        cout << '\n';

        eris.on();
        eris.set_level(5);
        eris.show();

        //Test a Shape_controller class
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 800, 600, "Controller classes");
        win.wait_for_button();

        Circle c1{Point{win.x_max() / 2, win.y_max() / 2}, 200};
        c1.set_fill_color(Color{16 * 15 + 6});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
        win.attach(c1);

        Shape_Controller ctr_c1(c1);
        win.set_label("Shape_Controller level: " + to_string(ctr_c1.level()));
        win.wait_for_button();

        for (int i = 1; i <= 5; ++i) {
            ctr_c1.set_level(i);
            win.set_label("Shape_Controller level: " + to_string(ctr_c1.level()));
            win.wait_for_button();
        }

        ctr_c1.off();
        win.set_label("Shape_Controller is OFF");
        win.wait_for_button();

        ctr_c1.on();
        win.set_label("Shape_Controller is ON");
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
