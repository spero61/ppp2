// introducing, "recursive" ! (feat. factorial function)

// A: I prefer recursive over iterative because it is more elegant.

#include "std_lib_facilities.h"

// iterative
double old_fac(int n) {
    double r = 1;
    while (n > 1) {
        r *= n;
        n--;
    }
    return r;
}

// recursive
double fac(int n) {
    return n > 1 ? n * fac(n - 1) : 1;
}

bool is_same_vector(vector<double> lhs, vector<double> rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (int i = 0; i < rhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

int main() {
    try {
        vector<double> iterative_fac;
        for (int i = 0; i <= 20; ++i) {
            double tmp = old_fac(i);
            cout << "old_fac(" << i << "): " << tmp << '\n';
            iterative_fac.push_back(tmp);
        }

        cout << '\n';

        vector<double> recursive_fac;
        for (int i = 0; i <= 20; ++i) {
            double tmp = fac(i);
            cout << "fac(" << i << "): " << fac(i) << '\n';
            recursive_fac.push_back(tmp);
        }

        if (is_same_vector(iterative_fac, recursive_fac))
            cout << "same\n";
        else
            cout << "different\n";

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
