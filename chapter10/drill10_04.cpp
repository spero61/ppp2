// Open an ofstream and output each point to a file named mydata.txt
// On windows, we suggest the .txt suffix to make it easier to look at the data
// with an ordinary text editor (such as WordPad).

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

        int index = 0;
        while (index < original_points.size()) {
            Point tmp;
            cout << index + 1 << ": original_points[" << index << "]: ";
            cin >> tmp;
            if (!cin) {
                if (cin.bad()) error("cin is bad");
                if (cin.fail()) {
                    cerr << "Please provide valid input\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } else {
                original_points[index] = tmp;
                ++index;
            }
        }

        cout << "Please enter [filename].txt\n";
        string filename;
        cin >> filename;

        // ofstream ost{filename};
        // if (!ost) error("con't open output file ", filename);

        // for (Point p : original_points) {
        //     ost << p << '\n';
        // }
        // ost.close();

        fstream fs;
        fs.open(filename, ios_base::out);
        if (!fs) error("impossible");

        for (Point p : original_points) {
            fs << p << '\n';
        }
        fs.close();

        cout << "Output file: " << filename << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}