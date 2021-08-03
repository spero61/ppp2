// a program where a user can choose among a set of functions (e.g., sin() and log()),
// provide parameters for those functions, and then graph them

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

enum class Graph_type {
    none,  // initial value
    linear,
    quadratic,
    cubic,
    sin,
    cos,
    tan,
    log,
    exp,
};

// As in book15_02.cpp, using global variables is inevitable, because capturing local variables in lambda function does not work.
// This is because the lambda expression can be converted to address of function only if it doesn't have capture arguments.
// And Function class defined in Graph.h is not
// (source : [https://groups.google.com/g/ppp-public/c/WBHYlwS6m3g](https://groups.google.com/g/ppp-public/c/WBHYlwS6m3g)

double coef_a{0};  // coefficients
double coef_b{0};
double coef_c{0};
double coef_d{0};

double calc_linear(double x) {
    return coef_a * x + coef_b;
}

double calc_quadratic(double x) {
    return coef_a * (x * x) + coef_b * x + coef_c;
}

double calc_cubic(double x) {
    return coef_a * pow(x, 3) + coef_b * pow(x, 2) + coef_c * x;
}

double calc_sin(double x) {
    return coef_a * sin(coef_b * x) + coef_c;
}

double calc_cos(double x) {
    return coef_a * cos(coef_b * x) + coef_c;
}

double calc_tan(double x) {
    return coef_a * tan(coef_b * x) + coef_c;
}

class Plot_window : public Window  // Lines_window inherits from Window
{
   public:
    Plot_window(Point xy, int w, int h, const string& title);  // declare constructor

   private:
    // data:
    Vector_ref<Axis> axes;       // axes[0]: x axis, axes[1]: y axis
    Vector_ref<Shape> graphs;    // a container for Function graph
    Vector_ref<Text> equations;  // function equation text for latest graphs (up to 8)
    Graph_type selected_graph;   // is set when a user select the graph using Menu select_menu

    const int x_orig;
    const int y_orig;
    const Point orig;         // (0, 0) for the axes
    const int x_axis_length;  // used for x axis
    const int y_axis_length;  // used for y axis
    const double r_min{-10};  // range [-10:11)
    const double r_max{11};
    const int n_points{400};   // number of points used in range
    const double x_scale{30};  // scaling factors for axes and graphs
    const double y_scale{30};

    // widgets:
    Button clear_button;  // hide all function graphs
    Button plot_button;   // plot graph
    Button quit_button;   // end program

    Menu select_menu;    // select a graph
    Button menu_button;  // button for select_menu

    Out_box output_equation;
    In_box parameter_a;  // to get user input for parameter values (are used to plot some graphs)
    In_box parameter_b;
    In_box parameter_c;

    // actions invoked by callbacks:x
    void clear();            // hide all polygons
    void plot();             // plot the selected graph (using or without parameter values)
    void quit() { hide(); }  // https://www.fltk.org/doc-1.3/classFl__Window.html#acd69a335bdc69f5624301f267ca7f94e

    void hide_menu();                                       // hide select menu
    void menu_pressed();                                    // show select menu items
    void toggle_parameter_input(bool a, bool b, bool c);    // helper function to toggle In_boxes
    void set_parameter_values(bool a, bool b, bool c);      // if an argument is true, set the corresponding parameter value
    void show_function_equation(Graph_type function_name);  // set Graph_type selected_graph for later use, then print the equation on Out_box output_equation
};

Plot_window::Plot_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title}, selected_graph{Graph_type::none}, x_orig{x_max() / 2}, y_orig{y_max() / 2}, orig{Point{x_orig, y_orig}}, x_axis_length{x_max() - 20}, y_axis_length{y_max() - 20}, clear_button{Point{x_max() - 230, 0}, 70, 20, "Clear", [](Address, Address pw) { reference_to<Plot_window>(pw).clear(); }}, plot_button{Point{x_max() - 150, 0}, 70, 20, "Plot", [](Address, Address pw) { reference_to<Plot_window>(pw).plot(); }}, quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Plot_window>(pw).quit(); }},  // quit button

      output_equation{Point{72, 5}, 150, 20, "Equation: "},
      // note that there is no way to set default value to In_box which might can keep user from surprising program exit
      // It requires to change the Graphics interface library code the author provided which is not necessary
      // REVIEW: I might find a way to prevent this problem after learning more features like pointers in later chapters
      parameter_a{Point{130, 30}, 70, 20, "Set parameters  a: "},
      parameter_b{Point{230, 30}, 70, 20, "b: "},
      parameter_c{Point{320, 30}, 70, 20, "c: "},
      select_menu{Point{x_max() - 140, 40}, 140, 20, Menu::vertical, "Functions"},
      menu_button{Point{x_max() - 90, 30}, 90, 20, "Graph menu", [](Address, Address pw) { reference_to<Plot_window>(pw).menu_pressed(); }}

