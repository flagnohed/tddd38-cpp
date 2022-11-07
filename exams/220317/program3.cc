#include <iostream>
#include <cmath> // for std::sqrt
#include <fstream>
#include <vector>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
	return 1;
    }

    // filename is stored in argv[1]

    // implement the steps here

    std::ifstream f(argv[1]);
    if (f.is_open()) {
        double dx;
        f >> dx;
        std::vector<double> values{};
        double y;
        while (f >> y) {
            values.push_back(y);
        }

        std::vector<double> lengths{};
        for (auto it = values.begin(); it < values.end() - 1; it++) {
            auto next = std::next(it, 1);
            double diff = *it - *next;
            lengths.push_back(diff);

        }
        double arc_length{};
        for (double dy : lengths) {
            arc_length += std::sqrt(dx*dx + dy*dy);
        }
        std::cout << "Calculated arc length: " << arc_length << std::endl;



    } else {
        std::cerr << "File does not exist." << std::endl;
        return 0;
    }


}