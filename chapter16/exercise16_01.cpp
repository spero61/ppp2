// My_window with next and quit buttons

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class My_window : public Window {
   public:
    My_window(Point xy, int w, int h, const string& title);

    void wait_for_button();
    Button next_button;
    Button quit_button;

   private:
    bool next_button_pushed;
    void next() { next_button_pushed = true; }
    void quit() { hide(); }  // curious FLTK idiom to delete window
};

My_window::My_window(Point xy, int w, int h, const string& title) : Window(xy, w, h, title),
                                                                    next_button_pushed(false),
                                                                    next_button{Point{x_max() - 150, 0}, 70, 20, "Next", [](Address, Address pw) { reference_to<My_window>(pw).next(); }},
                                                                    quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<My_window>(pw).quit(); }} {
    attach(next_button);
    attach(quit_button);
}

void My_window::wait_for_button() {
    while (!next_button_pushed) Fl::wait();
    next_button_pushed = false;
    Fl::redraw();
}

int main() {
    try {
        My_window win{Point{100, 100}, 600, 400, "My_window with next and quit buttons"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}