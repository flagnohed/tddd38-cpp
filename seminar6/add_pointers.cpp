#include <type_traits>

namespace details
{
    // implement add_pointers function template here
    
    template<typename T, typename U, typename = typename std::enable_if_t<!std::is_pointer<U>::value>>
    T add_pointers_helper();

    // if U is a pointer
    
    template<typename T, typename U, typename = typename std::enable_if_t<std::is_pointer<U>::value>>
    auto add_pointers_helper(){
        return details::add_pointers_helper<T*, std::remove_pointer<U>>();
    }
    
}

template <typename T, typename U>
struct add_pointers
{
  using type = decltype(details::add_pointers_helper<T, U>());
};

int main()
{
  static_assert(std::is_same<add_pointers<int, int>::type, int>::value, "int + int = int");
  static_assert(std::is_same<add_pointers<int, int*>::type, int*>::value, "int + int* = int*");
  static_assert(std::is_same<add_pointers<int*, int*>::type, int**>::value, "int* + int* = int**");
  static_assert(std::is_same<add_pointers<int**, int*>::type, int***>::value, "int** + int* = int**");
  static_assert(std::is_same<add_pointers<int**, int***>::type, int*****>::value, "int** + int*** = int*****");
}
