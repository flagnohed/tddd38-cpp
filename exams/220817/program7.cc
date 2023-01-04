#include <cassert>
#include <cstddef>
#include <iterator>
#include <list>
#include <vector>
#include <iostream>
template<typename T>
std::size_t count_bytes(T&& item);
namespace details {
    // prio with type conversion
    // prio: container, then normal
    template<typename T>
    auto count_bytes(T const& container, int) 
        -> decltype(std::begin(container), std::size_t{}) {
            std::size_t total{};
            for (auto const& item : container) {
                total += ::count_bytes(item);
            }
            return total;
        }
    
    template<typename T>
    auto count_bytes(T const& value, float) {
        return sizeof(value);
    }

}

template<typename T>
std::size_t count_bytes(T&& item) {
    return details::count_bytes<T>(std::forward<T>(item), 0);
}

int main()
{
    int x { 9 };
    assert(count_bytes(x) == sizeof(int));

    std::vector<int> v { 1, 2, 3 };
    assert(count_bytes(v) == 3 * sizeof(int));

    std::list<std::vector<std::string>> l {
	{ "a", "bc" }, // 3 chars
	{ },           // 0 chars
	{ "defg" },    // 4 chars
    };

    // 3 + 0 + 4 = 7 chars
    assert(count_bytes(l) == 7 * sizeof(char));

    std::vector<int> array[] = {
	{ 1, 2, 3, 4 }, // 4 ints
	{ 5, 6 },       // 2 ints
	{ },            // 0 ints
	{ 7, 8 },       // 2 ints
    };

    // 4 + 2 + 0 + 2 = 8 ints
    assert(count_bytes(array) == 8 * sizeof(int));
}