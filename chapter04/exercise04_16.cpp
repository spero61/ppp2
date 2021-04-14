// a program that, given a set of positive integers, finds the mode
#include "std_lib_facilities.h"

int main()
{
    vector<int> natural_numbers = {10, 13, 14, 16, 15, 17, 17, 5, 3, 5, 5, 17, 5, 5, 4, 5, 3, 1, 3, 7};
    vector<int> modes;
    vector<int> mode_counts;

    sort(natural_numbers);

    int count = 0;

    int mode = -1;
    int mode_cadidate = -1;
    int frequency = 0;

    // index starts from 1 not 0 due to the comparison of i th and (i - 1) th element
    for (int i = 1; i < natural_numbers.size(); ++i)
    {

        if (natural_numbers[i] == natural_numbers[i - 1])
        {
            mode_cadidate = natural_numbers[i];
            ++count;
        }

        // (natural_numbers[i] != natural_numbers[i - 1])
        else
        {
            if (count != 0)
            {
                if (count > frequency)
                {
                    // due to the fact that count of this algorithm is equal to (frequency - 1)
                    frequency = count + 1;
                    mode = mode_cadidate;
                }
                count = 0;
            }
        }
    }

    cout << "mode is " << mode << " and it appears " << frequency << " times\n";
}