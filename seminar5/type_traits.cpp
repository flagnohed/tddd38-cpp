// Implement is_const, is_pointer, is_array and is_const_pointer here


// is_const
template<typename T>
struct is_const
{
    static bool const value{false};
};

template<typename T>
struct is_const<T const>
{
    static bool const value{true};
};

// is_pointer
template<typename T>
struct is_pointer
{
    static bool const value{false};
};

template<typename T>
struct is_pointer<T*>
{
    static bool const value{true};
};

template<typename T>
struct is_pointer<T* const>
{
    static bool const value{true};
};

// is_array
template<typename T>
struct is_array
{
    static bool const value{false};
};

template<typename T, int N>
struct is_array<T[N]>
{
    static bool const value{true};
};

template<typename T>
struct is_const_pointer
{
    static bool const value{false};
};

template<typename T>
struct is_const_pointer<T* const>
{
    static bool const value{true};
};


int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}