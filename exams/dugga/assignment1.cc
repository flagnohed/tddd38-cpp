#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <string>

// Originally taken from: 2022-03-17 Assignment #4
// Modified so that it doesn't require type converting operators.

template<typename T>
class Stack {
public:
    template<typename... Ts>
    //cant initialize the vector???
    //error: no matching function for call to 
    // ‘std::vector<int, std::allocator<int> >::vector(<brace-enclosed initializer list>)’

    Stack(Ts&&... ts) : storage { std::forward<Ts>(ts)... }
    {  }

    
    //push
    T operator<<(T value) {
        storage.push_back(value);
        return value;
    } 
    //pop
    T operator>>(T& value) {
        value = storage.back();
        storage.pop_back();
        return value;
    } 
   

    bool operator==(T value) {
        return storage.back() == value;
    }

    bool is_empty() {
        return storage.empty();
    }
    
private:
    std::vector<T> storage{};

};

 //print
 template<typename T>
std::ostream& operator<<(std::ostream& os, Stack<T> st) {
    Stack<T> stack_copy{st};
    while (!stack_copy.is_empty()) {
        T a;
        stack_copy >> a;
        os << a << " ";
    }
    return os;
}


int main()
{
    {
	Stack<int> st { 6, 5, 4 };

	// 4 should be at the top of the stack
	assert( st == 4 );
	
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;

	// now 1 should be at the top
	assert( st == 1 );

	std::ostringstream oss { };
	oss << st;
	
	assert( oss.str() == "1 2 3 4 5 6 ");

	// popping into a, b and c as a chained operator call.
	int a, b, c;
	st >> a >> b >> c;

	assert( a == 1 );
	assert( b == 2 );
	assert( c == 3 );

	// pop the values one by one
	int i { 4 };
	while (st.is_empty())
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}
    }
}