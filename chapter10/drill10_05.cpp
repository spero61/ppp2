// Close the ofstream and then open an ifstream for mydata.txt.
// Read the data from mydata.txt and store it in a new vector called processed_points.

// Comment:
// Alternatively fill_from_file function can be used from the textbook of 10.4.
// Bjarne, Stroustrup. Programming (p. 351). Pearson Education. Kindle Edition.

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

void fill_from_file(vector<Point>& points, const string& iname) {
    ifstream ist{iname};
    if (!ist) error("can't open input file ", iname);

    for (Point p; ist >> p;) {
        points.push_back(p);
    }
    // the file is implicitly closed when we leave the function
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

        fstream fs;
        fs.open(filename, ios_base::out);
        if (!fs) error("impossible");

        for (Point p : original_points) {
            fs << p << '\n';
        }
        fs.close();

        cout << "Output file: " << filename << '\n';
        cout << '\n';

        vector<Point> processed_points;

        // fs.open(filename, ios_base::in);
        // if (!fs) error("impossible");

        // for (Point p; fs >> p;) {
        //     processed_points.push_back(p);
        // }
        // fs.close();

        // Opening the file implicitly as part of the creation of
        // an ostream or an istream and relying on the scope of the stream
        // to take care of closing the file is the ideal. (page 351)
        fill_from_file(processed_points, filename);

        cout << "processed_points: \n";
        for (Point p : processed_points) {
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