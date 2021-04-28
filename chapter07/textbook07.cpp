/*
code from the textbook of chapter 07

 Simple calculator

        Revision history:
                    Revised by Yoru Sung April 2021
                    Revised by Bjarne Stroustrup November 2013
                    Revised by Bjarne Stroustrup May 2007
                    Revised by Bjarne Stroustrup August 2006
                    Revised by Bjarne Stroustrup August 2004
                    Originally written by Bjarne Stroustrup
                               (bs@cs.tamu.edu) Spring 2004.

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
    "let" Name "=" Expression

----------------------------------------------

Print: ;
Quit: q
factorial : !

----------------------------------------------
 
Expression:
    Term
    Expression + Term
    Expression – Term
Term:
    Secondary
    Term * Secondary
    Term / Secondary
    Term % Secondary
                    
Secondary :
    Primary
    Primary !
    Primary k

Primary:
      Number
      ( Expression )
       – Primary
       + Primary
Number:
    floating-point-literal

 Input comes from cin through the Token_stream called ts.
*/

#include "std_lib_facilities.h"

const char number = '8'; // t.kind == number means that t is a number Token
const char quit = 'q';   // t.kind == quit means that t is a quit Token
const char print = ';';  // t.kind == print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

class Variable
{
public:
    string name;
    double value;
};

vector<Variable> var_table;

// return the value of the Variable named s
double get_value(string s)
{
    for (const Variable &v : var_table)
    {
        if (v.name == s)
            return v.value;
        error("get: undefined variable ", s);
    }
}

// set the Variable named s to d
void set_value(string s, double d)
{
    for (Variable &v : var_table)
    {
        if (v.name == s)
        {
            v.value = d;
            return;
        }
        error("set: undefined variable ", s);
    }
}

//------------------------------------------------------------------------------

class Token
{
public:
    char kind;
    double value; // for numbers: a value
    string name;
    Token() : kind{0} {}                                 // default constructor
    Token(char ch) : kind{ch} {}                         // initialize kind with ch
    Token(char ch, double val) : kind{ch}, value{val} {} // initialize kind and value
    Token(char ch, string n) : kind{ch}, name{n} {}      // initialize kind and name
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
    Token get();           // get a Token
    void putback(Token t); // put a Token back
    void ignore(char c);   // discard characters up to and including a c
private:
    bool full{false}; // is there a Token in the buffer?
    Token buffer{0};  // putback() saves its token here
};

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;  // copy t to buffer
    full = true; // buffer is now full
}

const char name = 'a';        // name token
const char let = 'L';         // declaration token
const string declkey = "let"; // declaration keyword

Token Token_stream::get()
{
    if (full) // check if we already have a Token ready
    {
        full = false;
        return buffer;
    }
    char ch;
    cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch)
    {
    case print:
    case quit:
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
    case '%':
    case '=':             // used for declaration()
        return Token(ch); // let each character represent itself

    case '.': // a floating-point-literal can start with a dot
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': // numeric literals 0 to 9
    {
        cin.putback(ch); // put digit back into the input stream
        double val;
        cin >> val; // read a floating-point number
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
            {
                s += ch;
            }
            cin.putback(ch);
            if (s == declkey)
                return Token{let}; // declaration keyword

            return Token{name, s};
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c) // c represents the kind of Token
{
    // first look in buffer:
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;
    // now search input:
    char ch = 0;
    while (cin >> ch)
    {
        if (ch == c)
            return;
    }
}

//------------------------------------------------------------------------------

Token_stream ts;     // provides get() and putback()
double expression(); // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

double primary() // deal with numbers and parentheses
{
    Token t = ts.get();

    switch (t.kind)
    {
    case '{': // handle '{' expression '}'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}')
            error("'}' expected");
        return d;
    }
    case '(': // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '+': // handle unary plus
    {
        return primary();
    }
    case '-': // handle unary minus
    {
        return -primary();
    }
    case number:
        return t.value; // return the number's value

    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

double secondary() // handle a factorial operator
{
    double left = primary();
    Token t = ts.get();

    if (t.kind == '!')
    {
        int x = int(left);
        if (x == 0)
        {
            x = 1;
        }
        else if (x < 0)
        {
            error("you cannot provide negative integer for factorial operation\n");
        }
        else
        {
            for (int i = x - 1; i > 0; --i)
            {
                x *= i;
            }
        }
        return double(x);
    }
    ts.putback(t); // put t back into the Token stream
    return left;   // if it is just a number pass it through to the next step
}

//------------------------------------------------------------------------------

double term() // deal with * and /
{
    double left = secondary();
    Token t = ts.get(); // get the next Token from the Token stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= secondary();
            t = ts.get();
            break;
        case '/':
        {
            double d = secondary();
            if (d == 0)
                error("/ : divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = secondary();
            if (d == 0)
                error("% : divide by zero");
            // note that x%y can be defined as x%y == x-y*int(x/y)
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t); // put t back into the Token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double expression() // deal with + and -
{
    double left = term(); // read and evaluate a Term
    Token t = ts.get();   // get the next Token from the Token stream
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(); // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t); // put t back into the Token stream
            return left;   // finally: no more + or -: return the answer
        }
    }
}

// is var already in var_table?
bool is_declared(string var)
{
    for (const Variable &v : var_table)
    {
        if (v.name == var)
        {
            return true;
        }
        return false;
    }
}

// add {var, val} to var_table
double define_name(string var, double val)
{
    if (is_declared(var))
        error(var, " declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

// assume we have seen "let"
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

// expression evaluation loop
void calculate()
{
    cout << "Welcome to our simple calculator.\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "Operators at your disposal (+, -, *, and / )\n"
         << "and you can use parenthesis as well.\n"
         << "(enter ';' for print the result and 'q' for quit)\n\n";
    while (cin)
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
            {
                t = ts.get(); // first, discard all "prints"
            }
            if (t.kind == quit)
                return;
            ts.putback(t);
            cout << result << statement() << '\n';
        }
        catch (exception &e)
        {
            cerr << e.what() << '\n'; // write error message
            clean_up_mess();
        }
    }
}
//-----------------------------------------------------------------------

int main()
{
    try
    {
        // predifine names:
        define_name("pi", 3.14159265358979);
        define_name("e", 2.718281828459);

        calculate();
        keep_window_open(); // cope with Windows console mode
        return 0;
    }
    catch (exception &e)
    {
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch (...)
    {
        cerr << "exception \n";
        keep_window_open("~~");
        return 2;
    }
}
