#include <utility>
#include <iostream>

/*
The idea is to create 4 helper functions.
To bypass the ambiguous overloads, use conversion to
enforce priority.
*/

// prio 1, no conversions needed
template<typename T>
auto prio_helper(T&& t, int, int, int) -> decltype(t.first())
{
    return t.first();
}

// prio 2, 1 conversion needed
template<typename T>
auto prio_helper(T&& t, int, int, double) -> decltype(t.second())
{
    return t.second();
}

// prio 3, 2 conversions needed
template<typename T>
auto prio_helper(T&& t, int, double, double) -> decltype(t.third())
{
    return t.third();
}

// prio 4, 3 conversions needed
template<typename T>
int prio_helper(T&& t, double, double, double)
{
    return 4;
}



template <typename T>
auto get_priority(T&& t)
{
    return prio_helper(std::forward<T>(t), 0, 0, 0);
}



struct X
{
  int first() const { return 1; }
};

struct Y
{
  int second() const { return 2; }
};

struct Z
{
  int third() const { return 3; }
};

struct XY
{
  int first() const { return 1; }
  int second() const { return 2; }
};

struct XZ
{
  int first() const { return 1; }
  int third() const { return 3; }
};

struct YZ
{
  int second() const { return 2; }
  int third() const { return 3; }
};

struct XYZ
{
  int first() const { return 1; }
  int second() const { return 2; }
  int third() const { return 3; }
};

int main()
{
  using std::cout;
  using std::endl;
  
  cout << get_priority(X{}) << endl
       << get_priority(Y{}) << endl
       << get_priority(Z{}) << endl
       << get_priority(XY{}) << endl
       << get_priority(XZ{}) << endl
       << get_priority(YZ{}) << endl
       << get_priority(XYZ{}) << endl
       << get_priority(5) << endl;
}
