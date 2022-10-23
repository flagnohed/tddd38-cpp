#include <type_traits>

template <typename T>
struct remove_reference
{
  using type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using type = T;
};


// base case
template<typename T>
struct remove_pointers
{
    using type = T;
};

// pointer
template<typename T>
struct remove_pointers<T*>
{
    using type = typename remove_pointers<T>::type;  // remove first pointer
};

// constant pointer
template<typename T>
struct remove_pointers<T* const>
{
    using type = typename remove_pointers<T*>::type;  // send to pointer template
};

int main()
{
  static_assert(std::is_same<
                remove_reference<int&&>::type, int
                >::value, "remove_reference failed for 'int&&'");
  static_assert(std::is_same<
                remove_reference<int&>::type, int
                >::value, "remove_reference failed for 'int&'");
  static_assert(std::is_same<
                remove_reference<int>::type, int
                >::value, "remove_reference failed for 'int'");
  static_assert(std::is_same<
                remove_reference<int const&>::type, int const
                >::value, "remove_reference failed for 'int const&'");

  static_assert(std::is_same<
                remove_pointers<int>::type, int
                >::value, "remove_pointers failed for 'int'");
  static_assert(std::is_same<
                remove_pointers<int*>::type, int
                >::value, "remove_pointers failed for 'int*'");
  static_assert(std::is_same<
                remove_pointers<int* const>::type, int
                >::value, "remove_pointers failed for 'int* const'");
  static_assert(std::is_same<
                remove_pointers<int* const*>::type, int
                >::value, "remove_pointers failed for 'int* const*'");
  static_assert(std::is_same<
                remove_pointers<int***>::type, int
                >::value, "remove_pointers failed for 'int***'");
}
