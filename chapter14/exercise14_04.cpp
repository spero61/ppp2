// Define a class Immobile_Circle, which is just like Circle but can't be moved.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Immobile_Circle : public Circle {
   public:
    using Circle::Circle;
    void move(int dx, int dy) override;
    Immobile_Circle(const Immobile_Circle&) = delete;  // prevent copying
    Immobile_Circle& operator=(const Immobile_Circle&) = delete;
};

void Immobile_Circle::move(int dx, int dy) {
    error("error: This is Immobile_Circle");
}

int main() {
    try {
        const Point x{100, 100};
        Simple_window win{x, 800, 600, "Immobile_Circle"};
        win.wait_for_button();

        const int radius{70};

        Immobile_Circle c1 = {Point{200, 150}, radius};
        win.attach(c1);
        win.wait_for_button();

        c1.move(300, 300);  // cause runtime-error
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