#include <iostream>
#include <cmath> // for std::sqrt
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iomanip>
using namespace std;
// time taken: 1h
int main(int argc, char** argv)
{
    if (argc < 2)
    {
	cerr << "Usage: " << argv[0] << " FILE" << endl;
	return 1;
    }

    // filename is stored in argv[1]

    // implement the steps here
    string filename = argv[1];
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Couldnt open file." << endl;
        return 1;
    }
    
    double dx;
    ifs >> dx;
    vector<double> values{}; // y values
    copy(istream_iterator<double>{ifs}, istream_iterator<double>{}, back_inserter(values));
    
    vector<double> lengths{values};
    adjacent_difference(values.begin(), values.end(), lengths.begin());
    
    lengths.erase(lengths.begin()); // first element is not a difference

    auto s = [dx](double dy) { return sqrt(dx*dx + dy*dy); };
    transform(lengths.begin(), lengths.end(), lengths.begin(), s);
    
    double total2 = accumulate(lengths.begin(), lengths.end(), 0.0);

    cout << "total length: " << total2 << endl;

}
