// Write a function that finds the smallest and the largest element of a vector argument
// and also computes the mean and the median. Do not use global variables.
// Either return a struct containing the results or pass them back through reference arguments.

// Q. Which of the two ways of returning several result values do you prefer and why?
// A. I prefer the former as user-defined-type is the heart of C++.

#include "std_lib_facilities.h"

struct Statistics
{
    double min{0};
    double max{0};
    double mean{0};
    double median{0};
};

Statistics compute_statistics(const vector<double> &v); // pass-by-const-reference
void print_result(struct Statistics stats);

int main()
{
    try
    {

        cout << "~ even number of elements ~\n";
        vector<double> elements_even{1, -2, 5, 6, 12, 7};
        print_result(compute_statistics(elements_even));

        cout << '\n';

        cout << "~ odd number of elements ~\n";
        vector<double> elements_odd{2021, 5, 3, 19, 20};
        print_result(compute_statistics(elements_odd));
        return 0;
    }
    catch (exception &e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "...Exception\n";
        return 2;
    }
}

Statistics compute_statistics(const vector<double> &v)
{
    // take a copy of v for computations
    vector<double> tmp = v;

    sort(tmp);

    Statistics stats;

    stats.min = tmp[0];
    stats.max = tmp[tmp.size() - 1];

    double sum;
    for (int i = 0; i < tmp.size(); ++i)
    {
        sum += tmp[i];
    }
    stats.mean = sum / tmp.size();

    // median for even number of elements
    if (tmp.size() % 2 == 0)
    {
        stats.median = (tmp[tmp.size() / 2] + tmp[tmp.size() / 2 - 1]) / 2;
    }
    // median for odd number of elements
    else
        stats.median = tmp[tmp.size() / 2];

    // return a struct containing the results
    return stats;
}

void print_result(struct Statistics stats)
{
    cout << "min: " << stats.min << '\n';
    cout << "max: " << stats.max << '\n';
    cout << "mean: " << stats.mean << '\n';
    cout << "median: " << stats.median << '\n';
}