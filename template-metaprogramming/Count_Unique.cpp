#include <type_traits>
#include <iostream>

template <typename... Ts>
struct Pack
{
    static constexpr std::size_t size = sizeof...(Ts);
};

// Primary tempalte
template <typename T, typename... Ts>
struct Contains;

// Recursion case
template <typename T, typename First, typename... Rest>
struct Contains<T, First, Rest...>
{
    static constexpr bool value = Contains<T, Rest...>::value;
};

// Base case
template <typename T, typename... Rest>
struct Contains<T, T, Rest...>
{
    static constexpr bool value = true;
};

template <typename T>
struct Contains<T>
{
    static constexpr bool value = false;
};

// Primary template
template <typename Result, typename... Rest>
struct Make_Unique;

// Recursion base
template <typename... Result, typename First, typename... Rest>
struct Make_Unique<Pack<Result...>, First, Rest...>
{
private: 
    using result = std::conditional_t<Contains<First, Result...>::value,
                                    Pack<Result...>,
                                    Pack<Result..., First>>;
public:
    using type = typename Make_Unique<result, Rest...>::type; 
};

// Base case
template <typename... Result>
struct Make_Unique<Pack<Result...>>
{   
    using type = Pack<Result...>;
};


template <typename... Ts>
struct Count_Unique
{
private:
    using result = typename Make_Unique<Pack<>, Ts...>::type;
public:
    static constexpr std::size_t value = result::size;
};

int main()
{
    static_assert(Contains<int, float, float>::value == 0);
    static_assert(Contains<int, float, int>::value == 1);

    static_assert( Count_Unique<>::value == 0 );
    static_assert( Count_Unique<int, int, int>::value == 1 );
    static_assert( Count_Unique<int, float, int, bool>::value == 3 );
    static_assert( Count_Unique<int, int, int, float>::value == 2 );
    static_assert( Count_Unique<float, int, int, int>::value == 2 );
}
