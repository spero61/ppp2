// Image on top of a Button (Use the random number generator provided in the textbook)

#include <random>

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

inline int rand_int(int min, int max) {
    static default_random_engine ran;
    return uniform_int_distribution<>{min, max}(ran);
}

class My_window : public Window {
   public:
    My_window(Point xy, int w, int h, const string& title);

    void wait_for_button();
    void move_button();  // hide a random button then show a color-filled square
    Button next_button;
    Button quit_button;
    Button my_button;
    Image my_image;

   private:
    bool next_button_pushed;
    void next() { next_button_pushed = true; }
    void quit() { hide(); }  // curious FLTK idiom to delete window
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title),
      next_button_pushed(false),
      next_button{Point{x_max() - 150, 0}, 70, 20, "Next", [](Address, Address pw) { reference_to<My_window>(pw).next(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<My_window>(pw).quit(); }},
      my_button{Point{x_max() / 2 - 100, y_max() / 2 - 125}, 200, 250, "Click me!", [](Address, Address pw) { reference_to<My_window>(pw).move_button(); }},
      my_image{Point{x_max() / 2 - 100, y_max() / 2 - 125}, "exercise16_03.jpg"} {
    attach(next_button);
    attach(quit_button);
    attach(my_button);
    attach(my_image);
}

void My_window::wait_for_button() {
    while (!next_button_pushed) Fl::wait();
    next_button_pushed = false;
    Fl::redraw();
}

void My_window::move_button() {
    // get current points for both my_button and my_image
    const int x{my_image.point(0).x};
    const int y{my_image.point(0).y};

    const int x_min_val{-x};
    const int y_min_val{-y};
    const int x_max_val{x_max() - x - 200};  // width: 200
    const int y_max_val{y_max() - y - 250};  // height: 250

    // get random number using the helper function the author provided
    const int x_move{rand_int(x_min_val, x_max_val)};
    const int y_move{rand_int(y_min_val, y_max_val)};

    // conduct moves for both my_button and my_image
    my_button.move(x_move, y_move);
    my_image.move(x_move, y_move);
}

int main() {
    try {
        My_window win{Point{100, 100}, 800, 800, "Image Button moves randomly when clicked"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}