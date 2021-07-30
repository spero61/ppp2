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

int Currency_to_int(Currency unit) {
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
            error("error: Currency_to_int()");
            return -1;
    }
}

constexpr int num_of_units{5};

class Currency_Converter : public Window  // Lines_window inherits from Window
{
   public:
    Currency_Converter(Point xy);  // declare constructor

   private:
    // data:
    double conversion_rates[num_of_units][num_of_units];               // https://en.cppreference.com/w/c/string/multibyte/char16_t
    string units[num_of_units] = {u8"$", u8"€", u8"¥", u8"£", u8"₩"};  //  REVIEW: Does not work with character literal, char16_t for instance, but why?
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

    void calc();
    void quit();
};

Currency_Converter::Currency_Converter(Point xy)
    : Window{xy, 600, 400, "Currency Converter"},
      input_unit{Currency::USD},
      output_unit{Currency::EUR},
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
    // To do: read conversion rates from a file
    for (int i = 0; i < num_of_units; ++i) {
        for (int j = 0; j < num_of_units; ++j) {
            conversion_rates[i][j] = 2;
        }
    }

    attach(quit_button);
    attach(input_currency);
    attach(input_amount);
    attach(calc_button);  // attach the parts to the window
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
    // test
    string input_amt = input_amount.get_string();

    const int input_index = Currency_to_int(input_unit);
    const int output_index = Currency_to_int(output_unit);

    double output_amt = stod(input_amt) * conversion_rates[input_index][output_index];

    ostringstream ss;
    ss << units[output_index] << ' ' << fixed << setprecision(2) << output_amt;
    output_amount.put(ss.str());
}

void Currency_Converter::quit() {
    hide();  // curious FLTK idiom to delete window
}

int main() {
    try {
        Currency_Converter win{Point{100, 100}};
        return gui_main();
    } catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...exception occurred\n";
        return 2;
    }
}