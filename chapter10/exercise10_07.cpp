// Make a version of the calculator from Chapter 7
// that accepts Roman numerals rather than the usual Arabic ones,
// for example, XXI + CIV == CXXV.

// Comment:
// I definitely REVIEW this problem later.

/*
This program implements a basic expression calculator.
Input from cin; output to cout.
The grammar for input is:

Calculation:
    Statement
    Help
    Print
    Quit
    Calculation Statement

 Statement:
    Declaration
    Expression
    
(note that Declaration also handles reassignment of the variable, for now)
Declaration:
    "let" Name '=' Expression
    "const" Name '=' Expression

Help:
    "help"
Print:
    ';'
    '\n'
Quit:
    "quit"
 
Expression:
    Term
    Expression '+' Term
    Expression '–' Term
Term:
    Primary
    Term '*' Primary
    Term '/' Primary
    Term '%' Primary

Primary:
      Number
      '(' Expression ')'
       '–'Primary
       '+' Primary
       Name
       Name '=' Expression

Number:
    Roman-numeral-literal

Name :
    alphabet
    Name alphabet
    Name digit
    Name '_'


 Input comes from cin through the Token_stream called ts.
*/

#include "exercise10_07_roman.cpp"
#include "std_lib_facilities.h"

const char let_char{'L'};
const char const_char{'C'};
const char help{'H'};            // t.kind == help means that t is a help Token
const char quit{'Q'};            // t.kind == quit means that t is a quit Token
const char print{';'};           // t.kind == print means that t is a print Token
const char number{'8'};          // t.kind == number means that t is a number Token
const char name{'a'};            // name token
const string letkey{"let"};      // declaration keyword for let
const string constkey{"const"};  // declaration keyword for const
const string quitkey{"quit"};    // quit keyword
const string helpkey{"help"};    // help keyword

struct Token {
    char kind;
    Roman_int value;  // for numbers: a value
    string name;
    Token() : kind{0} {}                                     // default constructor
    Token(char ch) : kind{ch} {}                             // initialize kind with ch
    Token(char ch, Roman_int val) : kind{ch}, value{val} {}  // initialize kind and value
    Token(char ch, string n) : kind{ch}, name{n} {}          // initialize kind and name
};

class Token_stream {
   public:
    Token_stream() : full{0}, buffer{0} {}

    Token get();         // get a Token
    void unget(Token t)  // put a Token back
    {
        buffer = t;   // copy t to buffer
        full = true;  // buffer is now full
    }
    void ignore(char c);  // discard characters up to and including a c

   private:
    bool full;
    Token buffer;
};

Token Token_stream::get() {
    if (full)  // check if we already have a Token ready
    {
        full = false;
        return buffer;
    }
    char ch;

    // cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)
    cin.get(ch);  // so we use cin.get(ch); instead for this exercise.

    // only '\n' would be treated specially among space characters
    while (isspace(ch) && ch != '\n') {
        cin.get(ch);
    }

    switch (ch) {
        case ';':
        case '\n':
            return Token(print);

        // case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '!':
        case '%':
        case '=':              // used for declaration()
        case ',':              // function argument vector separator
            return Token(ch);  // let each character represent itself

            // case '.':  // a floating-point literal can start with a dot
            // case '0': case '1': case '2': case '3': case '4': case '5':
            // case '6': case '7': case '8': case '9':  // numeric literals 0 to 9
            // {
            //     cin.unget();  // put digit back into the input stream
            //     Roman_int val;
            //     cin >> val;
            //     return Token(number, val);
            // }

        // Roman-numeral literals
        case 'M':
        case 'C':
        case 'X':
        case 'I':
        case 'D':
        case 'L':
        case 'V': {
            cin.unget();
            Roman_int r;
            cin >> r;
            return Token(number, r);
        }

        default:
            if (isalpha(ch) || ch == '_')  // to allow underscores in the variable var_table
            {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))  // to allow underscores in the variable var_table
                {
                    s += ch;
                }
                cin.unget();

                if (s == letkey)
                    return Token{let_char};  // declaration keyword
                else if (s == constkey)
                    return Token{const_char};  // declaration keyword
                else if (s == quitkey)
                    return Token{quit};
                else if (s == helpkey)
                    return Token{help};
                else
                    return Token{name, s};
            }

            error("Bad token");
    }
    // to deal with : control reaches end of non-void function [-Wreturn-type]
    return Token{};
}

void Token_stream::ignore(char c)  // c represents the kind of Token
{
    // first look in buffer:
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch;
    while (cin >> ch)
        if (ch == c)
            return;
}

struct Variable {
    string name;
    Roman_int value;
    bool is_const;
    Variable(string n, Roman_int v, bool b) : name(n), value(v), is_const(b) {}
};

