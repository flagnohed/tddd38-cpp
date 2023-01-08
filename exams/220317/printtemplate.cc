#include <iostream>
#include <vector>

void print() {
    std::cout << std::endl;
}

template<typename T, typename... Ts>
void print(T&& first, Ts const&... rest) {
    std::cout << first;
    print(rest...);
}



int main(){
    int x{7};
    print("hej");
    print("Så här många tänder har jag kvar: ", x);


    return 0;
}