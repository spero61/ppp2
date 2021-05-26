// Compare the two vectors and print Something's wrong!
// if the number of elements or the values of elements differ.

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

// comparison operator overloading for Point
bool operator==(const Point& a, const Point& b) {
    return ((a.get_x() == b.get_x()) && (a.get_y() == b.get_y()));
}

// comparison operator overloading for vector<Point>
bool operator==(const vector<Point>& a, const vector<Point>& b) {
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); ++i) {
        if ((a[i].get_x() != b[i].get_x()) || (a[i].get_y() != b[i].get_y()))
            return false;
    }
    return true;
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

        cout << "orginal_points: \n";
        for (Point p : original_points) {
            cout << p << '\n';
        }

        cout << '\n';
        cout << "processed_points: \n";
        for (Point p : processed_points) {
            cout << p << '\n';
        }

        // first trial: should be the same
        if (original_points != processed_points) {
            cerr << "Something's wrong!\n";
        } else {
            cout << "two vectors are the same\n";
        }

        // manipulate the first element of vector<Point> processed_points
        cout << '\n';
        cout << "please provide different value than ";
        cout << processed_points[0] << '\n';
        cout << "processed_points[0]: ";
        cin >> processed_points[0];

        //second trial: should be different
        if (original_points != processed_points) {
            cerr << "Something's wrong!\n";
        } else {
            cout << "two vectors are the same\n";
        }

        // check if the manipulation has been made correctly
        cout << '\n';
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