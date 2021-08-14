#include "std_lib_facilities.h"

void print_array(ostream& os, int* a, int n) {
    for (int i = 0; i < n; ++i) {
        os << a[i] << '\t';
    }
    os << '\n';
}

void print_vector(ostream& os, vector<int> vi) {
    for (int i = 0; i < vi.size(); ++i) {
        os << vi[i] << '\t';
    }
    os << '\n';
}

int main() {
    try {
        int num{7};
        int* p1{&num};
        cout << " p1: " << p1 << '\n'
             << "*p1: " << *p1 << "\n\n";

        int* p2{new int[7]{1, 2, 4, 8, 16, 32, 64}};
        cout << " p2: " << p2 << '\n'
             << "*p2: " << *p2 << '\n';  // *p2 is the same as p2[0]

        cout << "the array p2 points to:\n";
        print_array(cout, p2, 7);
        cout << '\n';

        int* p3{p2};
        p2 = p1;
        p2 = p3;
        cout << " p1: " << p1 << '\n'
             << " p2: " << p2 << '\n'
             << " p3: " << p3 << "\n\n";

        delete[] p2;

        p1 = new int[10]{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
        p2 = new int[10];
        for (int i = 0; i < 10; ++i) {
            p2[i] = p1[i];
        }
        print_array(cout, p1, 10);
        print_array(cout, p2, 10);

        vector<int> v1{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
        vector<int> v2{v1};
        print_vector(cout, v1);
        print_vector(cout, v2);

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
