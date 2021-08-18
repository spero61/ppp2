// 3. Provide named constants that you really can’t change the value of.
// Hint: You have to add a member to Variable that distinguishes between constants and
// variables and check for it in set_value().
// If you want to let the user define constants (rather than just having pi and e defined as constants),
// you’ll have to add a notation to let the user express that, for example, const pi = 3.14;
// Bjarne, Stroustrup. Programming (p. 253). Pearson Education. Kindle Edition.

// rollback declaration keyword from '#' to "let" and add "const"

/*
This program implements a basic expression calculator.
Input from cin; output to cout.
The grammar for input is:

Calculation:
    Statement
    Print
    Quit
    Calculation Statement

 Statement:
    Declaration
    Expression
    
Declaration:
    "let" Name = Expression
    "const" Name = Expression

----------------------------------------------

Print: ;
Quit: Q

predefined names
k : 1000
pi : 3.14159265358979
e : 2.718281828459

----------------------------------------------
 
Expression:
    Term
    Expression + Term
    Expression – Term
Term:
    Primary
    Term * Primary
    Term / Primary

Primary:
      Number
      ( Expression )
       – Primary
       + Primary
       Name
       Function ( Expression )

Function:
    "sqrt"
    "pow"     

Number:
    floating-point-literal


 Input comes from cin through the Token_stream called ts.
*/

#include "std_lib_facilities.h"

const char let_char = 'L';
const char const_char = 'C';
const char quit = 'Q';            // t.kind == quit means that t is a quit Token
const char print = ';';           // t.kind == print means that t is a print Token
const char number = '8';          // t.kind == number means that t is a number Token
const char name = 'a';            // name token
const char sqrtfunc = 's';        // sqrt function token
const char powfunc = 'p';         // power function token
const string letkey = "let";      // declaration keyword for let
const string constkey = "const";  // declaration keyword for const
const string quitkey = "exit";    // quit keyword set to "exit"  drill 7-11
const string sqrtkey = "sqrt";    // sqrt keyword
const string powkey = "pow";      // pow keyword

struct Token {
    char kind;
    double value;  // for numbers: a value
    string name;
    Token() : kind{0} {}                                  // default constructor
    Token(char ch) : kind{ch} {}                          // initialize kind with ch
    Token(char ch, double val) : kind{ch}, value{val} {}  // initialize kind and value
    Token(char ch, string n) : kind{ch}, name{n} {}       // initialize kind and name
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
    cin >> ch;  // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        case print:
        case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':              // used for declaration()
        case ',':              // function argument vector separator
            return Token(ch);  // let each character represent itself

        case '.':  // a floating-point literal can start with a dot
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':  // numeric literals 0 to 9
        {
            cin.unget();  // put digit back into the input stream
            double val;
            cin >> val;
            return Token(number, val);
        }

        default:
            if (isalpha(ch) || ch == '_')  // to allow underscores in the variable names
            {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))  // to allow underscores in the variable names
                {
                    s += ch;
                }
                cin.unget();
                if (s == letkey)
                    return Token{let_char};  // declaration keyword
                else if (s == constkey)
                    return Token{const_char};  // declaration keyword
                else if (s == quitkey)
                    return Token{name};
                else if (s == sqrtkey)
                    return Token{sqrtfunc};
                else if (s == powkey)
                    return Token{powfunc};

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
    double value;
    bool is_const;
    Variable(string n, double v, bool b) : name(n), value(v), is_const(b) {}
};

// names is equivalent to var_table in the book
vector<Variable> names;

// return the value of the Variable named s
double get_value(string s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return names[i].value;

    error("get: undefined name ", s);
    return 3;
}

// set the Variable named s to d
void set_value(string s, double d) {
    for (int i = 0; i <= names.size(); ++i)
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

// is var already in names?
bool is_declared(string s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return true;
    return false;
}

//------------------------------------------------------------------------------

Token_stream ts;      // provides get() and putback()
double expression();  // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// evaluates function of t.kind == c
double eval_function(char c) {
    // for function arguments
    vector<double> func_args;

    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected after function");

    switch (c) {
        case sqrtfunc:
            func_args.push_back(expression());
            t = ts.get();
            if (t.kind != ')')
                error("')' expected after function");
            if (func_args[0] < 0)
                error("square root of a negative number is inappropriate");
            return sqrt(func_args[0]);

        case powfunc:
            func_args.push_back(expression());
            t = ts.get();
            if (t.kind != ',')
                error("Please provide proper pow function arguments e.g., pow(2, 3)");
            func_args.push_back(expression());
            t = ts.get();
            if (t.kind != ')')
                error("')' expected after function");
            // if(args[1]-narrow_cast<int>(args[1])!=0)
            // error();
            return pow(func_args[0], func_args[1]);

        default:
            error("Function you called is not implemeted yet");
            return 5;
    }
}

// deal with numbers and parentheses
double primary() {
    Token t = ts.get();
    switch (t.kind) {
        // handle '(' expression ')'
        case '(': {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return d;
        }

        case '+':  // handle unary plus
        {
            return primary();
        }

        case '-':  // handle unary minus
            return -primary();

        case number:
            return t.value;  // return the number's value

        case name:
            return get_value(t.name);

        // if function is called, let eval_function handles it
        case sqrtfunc:
        case powfunc:
            return eval_function(t.kind);

        default:
            error("primary expected");
            return 4;
    }
}

// deal with * and /
double term() {
    double left = primary();
    Token t = ts.get();  // get the next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/': {
                double d = primary();
                if (d == 0)
                    error("/ : divide by zero");
                left /= d;
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
double expression() {
    double left = term();  // read and evaluate a Term
    Token t = ts.get();    // get the next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term();  // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();  // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.unget(t);  // put t back into the Token stream
                return left;  // finally: no more + or -: return the answer
        }
    }
}

double declaration(char c) {
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string variable_name = t.name;
    if (is_declared(variable_name)) {
        switch (c) {
            case const_char:
                error(variable_name, " is declared already!\nYou cannot change value of the const");

            case let_char:
                for (int i = 0; i < names.size(); ++i) {
                    if (names[i].name == variable_name) {
                        // when the variable is declared as const already
                        if (names[i].is_const == true)
                            error(variable_name, " is declared as const already!\nYou cannot change value of the const");
                        Token t2 = ts.get();
                        if (t2.kind != '=')
                            error("= missing in declaration of ", variable_name);
                        double d = expression();
                        names[i].value = d;
                        return d;
                    }
                }
        }
    }

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of ", variable_name);
    double d = expression();
    if (c == const_char)
        names.push_back(Variable(variable_name, d, true));
    else
        names.push_back(Variable(variable_name, d, false));
    return d;
}

double statement() {
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

const string prompt = "> ";
const string result = "= ";

void calculate() {
    cout << "\n~~ Welcome to our simple calculator ~~\n\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "Operators at your disposal (+, -, *, and / )\n"
         << "and you can use parenthesis as well.\n"
         << "to set a variable by using : # variable name = n\n"
         << "(pow(n, m) and sqrt(n), predefined number pi and e \n"
         << "enter ';' for print the result and 'Q' for quit)\n\n";
    while (true)
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.unget(t);
            cout << result << statement() << endl;
        } catch (runtime_error &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

// add {var, val} to var_table
double define_name(string var, double val, bool b) {
    if (is_declared(var))
        error(var, " declared twice");
    names.push_back(Variable{var, val, b});
    return val;
}

int main() {
    try {
        // predefine names:
        define_name("k", 1000, true);
        define_name("pi", 3.14159265358979, true);
        define_name("e", 2.718281828459, true);
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