// Calculator from exercise07_09.cpp with GUI implementation

/*
This program implements a basic expression calculator.
Input from In_Box input_equation; output to Out_Box output_result.
The grammar for input is:

Calculation:
    Statement
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
    Secondary
    Term '*' Secondary
    Term '/' Secondary
    Term '%' Secondary

Secondary:
    Primary
    Primary '!'

Primary:
      Number
      '(' Expression ')'
       '–'Primary
       '+' Primary
       Name
       Name '=' Expression
       Function '(' Arguments ')'

Function:
    "sqrt"
    "pow"
    "log"

Arguments :
    Expression
    Argument ',' Expression

Number:
    floating-point-literal

Name :
    alphabet
    Name alphabet
    Name digit
    Name '_'

 Input comes from In_Box input_equation through the Token_stream called ts.
*/

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

const char let_char = 'L';
const char const_char = 'C';
const char quit = 'Q';            // t.kind == quit means that t is a quit Token
const char print = ';';           // t.kind == print means that t is a print Token
const char number = '8';          // t.kind == number means that t is a number Token
const char name = 'a';            // name token
const char sqrtfunc = 's';        // sqrt function token
const char powfunc = 'p';         // power function token
const char logfunc = 'l';         // log function token
const string letkey = "let";      // declaration keyword for let
const string constkey = "const";  // declaration keyword for const
const string quitkey = "quit";    // quit keyword
const string sqrtkey = "sqrt";    // sqrt keyword
const string powkey = "pow";      // pow keyword
const string logkey = "log";      // log keyword

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
    Token_stream(string input_string) : full{0}, buffer{0}, ist{input_string} {}  // in case of using istringstream instead of cin

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
    istringstream ist;  // in case of using istringstream instead of cin
};

Token Token_stream::get() {
    if (full)  // check if we already have a Token ready
    {
        full = false;
        return buffer;
    }
    char ch;
    ist.get(ch);

    // only '\n' would be treated specially among space characters
    while (isspace(ch) && ch != '\n') {
        ist.get(ch);
    }

    switch (ch) {
        case ';':
        case '\n':
            return Token(print);
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
            ist.unget();  // put digit back into the input stream
            double val;
            ist >> val;
            return Token(number, val);
        }

        default:
            if (isalpha(ch) || ch == '_')  // to allow underscores in the variable var_table
            {
                string s;
                s += ch;
                while (ist.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))  // to allow underscores in the variable var_table
                {
                    s += ch;
                }
                ist.unget();

                if (s == letkey)
                    return Token{let_char};  // declaration keyword
                else if (s == constkey)
                    return Token{const_char};  // declaration keyword
                else if (s == quitkey)
                    return Token{quit};
                else if (s == sqrtkey)
                    return Token{sqrtfunc};
                else if (s == powkey)
                    return Token{powfunc};
                else if (s == logkey)
                    return Token{logfunc};
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
    while (ist >> ch)
        if (ch == c)
            return;
}

struct Variable {
    string name;
    double value;
    bool is_const;
    Variable(string n, double v, bool b) : name(n), value(v), is_const(b) {}
};

class Symbol_table {
   public:
    vector<Variable> var_table;
    double get_value(string s);                          // return the value of the Variable named s
    void set_value(string s, double d);                  // set the Variable named s to d
    bool is_declared(string s);                          // is var already in var_table?
    double define_name(string var, double val, bool b);  // add {var, val} to var_table
};

double Symbol_table::get_value(string s) {
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get: undefined name ", s);
    return 3;
}

