#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// implement priority
namespace details{
    template<typename T, typename U>
    auto prepend_helper(T& container, U&& value, int, int) 
    -> decltype(container.push_front(value), std::declval<void>()){
        container.push_front(std::forward<U>(value));
    }

    template<typename T, typename U>
    auto prepend_helper(T& container, U&& value, int, float)
    -> decltype(container = value + container, std::declval<void>()){
        container = value + container; 
    }

    template<typename T, typename U>
    auto prepend_helper(T& container, U&& value, float, float)
    -> decltype(container.insert(container.begin(), std::forward<U>(value)), std::declval<void>()){
        container.insert(container.begin(), std::forward<U>(value));
    }
}


template<typename T, typename U>
void prepend(T& container, U&& value){
    details::prepend_helper<T, U>(container, std::forward<U>(value), 0, 0);
}



int main()
{
    std::vector<int> v { 1, 2, 3 };

    assert(v.front() == 1);
    prepend(v, 0);
    assert(v.front() == 0);
    
    std::list<float> d { 1.2f, 3.45f, 67.8f, 9.0f };

    assert(d.front() == 1.2f);
    prepend(d, 0);
    assert(d.front() == 0.0f);

    std::string s { "ello world!" };

    assert(s.front() == 'e');
    prepend(s, 'H');
    assert(s.front() == 'H');
    
}
