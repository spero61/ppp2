// store_temps.cpp

#include "std_lib_facilities.h"

struct Reading {         // a temperature reading
    int hour;            // hour after midnight [0:23]
    double temperature;  // in Fahrenheit
};

int main() {
    try {
        vector<Reading> temps;  // store the readings here

        random_device rd;                                    // https://en.cppreference.com/w/cpp/numeric/random/random_device
        mt19937_64 gen(rd());                                // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        uniform_int_distribution<int> rd_hour(0, 23);        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        normal_distribution<double> rd_temperature(75, 17);  // https://en.cppreference.com/w/cpp/numeric/random/normal_distribution

        int hour{0};
        double temperature{0.0};

        for (int i = 0; i < 50; ++i) {
            hour = rd_hour(gen);
            temperature = rd_temperature(gen);
            temps.push_back(Reading{hour, temperature});
        }

        string filename = "raw_temps.txt";
        ofstream ost{filename};
        if (!ost) error("can't open output file ", filename);

        for (Reading r : temps) {
            ost << r.hour << ' ' << r.temperature << '\n';
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