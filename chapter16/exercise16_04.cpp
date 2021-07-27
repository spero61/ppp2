// a menu with items that draw polygons

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

constexpr double PI{3.14159265358979};

enum class Shape_type {
    circle,
    square,
    equilateral_triangle,
    hexagon
};

// regular_polygon from exercise13_10.cpp
class Regular_polygon : public Shape {
   public:
    Regular_polygon(Point cc, int dd, int ss);
    void draw_lines() const;
    Point center() { return c; }

   private:
    Point c;  // center point of the Regular_polygon.
    int d;    // A distance from the center which is radius of the circumscribed circle.
    int s;    // number of side that a Regular_polygon has. (s => 3)
};

Regular_polygon::Regular_polygon(Point cc, int dd, int ss) : c{cc}, d{dd}, s{ss} {
    if (d <= 0)
        error("Bad Regular_polygon: distance should be positive");
    if (s <= 2)
        error("Bad Regular_polygon: number of sides should be greater than 2");

    const double x{360.0 / s};  // degrees for tmp_x. Then add Points to draw a Regular_polygon

    // std::sin() https://en.cppreference.com/w/cpp/numeric/math/sin
    // std::cos() https://en.cppreference.com/w/cpp/numeric/math/cos

    // Note that FLTK coordinate's (0,0) is located at the Top-left corner.
    // quadrant 1,2,3, and 4 is based on Point c that is Point{c.x, c.y}
    for (int i = 0; i < s; ++i) {
        double tmp_x{i * x};
        if (tmp_x == 0 || tmp_x == 360)    // north
            add(Point{c.x, c.y - d});      // starting point
        else if (tmp_x > 0 && tmp_x < 90)  // quadrant 1
            add(Point{c.x + static_cast<int>(d * sin(tmp_x * PI / 180.0)), c.y - static_cast<int>(d * cos(tmp_x * PI / 180.0))});
        else if (tmp_x == 90)  // east
            add(Point{c.x + d, c.y});
        else if (tmp_x > 90 && tmp_x < 180)  // quadrant 4
            add(Point{c.x + static_cast<int>(d * cos((tmp_x - 90) * PI / 180.0)), c.y + static_cast<int>(d * sin((tmp_x - 90) * PI / 180.0))});
        else if (tmp_x == 180)  // south
            add(Point{c.x, c.y + d});
        else if (tmp_x > 180 && tmp_x < 270)  // quadrant 3
            add(Point{c.x - static_cast<int>(d * sin((tmp_x - 180) * PI / 180.0)), c.y + static_cast<int>(d * cos((tmp_x - 180) * PI / 180.0))});
        else if (tmp_x == 270)  // west
            add(Point{c.x - d, c.y});
        else if (tmp_x > 270 && tmp_x < 360)  // quadrant 2
            add(Point{c.x - static_cast<int>(d * cos((tmp_x - 270) * PI / 180.0)), c.y - static_cast<int>(d * sin((tmp_x - 270) * PI / 180.0))});
        else
            error("error(Regular_polygon constructor): This should not be reached");
    }

    add(Point{c.x, c.y - d});  // add starting point again. Because this class utilizes Open_polygon class
}

void Regular_polygon::draw_lines() const {
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i) {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());  // reset color
    }

    if (color().visibility())
        Shape::draw_lines();
}

class Polygon_window : public Window  // Lines_window inherits from Window
{
   public:
    Polygon_window(Point xy, int w, int h, const string& title);  // declare constructor

   private:
    // data:
    Vector_ref<Shape> shapes;

    // widgets:
    Button clear_button;  // hide polygons from the window
    Button quit_button;   // end program
    In_box coordinate_x;
    In_box coordinate_y;
    In_box size_input;  // get size (this means radius for circle, hexagon and side for other shapes)
    Menu draw_menu;
    Button menu_button;

    void draw_shape(Shape_type polygon_type);  // when an item of draw menu is clicked draw selected polygon
    void hide_menu();
    void menu_pressed();

    void clear();  // hide all polygons
    void quit();   // quit the program
};

Polygon_window::Polygon_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      clear_button{Point{x_max() - 150, 0}, 70, 20, "Clear", [](Address, Address pw) { reference_to<Polygon_window>(pw).clear(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Polygon_window>(pw).quit(); }},  // quit button
      coordinate_x{Point{20, 0}, 60, 20, "x:"},                                                                                   // get coordinate x to draw polygon
      coordinate_y{Point{120, 0}, 60, 20, "y:"},                                                                                  // get coordinate y to draw polygon
      size_input{Point{220, 0}, 60, 20, "size:"},                                                                                 // get size coefficient
      draw_menu{Point{x_max() - 140, 40}, 140, 20, Menu::vertical, "Draw"},
      menu_button{Point{x_max() - 80, 30}, 80, 20, "Draw menu", [](Address, Address pw) { reference_to<Polygon_window>(pw).menu_pressed(); }} {
    attach(clear_button);  // attach the parts to the window
    attach(quit_button);
    attach(coordinate_x);
    attach(coordinate_y);
    attach(size_input);
    draw_menu.attach(new Button{Point{0, 0}, 0, 0, "Circle", [](Address, Address pw) { reference_to<Polygon_window>(pw).draw_shape(Shape_type::circle); }});
    draw_menu.attach(new Button{Point{0, 0}, 0, 0, "Square", [](Address, Address pw) { reference_to<Polygon_window>(pw).draw_shape(Shape_type::square); }});
    draw_menu.attach(new Button{Point{0, 0}, 0, 0, "Equilateral Triangle", [](Address, Address pw) { reference_to<Polygon_window>(pw).draw_shape(Shape_type::equilateral_triangle); }});
    draw_menu.attach(new Button{Point{0, 0}, 0, 0, "Hexagon", [](Address, Address pw) { reference_to<Polygon_window>(pw).draw_shape(Shape_type::hexagon); }});
    attach(draw_menu);
    attach(menu_button);
    draw_menu.hide();  // default: hide menu items
}

void Polygon_window::draw_shape(Shape_type polygon_type) {
    const int x{coordinate_x.get_int()};
    const int y{coordinate_y.get_int()};
    const int size{size_input.get_int()};

    // get_int() returns -999999 when it is not a digit
    if (x == -999999 || y == -999999 || size == -999999) {
        error("error: at least one of input boxes is empty");
    }

    switch (polygon_type) {
        case Shape_type::circle:
            shapes.push_back(new Circle{Point{x, y}, size});
            break;

        case Shape_type::square:
            shapes.push_back(new Graph_lib::Rectangle{Point{x, y}, size, size});
            break;

        case Shape_type::equilateral_triangle:
            shapes.push_back(new Regular_polygon{Point{x, y}, size, 3});
            break;

        case Shape_type::hexagon:
            shapes.push_back(new Regular_polygon{Point{x, y}, size, 6});
            break;

        default:
            error("error: Polygon_window::draw_shape argument is wrong");
    }
    attach(shapes[shapes.size() - 1]);
    redraw();
    hide_menu();
}

void Polygon_window::quit() {
    hide();  // curious FLTK idiom to delete window
}

void Polygon_window::clear() {
    for (int i = 0; i < shapes.size(); ++i) {
        shapes[i].set_color(Color::invisible);
        shapes[i].set_fill_color(Color::invisible);
    }
    redraw();
}

void Polygon_window::hide_menu() {
    draw_menu.hide();
    menu_button.show();
}

void Polygon_window::menu_pressed() {
    menu_button.hide();
    draw_menu.show();
}

int main() {
    try {
        Polygon_window win{Point{100, 100}, 600, 400, "Draw polygons using menu"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}