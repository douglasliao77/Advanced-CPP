#include <type_traits>

template <typename...> 
struct Pack { };

template <typename Left, typename Right>
struct Interleave { };

template <typename Left, typename Right>
struct Concat { };

template <typename... Left, typename... Right>
struct Concat<Pack<Left...>, Pack<Right...>>
{
    using type = Pack<Left..., Right...>;
};


// Recursive Case
template<typename FirstLeft, typename... RestLeft,
         typename FirstRight, typename... RestRight>
struct Interleave<Pack<FirstLeft, RestLeft...>, Pack<FirstRight, RestRight...>>
{
    using type = typename Concat<Pack<FirstLeft, FirstRight>, 
        typename Interleave<Pack<RestLeft...>, Pack<RestRight...>>::type>
        ::type;
};

// Base case
template<typename... Left>
struct Interleave<Pack<Left...>, Pack<>>
{
    using type = Pack<Left...>;
};

template<typename... Right>
struct Interleave<Pack<>, Pack<Right...>>
{
    using type = Pack<Right...>;
};

template<>
struct Interleave<Pack<>, Pack<>>
{
    using type = Pack<>;
};


int main()
{
    // two equally sized packs
    {
        using Left  = Pack<int, float>;
        using Right = Pack<unsigned, double>;

        using Interleaving = typename Interleave<Left, Right>::type;
        using Answer = Pack<int, unsigned, float, double>;

        static_assert( std::is_same_v<Interleaving, Answer> );
    }

    // Left is larger than Right
    {
        using Left  = Pack<int, float, bool, char>;
        using Right = Pack<unsigned, double>;

        using Interleaving = typename Interleave<Left, Right>::type;
        using Answer = Pack<int, unsigned, float, double, bool, char>;

        static_assert( std::is_same_v<Interleaving, Answer> );
    }

    // Right is larger than Left
    {
        using Left  = Pack<int, float>;
        using Right = Pack<unsigned, double, bool, char>;

        using Interleaving = typename Interleave<Left, Right>::type;
        using Answer = Pack<int, unsigned, float, double, bool, char>;

        static_assert( std::is_same_v<Interleaving, Answer> );
    }

    // Right is empty
    {
        using Left  = Pack<int, float>;
        using Right = Pack<>;

        using Interleaving = typename Interleave<Left, Right>::type;
        static_assert( std::is_same_v<Interleaving, Left> );
    }

    // Left is empty
    {
        using Left  = Pack<>;
        using Right = Pack<unsigned, double>;

        using Interleaving = typename Interleave<Left, Right>::type;
        static_assert( std::is_same_v<Interleaving, Right> );
    }

    // Both are empty
    {
        using Left  = Pack<>;
        using Interleaving = typename Interleave<Left, Left>::type;
        static_assert( std::is_same_v<Interleaving, Left> );
    }
}
