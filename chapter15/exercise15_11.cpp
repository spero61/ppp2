// Find the average maximum temperatures for each month of the year for two or more locations.

// REVIEW needed: This code can be improved by defining more small classes well organized.
// I did use small classes and defined one, City_Index, as the author recommended in the book. (see p.489)
// And indeed it was helpful to make a coherent "city index" and made the code more structured.
// However, I decided not to dig too deep to solve this exercise as its name implicated, this is just "an exercise."
// I might come back and redesign the exercise later to make the code elegant.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

struct Avg_Max_Temp {
    int month;
    double helsinki, sapporo, seoul, auckland, new_york;
};

istream& operator>>(istream& is, Avg_Max_Temp& amt)
// assume format: ( year : young middle old )
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Avg_Max_Temp tmp;
    if (is >> ch1 >> tmp.month >> ch2 >> tmp.helsinki >> tmp.sapporo >> tmp.seoul >> tmp.auckland >> tmp.new_york >> ch3) {
        if (ch1 != '(' || ch2 != ':' || ch3 != ')') {
            is.clear(ios_base::failbit);
            return is;
        }
    } else
        return is;
    amt = tmp;
    return is;
}

class Scale {  // data value to coordinate conversion
   public:
    Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} {}
    int operator()(int v) const {  // see 21.4 Function objects
        return static_cast<int>(cbase + (v - vbase) * scale);
    }

   private:
    int cbase;  // coordinate base
    int vbase;  // base of values
    double scale;
};

class City_Index : public Shape {
   public:
    City_Index(Point orig_arg, vector<string> city_names, vector<int> city_colors);
    void draw_lines() const override;

   private:
    Vector_ref<Text> city_texts;
    Vector_ref<Line> city_lines;
    Point orig;
};

City_Index::City_Index(Point orig_arg, vector<string> city_names, vector<int> city_colors) : orig{orig_arg} {
    // basic sanity check
    if (city_names.size() != city_colors.size())
        error("error: wrong City_Index arguments: city_names.size() != city_colors.size()");

    const int x_interval{80};
    const int y_interval{50};
    for (int i = 0; i < city_names.size(); ++i) {
        // initialize Vector_ref<Text> city_texts
        city_texts.push_back(new Text{Point{orig.x + x_interval * 1, orig.y + (i * y_interval)}, city_names[i]});
        city_texts[city_texts.size() - 1].set_color(Color{37});  // default: gray_color
        city_texts[city_texts.size() - 1].set_font(Font::helvetica_bold);

        // initialize Vector_ref<Line> city_lines
        const int y_city_lines{orig.y + (i * y_interval) - 5};  // -5 is adjustment value to make the line vertically centered for its text
        city_lines.push_back(new Line{Point{orig.x + x_interval * 2, y_city_lines}, Point{orig.x + x_interval * 3, y_city_lines}});
        city_lines[city_lines.size() - 1].set_color(Color{city_colors[i]});
        city_lines[city_lines.size() - 1].set_style(Line_style{Line_style::solid, 3});
    }
}

void City_Index::draw_lines() const {
    // basic sanity check
    if (city_texts.size() != city_lines.size())
        error("error: City_Index draw_lines(): city_texts.size() != city_lines.size()");

    for (int i = 0; i < city_texts.size(); ++i) {
        city_texts[i].draw();
        city_lines[i].draw();
    }
}

