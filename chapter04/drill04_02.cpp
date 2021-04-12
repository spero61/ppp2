// ch4 drill from number 6 to 8
#include "std_lib_facilities.h"

int main()
{
    double val = 0;
    double smallest, largest;
    int count = 0;

    constexpr double m_per_cm = 100;
    constexpr double in_per_cm = 2.54;
    constexpr double ft_per_cm = 12 * in_per_cm;
    string unit = " ";

    double sum = 0;

    cout << "Please enter a number and a unit(cm, m, in, or ft).\n";

    while (cin >> val >> unit)
    {
        if (unit == "cm" || unit == "m" || unit == "in" || unit == "ft")
        {
            // convert values in cm using constant expressions
            if (unit == "m")
            {
                val *= m_per_cm;
            }
            else if (unit == "in")
            {
                val *= in_per_cm;
            }
            else if (unit == "ft")
            {
                val *= ft_per_cm;
            }

            // initialize the smallest and largest variables for the first round
            if (count == 0)
            {
                smallest = val;
                largest = val;
                ++count;
            }
            else
            {
                if (val < smallest)
                {
                    smallest = val;
                }
                if (val > largest)
                {
                    largest = val;
                }
            }

            // print results
            cout << "the value you entered in cm : " << val << " cm\n"
                 << "the smallest so far in cm: " << smallest << " cm\n"
                 << "the largest so far in cm: " << largest << " cm\n";

            // keep track of the sum of values entered
            sum += val;
        }

        // exclude illegal unit input
        else
        {
            cout << "illegal unit indicator. Try again.\n";
        }
    }
}