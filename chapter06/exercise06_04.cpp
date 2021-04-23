// Rework exercise 19 in Chapter 4
// to use a vector<Name_value> instead of two vectors

#include "std_lib_facilities.h"

class Name_value
{
public:
    string name;
    int score;
};

vector<Name_value> nvs;

int main()
{
    string name = " ";
    int score = -1;
    bool is_unique = true;
    
    cout << "Please enter name, score pairs (e.g. Kris 99)\n"
         << "you can terminate input with NoName 0\n";
    while (name != "NoName" || score != 0){
    cin >> name >> score;
        
        for (int i = 0; i < nvs.size(); ++i)
             {
                 if (nvs[i].name == name)
                     is_unique = false;
             }
        if (is_unique && (name != "NoName" && score != 0))
               {    Name_value tmp;
    tmp.name = name;
    tmp.score = score;
    nvs.push_back(tmp);
               }
        // terminate with an error message if a name is entered twice
        else if (name != "NoName" || score != 0)
               {
                   cout << "Error : name already exist! \n";
               }
        is_unique = true;
    }
    

    
    // write out all the (name, score) pairs, one per line.
    for (int i = 0; i < nvs.size(); ++i)
    {
        cout << "(name : score) is (" << nvs[i].name << " : " << nvs[i].score << ")\n";
    }
}
