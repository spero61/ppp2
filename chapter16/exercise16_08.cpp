// Currency converter

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

// Prefer the simpler and safer enum classes(C++11) to "plain" enums. (see p.320-321)
enum class Currency {
    USD,
    EUR,
    JPY,
    GBP,
    KRW
};

int currency_to_int(Currency unit) {
    switch (unit) {
        case Currency::USD:
            return 0;
        case Currency::EUR:
            return 1;
        case Currency::JPY:
            return 2;
        case Currency::GBP:
            return 3;
        case Currency::KRW:
            return 4;
        default:
            error("error: currency_to_int()");
            return -1;
    }
}

constexpr int num_of_units{5};

class Currency_Converter : public Window  // Lines_window inherits from Window
{
   public:
    Currency_Converter(Point xy, const string& input_filename);  // declare constructor

   private:
    // data:
    string iname;                                                // input filename (text file)
    double conversion_rates[num_of_units][num_of_units];         // https://en.cppreference.com/w/c/string/multibyte/char16_t
    vector<string> units = {u8"$", u8"€", u8"¥", u8"£", u8"₩"};  //  REVIEW: Does not work with character literal, char16_t for instance, but why?
    Currency input_unit;
    Currency output_unit;

    // widgets:
    Button calc_button;  // add (next_x, next_y) to lines
    Button quit_button;  // end program

    Out_box input_currency;
    In_box input_amount;
    Out_box output_currency;
    Out_box output_amount;

    Menu input_menu;
    Button input_menu_button;
    Menu output_menu;
    Button output_menu_button;

    // actions invoked by callbacks:
    void set_input_items(Currency unit);   // when an item of input_menu is clicked
    void set_output_items(Currency unit);  // when an item of output_menu is clicked

    void input_menu_pressed() {
        input_menu_button.hide();
        input_menu.show();
    }
    void output_menu_pressed() {
        output_menu_button.hide();
        output_menu.show();
    }

    void calc();             // calculate using a conversion rate and show the result on output_amount (Out_box)
    void quit() { hide(); }  // https://www.fltk.org/doc-1.3/classFl__Window.html#acd69a335bdc69f5624301f267ca7f94e
};

Currency_Converter::Currency_Converter(Point xy, const string& input_filename)
    : Window{xy, 600, 400, "Currency Converter"},
      iname{input_filename},
      input_unit{Currency::USD},
      output_unit{Currency::EUR},  // set defaults
      // construct/initialize the parts of the window:
      // location, size, name, action (using lambda expressions)
      quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) { reference_to<Currency_Converter>(pw).quit(); }},  // quit button

      input_currency{Point{x_max() / 2 - 260, 150}, 40, 20, ""},
      input_amount{Point{x_max() / 2 - 220, 150}, 110, 20, ""},
      calc_button{Point{x_max() / 2 - 60, 200}, 120, 60, "Calculate", [](Address, Address pw) { reference_to<Currency_Converter>(pw).calc(); }},
      output_currency{Point{x_max() / 2 + 120, 150}, 40, 20, ""},
      output_amount{Point{x_max() / 2 + 160, 150}, 110, 20, ""},
      input_menu{Point{x_max() / 2 - 265, 200}, 140, 30, Menu::vertical, "Input menu"},
      input_menu_button{Point{x_max() / 2 - 265, 200}, 140, 30, "Select Currency", [](Address, Address pw) { reference_to<Currency_Converter>(pw).input_menu_pressed(); }},

      output_menu{Point{x_max() / 2 + 115, 200}, 140, 30, Menu::vertical, "Output menu"},
      output_menu_button{Point{x_max() / 2 + 115, 200}, 140, 30, "Select Currency", [](Address, Address pw) { reference_to<Currency_Converter>(pw).output_menu_pressed(); }}

