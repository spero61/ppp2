// a program implements the grammar described as in exercise06_05
// terminate the program with a dot, '.'

#include "std_lib_facilities.h"

vector<string> verbs = {"rules", "fly", "swim"};
vector<string> articles = {"the", "a", "an"};
vector<string> nouns = {"birds", "fish", "C++"};
vector<string> conjunctions = {"and", "or", "but"};

bool is_article(string input)
{
    for (int i = 0; i < articles.size(); ++i)
    {
        if (articles[i] == input)
            return true;
    }
    return false;
}

bool is_verb(string input)
{
    for (string verb : verbs)
    {
        if (verb == input)
            return true;
    }
    return false;
}

bool is_noun(string input)
{
    for (string noun : nouns)
    {
        if (noun == input)
            return true;
    }
    return false;
}

bool is_conjunction(string input)
{
    for (string conjunction : conjunctions)
    {
        if (conjunction == input)
            return true;
    }
    return false;
}

bool sentence()
{
    string word1 = "";
    cin >> word1;
    if (!is_noun(word1))
        return false;

    string word2 = "";
    cin >> word2;
    if (!is_verb(word2))
        return false;

    string word3 = "";
    cin >> word3;
    if (word3 == ".")
        return true;
    if (!is_conjunction(word3))
        return false;

    return sentence();
}

int main()
{
    try
    {
        cout << "Welcome to our simple English Grammar checker.\n"
             << "notice that this is prototype, further works are needed\n"
             << "(enter '.' note that it needs space before dot)\n";

        while (cin)
        {

            bool is_sentence = sentence();

            if (is_sentence)
                cout << "OK\n";
            else
            {
                cout << "Not OK\n";
            }
        }
    }
    catch (runtime_error e)
    {
        cout << e.what() << '\n';
        return 1;
    }
}
