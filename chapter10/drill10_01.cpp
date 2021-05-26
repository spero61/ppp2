// Start a program to work with points, discussed in §10.4.
// Begin by defining the data type Point that has two coordinate members x and y.

#include "std_lib_facilities.h"

class Point {
   public:
    Point(double xx, double yy) : x{xx}, y{yy} {}
    double get_x() const { return x; }
    double get_y() const { return y; }

   private:
    double x, y;
};

int main() {
    try {
        Point p{3.14, 2.718};
        cout << '(' << p.get_x() << ", " << p.get_y() << ')' << '\n';
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}