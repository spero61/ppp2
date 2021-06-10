#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();

        Image ii{Point{0, 0}, "tuomiokirkko.jpg"};  // 300*250-pixel jpg
        win.attach(ii);

        Text title{Point{450, 50}, "Helsinki Cathedral"};
        title.set_font(Font::helvetica_bold);
        title.set_font_size(34);
        title.set_color(Color::white);
        win.attach(title);

        Text camera{Point{500, 80}, "Contaflex II 35mm"};
        camera.set_font(Font::helvetica_bold);
        camera.set_font_size(25);
        camera.set_color(Color::white);
        win.attach(camera);

        win.set_label("Ch12 Exercise09 - Helsingin Tuomiokirkko");
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