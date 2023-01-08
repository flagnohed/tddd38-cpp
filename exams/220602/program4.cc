#include <iostream>
#include <fstream>

/*

Example runs:

$ ./a.out example.txt 
The following parameters are not defined:
#0
#1
#2
#3

$ ./a.out example.txt first second
The following parameters are not defined:
#2
#3

$ ./a.out example.txt first second third fourth
In this text first is a parameter, and the same is true for second
meaning that first and second can be whatever we want. Also, as a test
we add fourth as well, thus skipping the third argument (but as a test
we include third here).

 */

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	std::cerr << "USAGE: " << argv[0] << " TEXT [PARAMETERS...]\n";
	return 1;
    }

    std::ifstream ifs { argv[1] };
    if (!ifs)
    {
	std::cerr << "Error: Unable to open file '" << argv[1] << "'\n";
	return 2;
    }
    
}