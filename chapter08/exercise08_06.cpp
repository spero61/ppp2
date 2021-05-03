// Write versions of the functions from exercise 5,
// but with a vector<string>

#include "std_lib_facilities.h"

vector<string> reverse_first(const vector<string> &v);    // leaving its original vector unchanged
vector<string> reverse_second(vector<string> &v);         // reverse the elements of its vector without using any other vectors
void print_result(string label, const vector<string> &v); //v is passed-by-const-reference for performance

int main()
{
    try
    {
        vector<string> example_odd{"apple", "banana", "cherry", "dragonfruit", "elderberry"};

        vector<string> result_first = reverse_first(example_odd);
        print_result("example_odd", example_odd);
        print_result("result_first", result_first);

        vector<string> result_second = reverse_second(example_odd);
        print_result("example_odd", example_odd);
        print_result("result_second", result_second);

        cout << '\n';

        vector<string> example_even{"apple", "banana", "cherry", "dragonfruit", "elderberry", "fig"};

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

vector<string> reverse_first(const vector<string> &v)
{
    vector<string> v_copy = v;
    int last_index = v_copy.size() - 1;
    for (int i = 0; i < v_copy.size() / 2; ++i)
    {
        swap(v_copy[i], v_copy[last_index - i]);
    }
    return v_copy;
}

vector<string> reverse_second(vector<string> &v)
{
    int last_index = v.size() - 1;
    for (int i = 0; i < v.size() / 2; ++i)
    {
        swap(v[i], v[last_index - i]);
    }
    return v;
}

void print_result(string label, const vector<string> &v)
{
    cout << label << ":\t";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';
    cout << '\n';
}