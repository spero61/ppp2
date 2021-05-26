// temp_stats.cpp

#include "std_lib_facilities.h"

struct Reading {         // a temperature reading
    int hour;            // hour after midnight [0:23]
    double temperature;  // in Fahrenheit
};

void fill_from_file(vector<Reading>& temps, const string& filename) {
    ifstream ist{filename};
    if (!ist) error("can't open input file ", filename);

    int hour{0};
    double temperature{0.0};
    while (ist >> hour >> temperature) {
        if (hour < 0 || 23 < hour)
            error("hour out of range");
        temps.push_back(Reading{hour, temperature});
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

        fill_from_file(temps, "raw_temps.txt");

        for (Reading r : temps) {
            cout << r.hour << ' ' << r.temperature << '\n';
        }

        // printing stats
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