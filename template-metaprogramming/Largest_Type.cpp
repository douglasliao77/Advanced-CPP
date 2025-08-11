#include <type_traits>


// Primary template
template <typename... Ts>
struct largest_type
{ };

// Base case
template <typename T>
struct largest_type<T>
{ 
    using type = T;
};

// Recursion case
template <typename T, typename First, typename... Rest>
struct largest_type<T, First, Rest...>
{
    using type = std::conditional_t<(sizeof(T) > sizeof(First)), 
                                    typename largest_type<T,Rest...>::type,
                                    typename largest_type<First,Rest...>::type>;
};

// Alias
template <typename... Ts>
using largest_type_t = typename largest_type<Ts...>::type;

int main()
{
    static_assert( std::is_same_v< largest_type<int>::type, int > );
    static_assert( std::is_same_v< largest_type<int, int>::type, int >);
    static_assert( std::is_same_v< largest_type<int>::type, int > );
    static_assert( std::is_same_v< largest_type<int, char>::type, int > );
    static_assert( std::is_same_v< largest_type<int, char, double>::type, double > );

    static_assert( std::is_same_v< largest_type_t<int>, int > );
    static_assert( std::is_same_v< largest_type_t<int, char>, int > );
    static_assert( std::is_same_v< largest_type_t<int, char, double>, double > );
}
