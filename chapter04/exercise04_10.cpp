// Rock, Paper, Scissors
#include "std_lib_facilities.h"

int main()
{

    vector<char> machine_moves = {'r', 'p', 's'};
    char user_input = ' ';
    char machine_next_move = 'r';
    int init = -1;

    // ASCII value of 'r', 'p', and 's' respectively
    constexpr int rock = 114;
    constexpr int paper = 112;
    constexpr int scissors = 115;

    cout << "~~~~~ Rock, Paper, Scissors ~~~~~\n\n"
         << "make your next move (e.g. r, p, s)\n";
    cin >> user_input;

    while (init <= 0)
    {
        cout << "Enter any number that is larger than 0\n";
        cin >> init;
    }

    // variations to make it less easy for the user to guess
    init += 2021;
    init -= 4;
    init *= 13;

    // handle the exception if the number excees range of 'int'
    // in this case, machine always plays 's'
    if (init < 0)
    {
        init += 2147483647;
    }

    machine_next_move = machine_moves[init % 3];

    cout << "machine palyed " << machine_next_move << " \n";
    cout << "user : " << user_input << " versus "
         << "machine : " << machine_next_move << " \n";

    switch (user_input)
    {
    case 'r':
        if ((int)machine_next_move > rock)
        {
            cout << "player win\n";
        }
        else if ((int)machine_next_move < rock)
        {
            cout << "machine win\n";
        }
        else
        {
            cout << "draw\n";
        }
        break;

    case 'p':
        if ((int)machine_next_move - paper == 2)
        {
            cout << "player win\n";
        }
        else if ((int)machine_next_move - paper == 3)
        {
            cout << "machine win\n";
        }
        else
        {
            cout << "draw\n";
        }
        break;

    case 's':
        if (scissors - (int)machine_next_move == 3)
        {
            cout << "player win\n";
        }
        else if (scissors - (int)machine_next_move == 1)
        {
            cout << "machine win\n";
        }
        else
        {
            cout << "draw\n";
        }
        break;

    default:
        cout << "provide valid input e.g. r, p, or s \n";
        break;
    }
}