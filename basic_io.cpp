#include <iostream>
#include <istream>
#include <string>

using namespace std;
int main()
{
    // can only use these four variables
    int i;
    string s;
    double d;
    char c;
    const int MAX_VAL = 256;

    cout << "Enter one integer: ";
    cin >> i;
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered the number: " << i << endl;

    cout << "Enter four integers: ";
    getline(cin >> ws, s);
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered the numbers: " << s << endl;

    cout << "Enter one integer and one real number: ";
    cin >> i >> d;
    cin.ignore(MAX_VAL, '\n');
    cout << "The real is: " << d << endl;
    cout << "The integer is: " << i << endl;

    cout << "Enter one real and one integer number: ";
    cin >> d >> i;
    cin.ignore(MAX_VAL, '\n');
    cout << "The real is: " << d << endl;
    cout << "The integer is: " << i << endl;

    cout << "Enter a character: ";
    cin >> c;
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered: " << c << endl;

    cout << "Enter a word: ";
    cin >> s;
    cin.ignore(MAX_VAL, '\n');
    cout << "The word " << s << " has " << s.length() << " character(s)" << endl;

    cout << "Enter an integer and a word: ";
    cin >> i >> s;
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered " << i << " and " << s << endl;

    cout << "Enter a character and a word: ";
    cin >> c >> s;
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered the string " << s << " and the character " << c << endl;

    cout << "Enter a word and real number: ";
    cin >> s >> d;
    cin.ignore(MAX_VAL, '\n');
    cout << "You entered " << s << " and " << d << endl;

    cout << "Enter a text-line: ";
    getline(cin, s);
    cout << "You entered: " << s << endl;

    cout << "Enter a second line of text: ";
    getline(cin, s);
    cout << "You entered: " << s << endl;

    cout << "Enter three words: ";
    getline(cin >> ws, s);
    cout << "You entered: " << s << endl;

    return 0;
}
