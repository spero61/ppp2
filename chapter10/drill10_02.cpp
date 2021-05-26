// Using the code and discussion in §10.4, prompt the user to input seven (x,y) pairs.
// As the data is entered, store it in a vector of Points called original_points.

// Comment:
// As we develop the idea through out the drills,
// error handlings for invalid input for a Point are not implemented here.

#include "std_lib_facilities.h"

class Point {
   public:
    Point(double xx, double yy) : x{xx}, y{yy} {}
    Point() : x{0.0}, y{0.0} {}
    double get_x() const { return x; }
    double get_y() const { return y; }

   private:
    double x, y;
};

istream& operator>>(istream& is, Point& p) {
    double x, y;
    char ch1, ch2, ch3;
    is >> ch1 >> x >> ch2 >> y >> ch3;

    if (!is) return is;
    if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
        is.clear(ios_base::failbit);
        return is;
    }
    p = Point{x, y};
    return is;
}

ostream& operator<<(ostream& os, const Point& p) {
    return os << '(' << p.get_x() << ',' << p.get_y() << ')';
}

int main() {
    try {
        vector<Point> original_points(7);  // seven elements each with the (default) value (0.0, 0.0)

        cout << "Provide inputs of seven (x,y) pairs.\n"
             << "Note that a space between characters is not allowed\n";

        for (int i = 0; i < original_points.size(); ++i) {
            Point tmp;
            if (cin >> tmp) {
                original_points[i] = tmp;
            }
            // error handling code
            // see drill10_03
        }

        cout << '\n';
        cout << "Result: \n";
        for (Point p : original_points) {
            cout << p << '\n';
        }
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}