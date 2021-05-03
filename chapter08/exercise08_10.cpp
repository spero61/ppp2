// Write a function maxv() that returns the largest element of a vector argument.

#include "std_lib_facilities.h"

// pass-by-value so that the original vector remains the same
double maxv(vector<double> v);

int main()
{
    vector<double> now{2021, 5, 3, 18, 14, 1987, 33, 100};
    cout << "largest element: " << maxv(now) << '\n';
}

double maxv(vector<double> v)
{
    sort(v);                // sorting in ascending order
    return v[v.size() - 1]; // return the last element
}