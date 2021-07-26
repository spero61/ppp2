// 4-by-4 checkerboard of square buttons

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class My_window : public Window {
   public:
    My_window(Point xy, int w, int h, const string& title);

    void wait_for_button();
    void toggle_button();  // hide a random button then show a color-filled square
    Button next_button;
    Button quit_button;
    Vector_ref<Button> square_buttons;
    Vector_ref<Graph_lib::Rectangle> rects;

   private:
    bool next_button_pushed;
    void next() { next_button_pushed = true; }
    void quit() { hide(); }  // curious FLTK idiom to delete window
};

My_window::My_window(Point xy, int w, int h, const string& title) : Window(xy, w, h, title),
                                                                    next_button_pushed(false),
                                                                    next_button{Point{x_max() - 150, 0}, 70, 20, "Next", [](Address, Address pw) { reference_to<My_window>(pw).next(); }},
                                                                    quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<My_window>(pw).quit(); }} {
    int index{0};
    const int side{static_cast<int>(x_max() / 4)};
    // rows
    for (int i = 0; i < 4; ++i) {
        // columns
        for (int j = 0; j < 4; ++j) {
            square_buttons.push_back(new Button{Point{0 + side * j, 0 + side * i}, side, side, "Button " + to_string(index++), [](Address, Address pw) { reference_to<My_window>(pw).toggle_button(); }});
            rects.push_back(new Graph_lib::Rectangle{Point{0 + side * j, 0 + side * i}, side, side});
        }
    }

    for (int i = 0; i < square_buttons.size(); ++i) {
        rects[i].set_color(Color::invisible);
        rects[i].set_fill_color(Color::invisible);
        attach(rects[i]);
        attach(square_buttons[i]);
    }
    attach(next_button);
    attach(quit_button);
}

void My_window::wait_for_button() {
    while (!next_button_pushed) Fl::wait();
    next_button_pushed = false;
    Fl::redraw();
}

void My_window::toggle_button() {
    random_device rd;                               // https://en.cppreference.com/w/cpp/numeric/random/random_device
    mt19937_64 gen(rd());                           // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    uniform_int_distribution<int> rd_value{0, 15};  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    for (int i = 0; i < square_buttons.size(); ++i) {
        square_buttons[i].show();
        rects[i].set_fill_color(Color::invisible);
    }
    const int index{rd_value(gen)};
    square_buttons[index].hide();
    rects[index].set_fill_color(Color{16 * 5 + index * 7});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
}

int main() {
    try {
        My_window win{Point{100, 100}, 800, 800, "4-by-4 checkerboard of square buttons"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}