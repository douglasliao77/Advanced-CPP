#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>
#include <deque>
#include <iostream>
#include <utility>

namespace 
{
    void negate_helper(bool& value, int, int)
    {
        value = !value;
    }

    template <typename T>
    auto negate_helper(T& value, int, int) 
        -> std::enable_if_t<std::is_signed_v<T>>
    {
        value = -value;
    }

    template <typename Container>
    auto negate_helper(Container& c, int, int)
        -> std::enable_if_t<std::is_same_v<typename Container::value_type,char>>
    {
        std::reverse(std::begin(c), std::end(c));
    }

    template <typename Container>
    auto negate_helper(Container& c, int, float)
        ->  decltype(std::begin(c), std::begin(c), std::declval<void>())
    {
        for (auto& value : c)
        {
            negate_helper(value, 0, 0);
        }
    }

    template <typename T>
    auto negate_helper(T& value, float, float) 
    {
        value = ~value; 
    }

}


template <typename T>
auto negate(T& value)
{
    negate_helper(value,0,0);
    return value;

}


int main()
{

    // bool value
    bool b { true };
    assert(negate(b) == false);
    // signed value
    double n { 1.0 };
    assert(negate(n) == -1.0);

    // bitwise negation
    unsigned u { 2196674553u };
    assert(negate(u) == 2098292742u);

    // string
    std::string s { "drawer" };
    assert(negate(s) == "reward");

    // container
    std::vector<int> v { 1, -2, 3, -4 };
    assert(( negate(v) == std::vector<int>{ -1, 2, -3, 4 } ));

    // recursive container case
    std::vector<std::deque<std::string>> r {
	std::deque<std::string>{ "bat", "brag" },
	std::deque<std::string>{ "flow", "loop" }
    };

    std::vector<std::deque<std::string>> result {
	std::deque<std::string>{ "tab", "garb" },
	std::deque<std::string>{ "wolf", "pool" }
    };

    assert(negate(r) == result);

    // C-array case
    int a[] { 6, -4, 0, 5 };
    negate(a);

    assert(a[0] == -6);
    assert(a[1] == 4);
    assert(a[2] == 0);
    assert(a[3] == -5);
}
