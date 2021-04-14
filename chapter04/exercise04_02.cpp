// fix the program in 4.6.3 so that it always prints out a median.

#include "std_lib_facilities.h"

int main()
{
    cout << "Please enter temperatures followed by enter.\n"
         << "or separated by space. Press | then enter for excape.\n";
    vector<double> temps;
    for (double temp; cin >> temp;)
    {
        temps.push_back(temp);
    }

    double sum = 0;
    for (double x : temps)
    {
        sum += x;
    }

    cout << "Average temperature: " << sum / temps.size() << '\n';

    sort(temps);

    double median = 0;

    // if number of temperatures given are even number
    // note that vector index starts from 0 not 1
    if (temps.size() % 2 == 0)
    {
        median = (temps[(temps.size() / 2) - 1] + temps[(temps.size() / 2)]) / 2;
    }
    else
    {
        median = temps[((temps.size() + 1) / 2) - 1];
    }
    cout << "Median temperature: " << median << '\n';
}