{
    // attach the parts to the window
    attach(clear_button);
    attach(plot_button);
    attach(quit_button);
    attach(output_equation);
    attach(parameter_a);
    attach(parameter_b);
    attach(parameter_c);
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "linear", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::linear); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "quadratic", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::quadratic); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "cubic", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::cubic); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "sin", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::sin); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "cos", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::cos); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "tan", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::tan); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "log", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::log); }});
    select_menu.attach(new Button{Point{0, 0}, 0, 0, "exp", [](Address, Address pw) { reference_to<Plot_window>(pw).show_function_equation(Graph_type::exp); }});
    attach(select_menu);
    attach(menu_button);
    select_menu.hide();  // default: hide menu items

    axes.push_back(new Axis{Axis::x, Point{10, y_orig}, x_axis_length, static_cast<int>(x_axis_length / x_scale), "range [-10:11)"});
    axes.push_back(new Axis{Axis::y, Point{x_orig, y_axis_length + 40}, y_axis_length, static_cast<int>(y_axis_length / y_scale), "one notch == 1"});
    // attach the parts to the window
    axes[0].label.move(-220, 5);
    axes[1].label.move(30, 10);
    axes[0].set_color(Color{208});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
    axes[1].set_color(Color{242});
    attach(axes[0]);  // x axis
    attach(axes[1]);  // y axis

    // set defaults
    toggle_parameter_input(false, false, false);  // hide all parameter input boxes
    output_equation.put(" select a graph -->");
    redraw();
}

void Plot_window::show_function_equation(Graph_type function_name) {
    switch (function_name) {
        case Graph_type::linear:
            output_equation.put("y = ax + b");
            selected_graph = Graph_type::linear;
            toggle_parameter_input(true, true, false);
            break;

        case Graph_type::quadratic:
            output_equation.put("y = ax^2 + bx + c");
            selected_graph = Graph_type::quadratic;
            toggle_parameter_input(true, true, true);
            break;

        case Graph_type::cubic:
            output_equation.put("y = ax^3 + bx^2 + cx");  // did not implement parameter for the constant
            selected_graph = Graph_type::cubic;
            toggle_parameter_input(true, true, true);
            break;

        case Graph_type::sin:
            output_equation.put("y = a * sin(bx) + c");
            selected_graph = Graph_type::sin;
            toggle_parameter_input(true, true, true);
            break;

        case Graph_type::cos:
            output_equation.put("y = a * cos(bx) + c");
            selected_graph = Graph_type::cos;
            toggle_parameter_input(true, true, true);
            break;

        case Graph_type::tan:
            output_equation.put("y = a * tan(bx) + c");
            selected_graph = Graph_type::tan;
            toggle_parameter_input(true, true, true);
            break;

        case Graph_type::log:
            output_equation.put("y = log(x)");
            selected_graph = Graph_type::log;
            toggle_parameter_input(false, false, false);
            break;

        case Graph_type::exp:
            output_equation.put("y = exp(x)");
            selected_graph = Graph_type::exp;
            toggle_parameter_input(false, false, false);
            break;

        default:
            error("error: Polygon_window::draw_shape argument is wrong");
    }
    // redraw();
    hide_menu();
}

void Plot_window::clear() {
    for (int i = 0; i < graphs.size(); ++i) {
        detach(graphs[i]);
    }
    redraw();
}

void Plot_window::plot() {
    switch (selected_graph) {
        case Graph_type::none:
            output_equation.put(" select a graph first!");
            return;  // to ask user to click the select menu first to plot the graph

        case Graph_type::linear:
            set_parameter_values(true, true, false);
            graphs.push_back(new Function{calc_linear, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::quadratic:
            set_parameter_values(true, true, true);
            graphs.push_back(new Function{calc_quadratic, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::cubic:
            set_parameter_values(true, true, true);
            graphs.push_back(new Function{calc_cubic, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::sin:
            set_parameter_values(true, true, true);
            graphs.push_back(new Function{calc_sin, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::cos:
            set_parameter_values(true, true, true);
            graphs.push_back(new Function{calc_cos, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::tan:
            set_parameter_values(true, true, true);
            graphs.push_back(new Function{calc_tan, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::log:
            // no need for set_parameter_values() function as it does not need parameters
            graphs.push_back(new Function{log, 0.000001, r_max, orig, n_points, x_scale, y_scale});
            break;

        case Graph_type::exp:
            // no need for set_parameter_values() function as it does not need parameters
            graphs.push_back(new Function{exp, r_min, r_max, orig, n_points, x_scale, y_scale});
            break;
        default:
            error("error: Plot_window: something wrong with Graph_type::selected_graph variable");
    }

    random_device rd;                                                    // https://en.cppreference.com/w/cpp/numeric/random/random_device
    mt19937_64 gen(rd());                                                // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    uniform_int_distribution<int> rd_color{0, 24};                       // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    graphs[graphs.size() - 1].set_color(Color{59 + rd_color(gen) * 8});  // https://www.fltk.org/doc-1.3/fltk-colormap.png
    graphs[graphs.size() - 1].set_style(Line_style{Line_style::solid, 2});
}

void Plot_window::hide_menu() {
    select_menu.hide();
    menu_button.show();
}

void Plot_window::menu_pressed() {
    menu_button.hide();
    select_menu.show();
}

void Plot_window::toggle_parameter_input(bool a, bool b, bool c) {
    if (a)
        parameter_a.show();
    else
        parameter_a.hide();
    if (b)
        parameter_b.show();
    else
        parameter_b.hide();
    if (c)
        parameter_c.show();
    else
        parameter_c.hide();
    // redraw();
};

void Plot_window::set_parameter_values(bool a, bool b, bool c) {
    // get_int() returns -999999 when it is not a digit
    if (a) coef_a = stod(parameter_a.get_string());
    if (b) coef_b = stod(parameter_b.get_string());
    if (c) coef_b = stod(parameter_c.get_string());
}

int main() {
    try {
        Plot_window win{Point{100, 100}, 800, 800, "Calculator with GUI"};
        return gui_main();

    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}
