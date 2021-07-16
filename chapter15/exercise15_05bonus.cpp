// Approximation of the PI value using sum of Leibniz's series

#include "std_lib_facilities.h"

constexpr double PI{3.1415926535897932384626433};

double term(int n) {  // n th term of the leibniz_series
    if (n == 1)
        return 1;
    else if (n % 2 == 0)
        return -1.0 / (2 * n - 1);
    return 1.0 / (2 * n - 1);
}

double leibniz_series(int n) {
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += term(i);
    }
    return sum;
}

int main() {
    try {
        int start{1};
        int end{2};
        while (end > start) {
            cout << "Sum of the 'n'th term of the Leibniz series\n"
                    "Enter 'start' value (positive integer)\n> ";
            cin >> start;
            cout << "Provide 'end' value (positive integer)\n> ";
            cin >> end;
            const int setw_val = static_cast<int>(log10(end) + 1);
            for (int i = start; i <= end; ++i) {
                cout << fixed << setprecision(10) << '[' << setw(setw_val) << i << "]: PI approx: " << 4 * leibniz_series(i) << '\n';
            }
            cout << '\n';
        }
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
