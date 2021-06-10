#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

constexpr double PI{3.141592};

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();
        win.set_label("Ch12 Exercise11");

        /*
            A(300, 200)    D(500,200)
            ---------------
            |             |
            |             |
            |             |
            |             |
            |             |
            ---------------
            B(300, 400)    C(500, 400)

        */

        Graph_lib::Polygon sqaure;    // a polygon; a Polygon is a kind of Shape
        sqaure.add(Point{300, 200});  // point A
        sqaure.add(Point{500, 200});  // point D
        sqaure.add(Point{500, 400});  // point C
        sqaure.add(Point{300, 400});  // point B
        win.attach(sqaure);
        win.wait_for_button();

        const double hypotenuse = 200.0 / cos(15 * PI / 180.0);
        const int x = static_cast<int>(sqrt(hypotenuse * hypotenuse - 200 * 200));

        Graph_lib::Polygon equil_triangle;
        equil_triangle.add(Point{300, 200});  // point A
        equil_triangle.add(Point{300 + x, 400});
        equil_triangle.add(Point{500, 200 + x});
        win.attach(equil_triangle);
        win.wait_for_button();

        const double y = (200.0 / (tan(PI * 72 / 180.0) + tan(PI * 36 / 180.0)));
        const double h = (y * tan(PI * 36 / 180.0));

        const double d = (100.0 + y) / tan(PI * 36 / 180.0);  // a side length of a regular pentagon
        const double w = (100.0 + y) / tan(PI * 54 / 180.0);

        // vertices of the pentagon
        // draw order: 1 - 3 - 2 - 4 - 5
        /*
        Mark m1{ Point{500 + static_cast<int>(y), 400 - static_cast<int>(h)},'1' };
        win.attach(m1);
        Mark m2{ Point{300 - static_cast<int>(y), 400 - static_cast<int>(h)},'2' };
        win.attach(m2);
        Mark m3{ Point{400, 400 + static_cast<int>(w - h)},'3' };
        win.attach(m3);
        Mark m4{ Point{static_cast<int>(400 - (d / 2)), static_cast<int>(200 - tan(PI * 36 / 180.0) * (d/2 - 100)) } ,'4'};
        win.attach(m4);
        Mark m5{ Point{static_cast<int>(400 + (d / 2)), static_cast<int>(200 - tan(PI * 36 / 180.0) * (d/2 - 100)) }, '5'};
        win.attach(m5);
        */

        // Since "Point"s only accept integer values, I use these values to fit Shape better as it supposed to do.
        const int x_adjustment{6};
        const int y_adjustment{4};

        Graph_lib::Polygon pentagon;
        pentagon.add(Point{500 + static_cast<int>(y), 400 - static_cast<int>(h)});
        pentagon.add(Point{400, 400 + static_cast<int>(w - h)});
        pentagon.add(Point{300 - static_cast<int>(y), 400 - static_cast<int>(h)});
        pentagon.add(Point{static_cast<int>(400 - (d / 2)) + x_adjustment, static_cast<int>(200 - tan(PI * 36 / 180.0) * (d / 2 - 100)) - y_adjustment});
        pentagon.add(Point{static_cast<int>(400 + (d / 2)) - x_adjustment, static_cast<int>(200 - tan(PI * 36 / 180.0) * (d / 2 - 100)) - y_adjustment});
        win.attach(pentagon);
        win.wait_for_button();

        // REVIEW point:
        // It would be better to find the center of pentagon then calculate the radius of the circle.
        // Since studying Geometry is not the main purpose of this book, I will leave this task as optional.
        Graph_lib::Circle circle{Point{401, 315}, 159};  // draw a circle by trial-and-error method XD
        win.attach(circle);
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