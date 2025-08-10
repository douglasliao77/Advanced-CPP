#include <type_traits>

template <typename...>
struct Pack { };

/* Implement Reverse here */
namespace details {

    // Primary template
    template <typename T, typename U>
    struct Reverse;

    // Recursive case
    template <typename T, typename... Ts, typename... Us>
    struct Reverse<Pack<T, Ts...>, Pack<Us...>> {
        using type = typename Reverse<Pack<Ts...>, Pack<T,Us...>>::type;
    };

    // Base case
    template <typename... Us>
    struct Reverse<Pack<>, Pack<Us...>> {
        using type = Pack<Us...>;
    };
}

template <typename T>
struct Reverse 
{
    using type = typename details::Reverse<T,Pack<>>::type;
};

int main()
{
    {
        using Input  = Pack<>;
        using Output = Pack<>;

        using Result = typename Reverse<Input>::type;
        static_assert( std::is_same_v<Result, Output> );
    }

    {
        using Input  = Pack<int>;
        using Output = Pack<int>;

        using Result = typename Reverse<Input>::type;
        static_assert( std::is_same_v<Result, Output> );
    }

    {
        using Input  = Pack<int, float>;
        using Output = Pack<float, int>;

        using Result = typename Reverse<Input>::type;
        static_assert( std::is_same_v<Result, Output> );
    }

    {
        using Input  = Pack<int, float, bool>;
        using Output = Pack<bool, float, int>;

        using Result = typename Reverse<Input>::type;
        static_assert( std::is_same_v<Result, Output> );
    }
}
