#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;



template<typename T>
T add(T const& lhs, T const& rhs){
    return lhs + rhs;
}

//N: size of array
template<typename T, int N>
T reduce(T const (&array)[N], T a={}, T (*func)(T const&, T const&) = add<T>){
    T res = func(a, array[0]);
    for (int i = 1; i < N; i++){
        res = func(res, array[i]);
    }
    return res;
}

double add(double const& lhs, double const& rhs){
    return lhs + rhs;
}

double multiply(double const& lhs, double const& rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1,2,3,4,5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}