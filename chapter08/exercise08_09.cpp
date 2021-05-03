// Write a function that given two vector<double>s price and weight computes a value (an “index”)
// that is the sum of all price[i]*weight[i]. Make sure to have weight.size()==price.size().

#include "std_lib_facilities.h"

double compute_sum(const vector<double> &price, const vector<double> &weight);

int main()
{
    vector<double> price{1000, 1500, 2000, 3000};
    vector<double> weight{0.5, 4, 1, 4.5};

    cout << "sum: " << compute_sum(price, weight) << '\n';
}

double compute_sum(const vector<double> &price, const vector<double> &weight)
{
    int number_of_items = price.size();
    if (number_of_items != weight.size())
        error("make sure to have weight.size()==price.size()");

    double sum{0};
    for (int i = 0; i < number_of_items; ++i)
        sum += price[i] * weight[i];

    return sum;
}