void Symbol_table::set_value(string s, double d) {
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

double Symbol_table::define_name(string var, double val, bool b) {
    if (is_declared(var))
        error(var, " declared twice");
    var_table.push_back(Variable{var, val, b});
    return val;
}

//------------------------------------------------------------------------------

Token_stream ts;                      // provides get() and unget()
Symbol_table st;                      // provides get_value(), set_value(), is_declared(), and define_name()
double expression(Token_stream& ts);  // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// evaluates function of t.kind == c
double eval_function(char c, Token_stream& ts) {
    // for function arguments
    vector<double> func_args;

    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected after function");

    switch (c) {
        case sqrtfunc:
            func_args.push_back(expression(ts));
            t = ts.get();
            if (t.kind != ')')
                error("')' expected after function");
            if (func_args[0] < 0)
                error("square root of a negative number is inappropriate");
            return sqrt(func_args[0]);

        case powfunc:
            func_args.push_back(expression(ts));
            t = ts.get();
            if (t.kind != ',')
                error("Please provide proper pow function arguments e.g., pow(2, 3)");
            func_args.push_back(expression(ts));
            t = ts.get();
            if (t.kind != ')')
                error("')' expected after function");
            // if(args[1]-narrow_cast<int>(args[1])!=0)
            // error();
            return pow(func_args[0], func_args[1]);

        case logfunc:
            func_args.push_back(expression(ts));
            t = ts.get();
            if (t.kind != ')')
                error("')' expected after function");
            return log(func_args[0]);

        default:
            error("Function you called is not implemented yet");
            return 5;
    }
}

// deal with numbers, parentheses and unary plus, minus
// also calls eval_function when needed
double primary(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
            // handle '(' expression ')'
        case '(': {
            double d = expression(ts);
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return d;
        }

        case '+':  // handle unary plus
        {
            return primary(ts);
        }

        case '-':  // handle unary minus
            return -primary(ts);

        case number:
            return t.value;  // return the number's value

        case name:
            return st.get_value(t.name);

            // if function is called, let eval_function handles it
        case sqrtfunc:
        case powfunc:
        case logfunc:
            return eval_function(t.kind, ts);

        default:
            error("primary expected");
            return 4;
    }
}

double secondary(Token_stream& ts)  // handle a factorial operator
{
    double left = primary(ts);
    Token t = ts.get();

    if (t.kind == '!') {
        int x = int(left);
        if (x == 0) {
            x = 1;
        } else if (x < 0) {
            error("you cannot provide negative integer for factorial operation\n");
        } else {
            for (int i = x - 1; i > 0; --i) {
                x *= i;
            }
        }
        return double(x);
    }
    ts.unget(t);  // put t back into the Token stream
    return left;  // if it is just a number pass it through to the next step
}

//------------------------------------------------------------------------------

// deal with *, / and %
double term(Token_stream& ts) {
    double left = secondary(ts);
    Token t = ts.get();  // get the next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= secondary(ts);
                t = ts.get();
                break;
            case '/': {
                double d = secondary(ts);
                if (d == 0)
                    error("/ : divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%': {
                double d = secondary(ts);
                if (d == 0)
                    error("% : divide by zero");
                // note that x%y can be defined as x%y == x-y*int(x/y)
                left = fmod(left, d);
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
double expression(Token_stream& ts) {
    double left = term(ts);  // read and evaluate a Term
    Token t = ts.get();      // get the next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term(ts);  // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(ts);  // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.unget(t);  // put t back into the Token stream
                return left;  // finally: no more + or -: return the answer
        }
    }
}

double declaration(char c, Token_stream& ts) {
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
                        double d = expression(ts);
                        st.var_table[i].value = d;
                        return d;
                    }
                }
        }
    }

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of ", variable_name);
    double d = expression(ts);
    if (c == const_char)
        st.var_table.push_back(Variable(variable_name, d, true));
    else
        st.var_table.push_back(Variable(variable_name, d, false));
    return d;
}

double statement(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
        case let_char:
        case const_char:
            return declaration(t.kind, ts);

        default:
            ts.unget(t);
            return expression(ts);
    }
}

void clean_up_mess() {
    ts.ignore(print);
}

string calculate(string input_string) {
    Token_stream ts{input_string};
    ostringstream ost;
    try {
        ost << statement(ts);
        return ost.str();
    } catch (runtime_error& e) {
        cerr << e.what() << '\n';
        clean_up_mess();
    }
}

class Calculator_window : public Window  // Lines_window inherits from Window
{
   public:
    Calculator_window(Point xy, int w, int h, const string& title);  // declare constructor

   private:
    // data:
    Vector_ref<Shape> how_to_use;
    bool is_how_to_use_shown;

