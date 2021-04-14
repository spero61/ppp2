#include "std_lib_facilities.h"

int main()
{
    vector<double> distances;
    double sum = 0;

    // distance : a distance between two cities along a given route
    for (double distance; cin >> distance;)
    {
        distances.push_back(distance);
        sum += distance;
    }

    sort(distances);

    cout << "the sum of all distances : " << sum << '\n';
    cout << "the smallest distance : " << distances[0] << '\n';
    cout << "the greatest distance : " << distances[distances.size() - 1] << '\n';
    cout << "mean distance : " << sum / distances.size() << '\n';
}
