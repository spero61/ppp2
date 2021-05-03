// Write two functions that reverse the order of elements in a vector<int>
// For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1

#include "std_lib_facilities.h"

vector<int> reverse_first(const vector<int> &v);       // leaving its original vector unchanged
vector<int> reverse_second(vector<int> &v);            // reverse the elements of its vector without using any other vectors
void print_result(string label, const vector<int> &v); // v is passed-by-const-reference for performance

int main()
{
    try
    {
        vector<int> example_odd{1, 3, 5, 7, 9};

        vector<int> result_first = reverse_first(example_odd);
        print_result("example_odd", example_odd);
        print_result("result_first", result_first);

        vector<int> result_second = reverse_second(example_odd);
        print_result("example_odd", example_odd);
        print_result("result_second", result_second);

        cout << '\n';

        vector<int> example_even{0, 2, 4, 6, 8, 10};

        result_first = reverse_first(example_even);
        print_result("example_even", example_even);
        print_result("result_first", result_first);

        result_second = reverse_second(example_even);
        print_result("example_even", example_even);
        print_result("result_second", result_second);

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

vector<int> reverse_first(const vector<int> &v)
{
    vector<int> v_copy = v;
    int last_index = v_copy.size() - 1;
    for (int i = 0; i < v_copy.size() / 2; ++i)
    {
        swap(v_copy[i], v_copy[last_index - i]);
    }
    return v_copy;
}

vector<int> reverse_second(vector<int> &v)
{
    int last_index = v.size() - 1;
    for (int i = 0; i < v.size() / 2; ++i)
    {
        swap(v[i], v[last_index - i]);
    }
    return v;
}

void print_result(string label, const vector<int> &v)
{
    cout << label << ":\t";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';
    cout << '\n';
}