    // widgets:
    Button help_button;  // toggle 'how to use'
    Button calc_button;
    Button quit_button;  // end program

    In_box input_equation;
    Out_box output_result;

    // actions invoked by callbacks:
    void help();
    void calc();             // calculate and show the result on Out_box output_result
    void quit() { hide(); }  // https://www.fltk.org/doc-1.3/classFl__Window.html#acd69a335bdc69f5624301f267ca7f94e
};

Calculator_window::Calculator_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title}, is_how_to_use_shown{false},
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      help_button{Point{x_max() - 150, 0}, 70, 20, "Help", [](Address, Address pw) { reference_to<Calculator_window>(pw).help(); }},
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Calculator_window>(pw).quit(); }},  // quit button

      input_equation{Point{x_max() / 2 - 110, static_cast<int>(y_max() / 2 - 0.3 * y_max() - 10)}, 220, 20, "input: "},

      calc_button{Point{x_max() / 2 - 60, y_max() / 2 - 40}, 120, 50, "Calculate", [](Address, Address pw) { reference_to<Calculator_window>(pw).calc(); }},

      output_result{Point{x_max() / 2 - 110, static_cast<int>(y_max() / 2 + 0.2 * y_max())}, 220, 20, "result: "}

{
    how_to_use.push_back(new Graph_lib::Rectangle{Point{0, 20}, x_max(), y_max() - 20});  // this light gray rectangle would overlap the other widgets as if they are disappeared
    how_to_use[0].set_fill_color(Color{49});                                              // https://www.fltk.org/doc-1.3/fltk-colormap.png

    // Basically, a Text object defines a line of text starting at a Point. The Point will be the bottom left corner of the text.
    // The reason for restricting the string to be a single line is to ensure portability across systems.
    // Don't try to put in a newline character('\n'); it may or may not be represented as a newline in your window.
    // source: Bjarne, Stroustrup. Programming (p. 467). Pearson Education. Kindle Edition.
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 0}, "~~ Simple Calculator with GUI ~~"});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 1}, "Please enter expressions using floating-point numbers."});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 2}, "Operators at your disposal (+, -, *, and / )"});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 3}, "and you can use parenthesis as well."});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 4}, "to set a variable by using : let variable name = n"});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 5}, "you can also define const similarly : const variable name = n"});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 6}, "there are functions (pow(n, m), sqrt(n), and log(n) of base e"});
    how_to_use.push_back(new Text{Point{110, 50 + 30 * 7}, "predefined number k for 1000, pi, and e "});
    how_to_use.push_back(new Text{Point{110, 60 + 30 * 8}, "Click 'Calculate' button to print the result."});
    how_to_use.push_back(new Text{Point{110, 60 + 30 * 9}, "Click 'Help' button again to hide this instruction."});
    for (int i = 0; i < how_to_use.size(); ++i) {
        if (i == 0) continue;  // skip the light rectangle (background box)
        how_to_use[i].set_color(Color::black);
        // note that Vector_ref class does not have set_font() nor set_font_size()
    }

    // attach the parts to the window
    attach(help_button);
    attach(quit_button);

    attach(input_equation);
    attach(calc_button);
    attach(output_result);

    // set defaults
    output_result.put(0);
    redraw();
}

void Calculator_window::help() {
    if (!is_how_to_use_shown) {
        for (int i = 0; i < how_to_use.size(); ++i) {
            attach(how_to_use[i]);
        }
        is_how_to_use_shown = true;
    } else {
        for (int i = 0; i < how_to_use.size(); ++i) {
            detach(how_to_use[i]);
        }
        is_how_to_use_shown = false;
    }
    redraw();
}

void Calculator_window::calc() {
    string input_string = input_equation.get_string();
    string result = calculate(input_string);
    output_result.put(result);
}

int main() {
    try {
        // predefine var_table:
        st.define_name("k", 1000, true);
        st.define_name("pi", 3.14159265358979, true);
        st.define_name("e", 2.718281828459, true);

        Calculator_window win{Point{100, 100}, 600, 400, "Calculator with GUI"};
        return gui_main();

    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}