#include <iostream>
using namespace std;
int n{};

int& foo(int& n){
    return n;
}

int bar(int&  n){
    return n;
}

int&& move(int& n){
    return static_cast<int&&>(n);
}

void ex_3(){
    char p {'a'};
    char* ptr {&p};
    int array[10]{1,2,3};
    char** pptr {&ptr};
    int const n {4};
    int const* np {&n};
    int* const npp {&array[0]};
}

int main(){
    return 0;
}

/*
 * glvalue: generalized lvalue
 * prvalue: pure rvalue
 * xvalue: expriring value
 * lvalue: left hand side
 * rvalue: right hand side
 */

/*
 * Q: What is the value categories of the following expressions?
 * 1a: n -- lvalue
 * 1b: n+1 -- prvalue
 * 1c: n=2 -- lvalue
 * 1d: double{} -- prvalue
 * 1e: move(n) -- lvalue
 * 1f: foo(n) -- lvalue
 * 1g: bar(n) -- prvalue
 * 1h: foo(n=bar(n)) -- lvalue
 *
 * Q: Write declarations for the following variables:
 * 2a: char* p;
 * 2b: int arr[10];
 * 2c: std::string (*str_arr[3]);
 * 2d: char** cptr;
 * 2e: int const i;
 * 2f: int const* i;  / pointer to constant int
 * 2g: int* const i;  // constant pointer to i
 *
 * Q: Write a program that initializes all the variables from exercise 2:
 * Answer put in ex_3 func.
 *
 * 4a: Legal. Is a function declaration with input int, output int.
 * 4b: Legal. Same as a except the name of the input variable is not included.
 * 4c: Legal. Function a with input parameter i, with redundant parentesis. They are disregarded by the compiler and flagged as semantic warning.
 * 4d: Legal. Function a with input parameter i as a pointer to a function that returns a int with no input.
 * 4e: Legal. Function a with input parameter with no name that is a constant pointer to an int. Returns int.
 * 4f: Illegal.
 * 4g: Legal. Function a returns int with input as a pointer to a function returning a pointer to a constant int with no input.
 * 4h: Function a returns int, takes a pointer to a function as input that returns an int and has an int as input.
 *
 * using x = int (&)(int, int);
 * x is a reference to a function that returns an int and has two ints as input parameters.
 * this can be used in combination with:
 * int func(int a, int b){return a;}
 * x new_func {func};
 * return new_func{1,2};
 *
 * 6
 * Size of msg: 13
 * Length of C-string: 12
 * It is because the last character is the '\0', denoting the end of the string.
 *
 * 7
 * int i1{}; == 0
 * int i2(2); == 2
 * int i3 = 1; == 1
 * int i4 = {}; // invalid, it initializes to an array but the type is just int.
 * int i5();  // invalid for variables, this interprets as a function named i5 that returns int with no input parameter.
 * string str1{}; == ""
 * string str2("hello"); == "hello"
 * string str4(3, 'a');  // not valid variable declaration. Interprets as a function returning string with int param and char param.
 * string str5 = str2; == "hello"
 * float f1{5.37e100}; // too big to be a float, cannot convert to correct type.
 * float f2 = 5.37e100 == inf // copy that value into f2, but its too big so it takes the value as inf.
 * float f3{1738335806};  // invalid, too big. Needs recasting to be valid, since float cant handle these big numbers with this declaration.
 * (note: when using copy as declaration, narrowing conversion isn't checked, therefore it says inf.)
 */
