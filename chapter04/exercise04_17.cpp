// a program that finds the min, max, and mode of a sequence of strings.
#include "std_lib_facilities.h"

int main()
{
    vector<string> words = {"moi", "moi", "terve", "moi", "moi", "hei", "hei"};
    vector<int> modes;
    vector<int> mode_counts;

    sort(words);

    int count = 0;

    string mode = " ";
    string mode_cadidate = " ";
    int frequency = 0;

    // index starts from 1 not 0 due to the comparison of i th and (i - 1) th element
    for (int i = 1; i < words.size(); ++i)
    {

        if (words[i] == words[i - 1])
        {
            mode_cadidate = words[i];
            ++count;
        }

        // (words[i] != words[i - 1])
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

    cout << "min of words is " << words[0] << '\n';
    cout << "max words is " << words[words.size() - 1] << '\n';
    cout << "mode words is " << mode << " and it appears " << frequency << " times\n";
}