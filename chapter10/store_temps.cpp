// store_temps.cpp

#include "std_lib_facilities.h"

struct Reading {         // a temperature reading
    int hour;            // hour after midnight [0:23]
    double temperature;  // in Fahrenheit
    char suffix;         // temperature suffix: 'c' for Celsius and 'f' for Fahrenheit temperature
};

int main() {
    try {
        vector<Reading> temps;  // store the readings here

        random_device rd;                                    // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                                // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        uniform_int_distribution<int> rd_hour(0, 23);        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        normal_distribution<double> rd_temperature(75, 17);  // https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
        uniform_int_distribution<int> rd_suffix_num(0, 1);

        int hour{0};
        double temperature{0.0};
        char suffix{' '};
        constexpr int number_of_elements{50};

        for (int i = 0; i < number_of_elements; ++i) {
            hour = rd_hour(gen);
            temperature = rd_temperature(gen);

            // using pseudo-random binary number
            if (rd_suffix_num(gen)) {
                suffix = 'c';
            } else {
                suffix = 'f';
            }
            temps.push_back(Reading{hour, temperature, suffix});
        }

        string filename = "raw_temps_uusi.txt";
        ofstream ost{filename};
        if (!ost) error("can't open output file ", filename);

        for (Reading r : temps) {
            ost << r.hour << ' ' << r.temperature << ' ' << r.suffix << '\n';
        }
        ost.close();

        cout << "file created: " << filename << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}