#include <string>
#include <iostream>
#include <iomanip>
#include <istream>
using namespace std;


/*
 * Assuming: Last price > first price, inputs will be
 * in the interval [-100.00, +100000.00].
 */

int main(){
    float first_price, last_price, stride, tax_percent;
    cout << "INPUT PART" << endl;
    cout << "==========" << endl;

    while (1){
        cout << "Enter first price: ";
        cin >> first_price;
        if (first_price < 0){
            cerr << "ERROR: First price must be at least 0 (zero) SEK" << endl;
        } else {
            break;
        }
    }


    while (1){
        cout << "Enter last price: ";
        cin >> last_price;
        if (last_price < 0){
            cerr << "ERROR: Last price must be at least 0 (zero) SEK" << endl;
        } else {
            break;
        }
    }

    while (1){
        cout << "Enter stride: ";
        cin >> stride;
        if (stride < 0.01){
            cerr << "ERROR: Stride must be at least 0.01" << endl;
        } else {
            break;
        }
    }

    while (1){
        cout << "Enter tax percent: ";
        cin >> tax_percent;
        if (tax_percent > 100 || tax_percent < 0){
            cerr << "ERROR: Tax percent must be between 0 and 100" << endl;
        } else {
            break;
        }
    }

    cout.precision(2);
    cout << "TAX TABLE" << endl;
    cout << "==========" << endl;
    cout << "Price      Tax         Price with tax" << endl;
    cout << "-------------------------------------" << endl;
    for (float p = first_price; p <= last_price; p += stride){
        float tax = p*tax_percent/100;

        cout << fixed << p << "    " << tax << "     " << p + tax << endl;
    }
    return 0;
}