class Symbol_table {
   public:
    vector<Variable> var_table;
    Roman_int get_value(string s);                             // return the value of the Variable named s
    void set_value(string s, Roman_int d);                     // set the Variable named s to d
    bool is_declared(string s);                                // is var already in var_table?
    Roman_int define_name(string var, Roman_int val, bool b);  // add {var, val} to var_table
};

Roman_int Symbol_table::get_value(string s) {
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get: undefined name ", s);
    return 3;
}

void Symbol_table::set_value(string s, Roman_int d) {
    for (int i = 0; i <= var_table.size(); ++i)
        if (var_table[i].name == s) {
            var_table[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s) {
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return true;
    return false;
}

Roman_int Symbol_table::define_name(string var, Roman_int val, bool b) {
    if (is_declared(var))
        error(var, " declared twice");
    var_table.push_back(Variable{var, val, b});
    return val;
}

//------------------------------------------------------------------------------

Token_stream ts;         // provides get() and unget()
Symbol_table st;         // provides get_value(), set_value(), is_declared(), and define_name()
Roman_int expression();  // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers, parentheses and unary plus, minus
Roman_int primary() {
    Token t = ts.get();
    switch (t.kind) {
        // handle '(' expression ')'
        case '(': {
            Roman_int d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("'(' expected");
            return d;
        }

        case '+':  // handle unary plus
        {
            return primary();
        }

            // Roman-numerals does not have value less than 1
            // case '-':  // handle unary minus
            //     return -primary();

        case number:
            return t.value;  // return the number's value

        case name:
            return st.get_value(t.name);

        default:
            error("primary expected");
            return 4;
    }
}
//------------------------------------------------------------------------------

// deal with *, / and %
Roman_int term() {
    Roman_int left = primary();
    Token t = ts.get();  // get the next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/': {
                Roman_int d = primary();
                // if (d == 0) // Roman numerals does not have zero
                //     error("/ : divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%': {
                Roman_int d = term();
                left %= d;
                t = ts.get();
                break;
            }
            default:
                ts.unget(t);  // put t back into the Token stream
                return left;
        }
    }
}

// deal with + and -
Roman_int expression() {
    Roman_int left = term();  // read and evaluate a Term
    while (true) {
        Token t = ts.get();  // get the next Token from the Token stream
        switch (t.kind) {
            case '+':
                left += term();  // evaluate Term and add
                break;
            case '-':
                left -= term();  // evaluate Term and subtract
                break;
            default:
                ts.unget(t);  // put t back into the Token stream
                return left;  // finally: no more + or -: return the answer
        }
    }
}

Roman_int declaration(char c) {
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string variable_name = t.name;
    if (st.is_declared(variable_name)) {
        switch (c) {
            case const_char:
                error(variable_name, " is declared already!\nYou cannot change value of the const");

            case let_char:
                for (int i = 0; i < st.var_table.size(); ++i) {
                    if (st.var_table[i].name == variable_name) {
                        // when the variable is declared as const already
                        if (st.var_table[i].is_const == true)
                            error(variable_name, " is declared as const already!\nYou cannot change value of the const");
                        Token t2 = ts.get();
                        if (t2.kind != '=')
                            error("= missing in declaration of ", variable_name);
                        Roman_int d = expression();
                        st.var_table[i].value = d;
                        return d;
                    }
                }
        }
    }

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of ", variable_name);
    Roman_int d = expression();
    if (c == const_char)
        st.var_table.push_back(Variable(variable_name, d, true));
    else
        st.var_table.push_back(Variable(variable_name, d, false));
    return d;
}

Roman_int statement() {
    Token t = ts.get();
    switch (t.kind) {
        case let_char:
        case const_char:
            return declaration(t.kind);

        default:
            ts.unget(t);
            return expression();
    }
}

void clean_up_mess() {
    ts.ignore(print);
}

void print_help_messages() {
    cout << "Please enter expressions using floating-point numbers.\n"
         << "Operators at your disposal (+, -, *, and / )\n"
         << "and you can use parenthesis as well.\n"
         << "to set a variable by using : let variable name = n\n"
         << "you can also define const similarly : const variable name = n\n"
         << "predifined number k for 'M'\n"
         << "enter ';' or just enter for print the result.\n"
         << "terminate the program by enter quit \n\n";
}

const string prompt = "> ";
const string result = "= ";

void calculate() {
    cout << "\n~~ Welcome to our simple calculator ~~\n"
         << "Enter help followed by enter to see help messages\n";
    while (true)
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();

            if (t.kind == help) {
                print_help_messages();
                continue;
            } else if (t.kind == quit)
                return;
            ts.unget(t);
            cout << result << statement() << endl;
        } catch (runtime_error &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

int main() {
    try {
        calculate();
        return 0;
    } catch (exception &e) {
        cerr << "exception: " << e.what() << endl;
        char c;
        while (cin >> c && c != ';')
            ;
        return 1;
    } catch (...) {
        cerr << "exception\n";
        char c;
        while (cin >> c && c != ';')
            ;
        return 2;
    }
}