int main() {
    try {
        constexpr int xmax{1200};  // window size
        constexpr int ymax{800};

        constexpr int xoffset{80};  // distance from left-hand side of window to y axis
        constexpr int yoffset{60};  // distance from bottom of window to x axis

        constexpr int xspace{200};  // space beyond axis
        constexpr int yspace{40};

        constexpr int xlength{xmax - xoffset - xspace};  // length of axes
        constexpr int ylength{ymax - yoffset - yspace};

        constexpr int start_month{1};
        constexpr int end_month{12};

        constexpr double min_temp_limit{-60.0};  // for basic sanity check
        constexpr double max_temp_limit{60.0};   // in degrees Celsius
        constexpr int max_temp_graph{40};        // for scaling values fit to the graph
        constexpr int min_temp_graph{-20};       // in degrees Celsius

        constexpr int y_temp_max{ylength};
        constexpr int y_interval{5};
        constexpr int y_temp_unit{static_cast<int>((ylength / (max_temp_graph - min_temp_graph)) / y_interval)};  // each notch is every five degrees Celcius

        constexpr double xscale = double(xlength) / (end_month - start_month);
        constexpr double yscale = double(ylength) / (max_temp_graph - min_temp_graph);

        constexpr int gray_color{37};
        constexpr int dot_radius{5};  // radius for Vector_ref<Circle> cityname_dots

        Scale xs{xoffset, start_month, xscale};
        Scale ys{ymax - yoffset, min_temp_graph, -yscale};

        Point tl{100, 100};
        Simple_window win{tl, xmax, ymax, "Average Maximum Temperatures"};
        win.wait_for_button();

        Point orig{xoffset, ymax - yoffset};
        Axis x{Axis::x, Point{orig.x, ys(0) + 2}, xlength, end_month - start_month, "Month"};  // + 2 is adjustment value stemmed from narrow conversion from double to int
        Axis y{Axis::y, orig, ylength, (max_temp_graph - min_temp_graph) / y_interval, "temp(Celcius)"};
        x.label.set_font(Font::helvetica_bold);
        y.label.set_font(Font::helvetica_bold);
        x.label.set_color(Color{gray_color});
        y.label.set_color(Color{gray_color});
        x.label.set_font_size(20);
        y.label.set_font_size(20);
        x.label.move(665, 25);
        y.label.move(-58, -8);

        // add title label
        Point br{xmax - xspace - 270, ymax - yspace - 20};  // bottom-right
        Text title_label{br, "Average Max Temperatures by Month"};
        title_label.set_font_size(24);
        title_label.set_font(Font::helvetica_bold);
        title_label.set_color(Color{gray_color});

        win.attach(x);  // x axis
        win.attach(y);  // y axis
        win.attach(title_label);
        win.wait_for_button();

        // value expressed in a line graph
        Open_polyline helsinki;
        Open_polyline sapporo;
        Open_polyline seoul;
        Open_polyline auckland;
        Open_polyline new_york;

        // value expressed in dots
        Vector_ref<Circle> helsinki_dots;
        Vector_ref<Circle> sapporo_dots;
        Vector_ref<Circle> seoul_dots;
        Vector_ref<Circle> auckland_dots;
        Vector_ref<Circle> new_york_dots;

        vector<string> month_texts{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        vector<string> temp_texts{"-15", "-10", "-5", "0", "5", "10", "15", "20", "25", "30", "35", "40"};

        Vector_ref<Text> month_labels;
        Vector_ref<Text> temp_labels;
        Vector_ref<Line> northings;  // horizontal grid lines

        string file_name = "temperature-data.txt";
        ifstream ifs{file_name};
        if (!ifs) error("can't open ", file_name);
        for (Avg_Max_Temp amt; ifs >> amt;) {
            // basic sanity checks
            if (amt.month < start_month || end_month < amt.month)
                error("month out of range");
            if (amt.helsinki < min_temp_limit || amt.helsinki > max_temp_limit)
                error("Helsinki: temperature out of range");
            if (amt.sapporo < min_temp_limit || amt.sapporo > max_temp_limit)
                error("Sapporo: temperature out of range");
            if (amt.seoul < min_temp_limit || amt.seoul > max_temp_limit)
                error("Seoul: temperature out of range");
            if (amt.auckland < min_temp_limit || amt.auckland > max_temp_limit)
                error("Auckland: temperature out of range");
            if (amt.new_york < min_temp_limit || amt.new_york > max_temp_limit)
                error("New York: temperature out of range");
            const int x = xs(amt.month);

            // month labels on x axis
            month_labels.push_back(new Text{Point{x - 18, ys(0) + 20}, month_texts[amt.month - 1]});
            month_labels[month_labels.size() - 1].set_font_size(18);
            month_labels[month_labels.size() - 1].set_color(Color{gray_color});
            win.attach(month_labels[month_labels.size() - 1]);

            // temperature labels on y axis
            const int temp_label_int{stoi(temp_texts[amt.month - 1])};
            const int x_temp_label = (-10 < temp_label_int && temp_label_int < 10) ? orig.x - 40 : orig.x - 47;  // deal with -5, 0, 5 temp_label adjustment
            const int y_temp_label = ys(temp_label_int) + 10;                                                    // + 10  is adjustment value
            temp_labels.push_back(new Text{Point{x_temp_label, y_temp_label}, temp_texts[amt.month - 1]});
            temp_labels[temp_labels.size() - 1].set_font_size(18);
            temp_labels[temp_labels.size() - 1].set_color(Color{gray_color});
            win.attach(temp_labels[temp_labels.size() - 1]);

            // create local variable "Point"s
            Point helsinki_p{x, static_cast<int>(ys(amt.helsinki))};
            Point sapporo_p{x, static_cast<int>(ys(amt.sapporo))};
            Point seoul_p{x, static_cast<int>(ys(amt.seoul))};
            Point auckland_p{x, static_cast<int>(ys(amt.auckland))};
            Point new_york_p{x, static_cast<int>(ys(amt.new_york))};

            // add(Point p) for each Open_polyline of the city : a line graph
            helsinki.add(helsinki_p);
            sapporo.add(sapporo_p);
            seoul.add(seoul_p);
            auckland.add(auckland_p);
            new_york.add(new_york_p);

            // add(Point p) for each Circle to corresponding Vector_ref<Circle> : a dot
            helsinki_dots.push_back(new Circle{helsinki_p, dot_radius});
            sapporo_dots.push_back(new Circle{sapporo_p, dot_radius});
            seoul_dots.push_back(new Circle{seoul_p, dot_radius});
            auckland_dots.push_back(new Circle{auckland_p, dot_radius});
            new_york_dots.push_back(new Circle{new_york_p, dot_radius});

            // draw horizontal grid lines (northings)
            // adjustment for y since Point only takes int, there are rounding errors
            const int y_northings = (amt.month < 10) ? y_temp_label - 8 : y_temp_label - 6;
            northings.push_back(new Line{Point{orig.x, y_northings}, Point{orig.x + xlength, y_northings}});
            northings[northings.size() - 1].set_style(Line_style::dot);
            northings[northings.size() - 1].set_color(Color{gray_color});
            win.attach(northings[northings.size() - 1]);
        }

        // https://www.fltk.org/doc-1.3/fltk-colormap.png
        constexpr int helsinki_color{139};
        constexpr int sapporo_color{109};
        constexpr int seoul_color{174};
        constexpr int auckland_color{132};
        constexpr int new_york_color{170};

        // Labeling each city's name and its color line using class City_Index
        vector<int> city_colors{helsinki_color, sapporo_color, seoul_color, auckland_color, new_york_color};
        vector<string> city_names{"Helsinki", "Sapporo", "Seoul", "Auckland", "New York"};
        City_Index ci_legend{Point{xmax - xspace - 60, 70}, city_names, city_colors};
        win.attach(ci_legend);

        // for simplicity put Open_polyline objects to cities
        Vector_ref<Open_polyline> cities;
        cities.push_back(helsinki);
        cities.push_back(sapporo);
        cities.push_back(seoul);
        cities.push_back(auckland);
        cities.push_back(new_york);
        for (int i = 0; i < cities.size(); ++i) {
            cities[i].set_color(Color{city_colors[i]});
            cities[i].set_style(Line_style{Line_style::solid, 3});
            win.attach(cities[i]);
        }
        win.wait_for_button();

        // leave out sanity checks for now
        // assume: all Vector_ref<Circle> cityname_dots's size is the same
        for (int i = 0; i < helsinki_dots.size(); ++i) {
            helsinki_dots[i].set_color(Color{helsinki_color});
            helsinki_dots[i].set_fill_color(Color{helsinki_color});
            sapporo_dots[i].set_color(Color{sapporo_color});
            sapporo_dots[i].set_fill_color(Color{sapporo_color});
            seoul_dots[i].set_color(Color{seoul_color});
            seoul_dots[i].set_fill_color(Color{seoul_color});
            auckland_dots[i].set_color(Color{auckland_color});
            auckland_dots[i].set_fill_color(Color{auckland_color});
            new_york_dots[i].set_color(Color{new_york_color});
            new_york_dots[i].set_fill_color(Color{new_york_color});
            win.attach(helsinki_dots[i]);
            win.attach(sapporo_dots[i]);
            win.attach(seoul_dots[i]);
            win.attach(auckland_dots[i]);
            win.attach(new_york_dots[i]);
        }
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