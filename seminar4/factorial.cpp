#include <iostream>

using namespace std;


// using unsigned long long because of 20! doesnt fit in int

template <unsigned long long T>
unsigned long long factorial(){
    return T * factorial<T-1>(); 
}

template<>
unsigned long long factorial<0>(){
    return 1;
}


int main()
{
    cout << factorial<0>() << endl;
    cout << factorial<1>() << endl;
    cout << factorial<5>() << endl;
    cout << factorial<20>() << endl;
}