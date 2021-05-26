// temp_stats.cpp

#include "std_lib_facilities.h"

struct Reading {         // a temperature reading
    int hour;            // hour after midnight [0:23]
    double temperature;  // in Fahrenheit
    char suffix;         // temperature suffix: 'c' for Celsius and 'f' for Fahrenheit temperature
};

double celsius_to_fahrenheit(double celsius) {
    return (celsius * 1.8) + 32;
}

void fill_from_file(vector<Reading>& temps, const string& filename) {
    ifstream ist{filename};
    if (!ist) error("can't open input file ", filename);

    int hour{0};
    double temperature{0.0};
    char suffix{' '};
    while (ist >> hour >> temperature >> suffix) {
        if (hour < 0 || 23 < hour)
            error("hour out of range");

        // if the temperature is in Celsius, convert into Fahrenheit then change the suffix from 'c' to 'f'.
        if (suffix == 'c') {
            temperature = celsius_to_fahrenheit(temperature);
            suffix = 'f';
        }
        temps.push_back(Reading{hour, temperature, suffix});
    }
}

// calculates the mean
double calculate_mean(const vector<Reading>& v) {
    double sum{0.0};
    for (Reading r : v) {
        sum += r.temperature;
    }
    return sum / v.size();
}

// calculates the median
double calculate_median(const vector<Reading>& v) {
    double median{0.0};
    vector<double> temperatures;
    for (Reading r : v) {
        temperatures.push_back(r.temperature);
    }

    // sort vector<double> temperatures in ascending order
    sort(temperatures.begin(), temperatures.end());

    int index = temperatures.size();
    // the number of elements is odd number
    if (temperatures.size() % 2 != 0) {
        return temperatures[index / 2];
    }
    // the number of elements is even number
    return (temperatures[index / 2] + temperatures[(index / 2) - 1]) / 2;
}

int main() {
    try {
        vector<Reading> temps;  // store the readings here
        int hour;
        double temperature;

        fill_from_file(temps, "raw_temps_uusi.txt");

        for (Reading r : temps) {
            cout << r.hour << ' ' << r.temperature << ' ' << r.suffix << '\n';
        }

        // printing stats (in Fahrenheit)
        cout << "mean: " << calculate_mean(temps) << '\n';
        cout << "median: " << calculate_median(temps) << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}