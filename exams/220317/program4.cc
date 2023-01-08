#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>

// time taken: 1.5h

template<typename T>
class Stack {
public:
    template<typename... Ts>
    Stack(Ts&&... ts) : storage{std::vector<T>{std::forward<Ts>(ts)...}}{
    }
    
    

    Stack<T>& operator<<(T t) {
        storage.push_back(t);
        return *this;
    }
    Stack<T>& operator>>(T& t) {
        if (!storage.empty()) {
            t = storage.back();
            
            storage.pop_back();
        }
            
        return *this;
    }
    operator bool() {
        return !storage.empty();
    }

    operator T() {
        return storage.back();
    }


    std::ostream& print(std::ostream& os) const {
        for (std::size_t i{storage.size()}; i > 0; i--) {
            os << storage[i-1] << " ";
        }
        return os;
    }
    

    

private: 
    std::vector<T> storage;
};
template<typename T>
std::ostream& operator<<(std::ostream& os, Stack<T> const& st) {
        return st.print(os);
}

int main()
{   // everything works except printing to ostream
    {
	Stack<int> st { 6, 5, 4 };

	// 4 should be at the top of the stack
	assert( st == 4 );
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;
	// now 1 should be at the top
	assert( st == 1 );
	
	// stack must be convertible to bool
	assert( st );

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
	while (st)
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}

	// now the list should be empty
	assert( !st );
    }
    

}