{
    // currency conversion rates' source: https://www.xe.com/  Jul 30, 2021, 16:50-16:56 UTC
    // read conversion rates from a file then save to double conversion_rates[][]
    ifstream ist{iname};
    if (!ist) error("can't open input file: ", iname);
    ist.exceptions(ist.exceptions() | ios_base::badbit);  // throw for bad()

    // vector<string> tmps to keep space separated values temporarily
    vector<string> tmps;
    for (string str; ist >> str;) {
        tmps.push_back(str);
    }

    // initialize 2d-array named conversion_rates
    int index{0};
    for (int i = 0; i < num_of_units; ++i) {
        for (int j = 0; j < num_of_units; ++j) {
            conversion_rates[i][j] = stod(tmps[index++]);  // https://www.cplusplus.com/reference/string/stod/
        }
    }
    if (ist.eof()) ist.clear();
    if (ist.fail()) error("get_words() failed: ", iname);

    // attach the parts to the window
    attach(quit_button);
    attach(input_currency);
    attach(input_amount);
    attach(calc_button);
    attach(output_currency);
    attach(output_amount);
    // order by trading volumes (descending order)
    input_menu.attach(new Button{Point{0, 0}, 0, 0, "USD - US Dollar", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_input_items(Currency::USD); }});
    input_menu.attach(new Button{Point{0, 0}, 0, 0, "EUR - Euro", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_input_items(Currency::EUR); }});
    input_menu.attach(new Button{Point{0, 0}, 0, 0, "JPY - Japanese Yen", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_input_items(Currency::JPY); }});
    input_menu.attach(new Button{Point{0, 0}, 0, 0, "GBP - British Pound", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_input_items(Currency::GBP); }});
    input_menu.attach(new Button{Point{0, 0}, 0, 0, "KRW - S.Korean Won", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_input_items(Currency::KRW); }});
    attach(input_menu);
    attach(input_menu_button);
    // order by trading volumes (descending order)
    output_menu.attach(new Button{Point{0, 0}, 0, 0, "USD - US Dollar", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_output_items(Currency::USD); }});
    output_menu.attach(new Button{Point{0, 0}, 0, 0, "EUR - Euro", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_output_items(Currency::EUR); }});
    output_menu.attach(new Button{Point{0, 0}, 0, 0, "JPY - Japanese Yen", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_output_items(Currency::JPY); }});
    output_menu.attach(new Button{Point{0, 0}, 0, 0, "GBP - British Pound", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_output_items(Currency::GBP); }});
    output_menu.attach(new Button{Point{0, 0}, 0, 0, "KRW - S.Korean Won", [](Address, Address pw) { reference_to<Currency_Converter>(pw).set_output_items(Currency::KRW); }});
    attach(output_menu);
    attach(output_menu_button);

    // set defaults
    input_menu.hide();
    output_menu.hide();
    input_currency.put(u8"USD  $");
    output_currency.put(u8"EUR  €");
}

void Currency_Converter::set_input_items(Currency unit) {
    input_menu.hide();
    input_menu_button.show();
    input_unit = unit;
    calc();

    switch (unit) {
        case Currency::USD:
            input_currency.put("USD");
            break;
        case Currency::EUR:
            input_currency.put("EUR");
            break;
        case Currency::JPY:
            input_currency.put("JPY");
            break;
        case Currency::GBP:
            input_currency.put("GBP");
            break;
        case Currency::KRW:
            input_currency.put("KRW");
            break;
        default:
            error("error: something wrong with input_unit");
            break;
    }
}

void Currency_Converter::set_output_items(Currency unit) {
    output_menu.hide();
    output_menu_button.show();
    output_unit = unit;
    calc();

    switch (unit) {
        case Currency::USD:
            output_currency.put("USD");
            break;
        case Currency::EUR:
            output_currency.put("EUR");
            break;
        case Currency::JPY:
            output_currency.put("JPY");
            break;
        case Currency::GBP:
            output_currency.put("GBP");
            break;
        case Currency::KRW:
            output_currency.put("KRW");
            break;
        default:
            error("error: something wrong with output_unit");
            break;
    }
}

void Currency_Converter::calc() {
    string input_amt = input_amount.get_string();

    // safer conversion helper function enum class to int (compared to direct conversion from enum to int)
    const int input_index = currency_to_int(input_unit);
    const int output_index = currency_to_int(output_unit);

    double output_amt = stod(input_amt) * conversion_rates[input_index][output_index];

    ostringstream ss;
    ss << units[output_index] << ' ' << fixed << setprecision(2) << output_amt;
    output_amount.put(ss.str());
}

int main() {
    try {
        Currency_Converter win{Point{100, 100}, "exercise16_08_input.txt"};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}