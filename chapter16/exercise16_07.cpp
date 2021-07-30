// Make an image of an airplane "fly around" in a window.

#include <thread>

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Airplane_window : public Window  // Lines_window inherits from Window
{
   public:
    Airplane_window(Point xy, int w, int h, const string& title, const string& image_filename, int image_width, int image_height);  // declare constructor

   private:
    // data:
    Image airplane;
    int airplane_width;
    int airplane_height;
    bool is_flying;

    // widgets:
    Button start_button;
    Button stop_button;
    Button quit_button;  // end program

    void start();            // airplane start flying
    void stop();             // airplane stop flying
    void quit() { hide(); }  // https://www.fltk.org/doc-1.3/classFl__Window.html#acd69a335bdc69f5624301f267ca7f94e
};

Airplane_window::Airplane_window(Point xy, int w, int h, const string& title, const string& image_filename, int image_width, int image_height)
    : Window{xy, w, h, title}, airplane{Point{x_max() / 2, y_max() / 2}, image_filename}, airplane_width{image_width}, airplane_height{image_height}, is_flying{false}, start_button{Point{x_max() - 230, 0}, 70, 20, "Start", [](Address, Address pw) { reference_to<Airplane_window>(pw).start(); }}, stop_button{Point{x_max() - 150, 0}, 70, 20, "Stop", [](Address, Address pw) { reference_to<Airplane_window>(pw).stop(); }}, quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Airplane_window>(pw).quit(); }} {
    airplane.move(-static_cast<int>(airplane_width / 2), -static_cast<int>(airplane_height / 2));  // adjustment airplane image to the center
    attach(airplane);
    attach(start_button);
    attach(stop_button);
    attach(quit_button);
    redraw();
}

// https://www.fltk.org/doc-1.3/fltk-colormap.png

void Airplane_window::start() {
    random_device rd;                           // https://en.cppreference.com/w/cpp/numeric/random/random_device
    mt19937_64 gen(rd());                       // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    uniform_int_distribution<int> rd_x{3, 10};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<int> rd_y{4, 8};   // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    int x_move = rd_x(gen);
    int y_move = rd_y(gen);

    is_flying = true;

    while (is_flying) {
        const int x = airplane.point(0).x;
        const int y = airplane.point(0).y;

        // deal with each case when the airplane touches...
        //
        // left hand side boundary
        if (x + x_move < 0) {
            x_move = rd_x(gen);
        }
        // right hand side boundary
        else if (x + x_move + airplane_width > x_max()) {
            x_move = -rd_x(gen);
        }

        // upper boundary
        if (y + y_move < 0) {
            y_move = rd_y(gen);
        }
        // lower boundary
        else if (y + y_move + airplane_height > y_max()) {
            y_move = -rd_y(gen);
        }

        airplane.move(x_move, y_move);
        redraw();                           // Fl_Widget::redraw(); // https://www.fltk.org/doc-1.3/classFl__Widget.html#aa63ce68cbf4620cf8750b868368ea02b
        Fl::wait();                         // https://www.fltk.org/doc-1.3/classFl.html#a108a84216f0b3fa1cb0c46ab7449a312
        std::this_thread::sleep_for(10ms);  // https://en.cppreference.com/w/cpp/thread/sleep_for
    }
}

void Airplane_window::stop() {
    is_flying = false;
}

int main() {
    try {
        Airplane_window win{Point{100, 100}, 600, 400, "Fly Airplane!", "exercise16_07.jpg", 50, 30};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}