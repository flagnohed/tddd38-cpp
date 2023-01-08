#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;

int main()
{
    double const length {10.0};
    vector<double> road {};

    copy(istream_iterator<double>{cin}, istream_iterator<double>{}, 
        back_inserter(road));
    vector<double> result(road);

    rotate(road.begin(), road.begin() + 1, road.end());

    
    for (unsigned i{0}; i < road.size(); ++i)
    {
        double a {road[i]};
        double b {result[i]};
        result[i] = sqrt((a - b) * (a - b) + length * length);
    }
    /* this one doesn't work 
    auto len = [length](double& a, double& b) {return sqrt((a-b)*(a-b) + length*length);};
    transform(road.begin(), road.end(), result.begin(), len);
    */
    ostream_iterator<double> os(cout, " m\n");
    copy(result.begin(), result.end(), os);

    double total = accumulate(result.begin(), result.end(), 0.0);
    cout << "Total distance: " << total << " m" << endl;
}
