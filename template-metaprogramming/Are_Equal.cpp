#include <type_traits>


template <typename... Ts>
struct Pack { };

// Primary template
template <typename T, typename Pack>
struct Contains
{ };

// Recursion case
template <typename T, typename First, typename... Rest>
struct Contains<T, Pack<First, Rest...>>
{
    static constexpr bool value = Contains<T, Pack<Rest...>>::value;
};  

// Base case
template <typename T>
struct Contains<T, Pack<>>
{
    static constexpr bool value = false;
};

template <typename T, typename... Rest>
struct Contains<T, Pack<T, Rest...>>
{
    static constexpr bool value = true;
};


// Primary template
template <typename FirstPack, typename SecondPack>
struct Is_Subset { };

// Recursion case
template <typename T, typename... Ts, typename... Us>
struct Is_Subset<Pack<T, Ts...>, Pack<Us...>>
{
    static constexpr bool value = Contains<T, Pack<Us...>>::value 
        && Is_Subset<Pack<Ts...>, Pack<Us...>>::value;
};

// Base case
template <typename... Us >
struct Is_Subset<Pack<>, Pack<Us...>>
{
    static constexpr bool value = true;
};

template <typename T, typename U>
struct Are_Equal {
    static constexpr bool value = false;
 };


template <typename... Ts, typename... Us>
struct Are_Equal<Pack<Ts...>, Pack<Us...>>
{
    static constexpr bool value = Is_Subset<Pack<Ts...>, Pack<Us...>>::value 
        && Is_Subset<Pack<Us...>, Pack<Ts...>>::value;
};


int main()
{
    using List = Pack<char, double, bool, int, bool, char>;

    static_assert( Contains<int, List>::value );
    static_assert( !Contains<unsigned, List>::value );

    static_assert( Is_Subset<Pack<int, char>, List>::value );
    static_assert( !Is_Subset<Pack<int, char, float>, List>::value );

    static_assert( Are_Equal<List, List>::value );
    static_assert( !Are_Equal<Pack<int, char>, List>::value );
}
