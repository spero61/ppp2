// Design a program that asks users for two numbers, asks them whether they want to calculate
// permutations or combinations, and prints out the result.

#include "std_lib_facilities.h"

// factorial operation
int factorial(int n)
{
    int factorial = 1;
    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
    }
    return factorial;
}

// permutation operation
int permutation(int a, int b)
{
    return factorial(a) / factorial(a - b);
}

// computation operation
int computation(int a, int b)
{
    return permutation(a, b) / factorial(b);
}

int main()
{
    try
    {

        int a;
        int b;
        cout << "~ Welcome to permutation, computation calculator ~\n";

        // take user input of two positive integers (int a, int b)
        cout << "Please enter two positive integers, a and b, for operation\n"
             << "numbers are seperated by space and a must be greater than b (e.g.,  5 3 )\n";
        while (true)
        {
            cin >> a >> b;

            if (a <= 0 || b <= 0)
                cerr << "a and b should be positive integers\n";
            else if (a <= b)
                cerr << "a must be greater than b\n";
            // if a and b are positive integer and a is greater than b
            else
                break;
        }

        int result = 0;
        char selection = ' ';
        bool is_chosen = false;
        string chosen = "";

        cout << "Which operation would you like to execute?\n";
        while (!is_chosen)
        {
            // asks users to choose between permutation and computation ('p' or 'c')
            cout << "press p or P followed by enter for permutation,\n"
                 << "press c or C followed by enter for computation.\n";
            cin >> selection;

            if (selection == 'P' || selection == 'C')
            {

                // toLower -> lowercase letter + 32
                selection += 32;
            }

            switch (selection)
            {
            // permutation is chosen call the function
            case 'p':
                result = permutation(a, b);
                chosen = "permutation : P(";
                is_chosen = true;
                break;

            // computation is chosen call the function
            case 'c':
                result = computation(a, b);
                chosen = "computation : C(";
                is_chosen = true;
                break;

            // when user input is wrong
            default:
                cerr << "you put wrong character to choose the operation.\n Try again~ \n";
                break;
            }
        }
        // print result
        cout << "You chose " << chosen << a << ", " << b << ") = " << result << '\n';
        return 0;
    }
    catch (runtime_error e)
    {
        cout << e.what() << '\n';
        return 1;
    }
}