#include <cassert>
#include <string>
#include <iostream>
#include <utility>

struct Sentinel{};

template<typename... Ts>
Sentinel make_list(){
    return Sentinel{};
}

template<typename T, typename... Ts>
auto make_list(T t, Ts... lst){
    
    return std::make_pair(t, make_list(lst...));
    
}

template<int N, typename T>
struct Get_Index{
    static auto& value(T& t){
        return Get_Index<N-1, decltype(std::get<1>(t))&>::value(std::get<1>(t));
    }
};

template<typename U>
struct Get_Index<0, U>{
    static auto& value(U& u){
        return std::get<0>(u);
    }
};

template<int N>
auto& get_index(auto& lst){
    return Get_Index<N, decltype(lst)>::value(lst);
}

int main()
{
    std::string last { "54" };
    auto list1 = make_list(1, 2.3, '4', last);
    
    assert(get_index<0>(list1) == 1);
    assert(get_index<1>(list1) == 2.3);
    assert(get_index<2>(list1) == '4');
    assert(get_index<3>(list1) == "54");

    // Check that the values can be modified
    get_index<0>(list1) = 10;
    assert(get_index<0>(list1) == 10);
    
}
