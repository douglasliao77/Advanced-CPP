#include <type_traits>




// Primary template
template <typename T, typename... Ts>
struct occurance_count { };

// Base case
template <typename T>
struct occurance_count<T>
{
    static constexpr int value = 0;
};

template <typename T, typename... Rest>
struct occurance_count<T, T, Rest...>
{
     static constexpr int value = 1 + occurance_count<T, Rest...>::value;
};

// Recursion case
template <typename T, typename First, typename... Rest>
struct occurance_count<T, First, Rest...>
{
    static constexpr int value = 0 + occurance_count<T, Rest...>::value;
};




template <typename... T>
struct most_common{ };  

template <typename T>
struct most_common<T>
{
    using type = T;
    static constexpr int value = 1;
};  

template <typename T, typename... Ts>
struct most_common<T,Ts...>
{
private: 
    static constexpr int current = occurance_count<T, T, Ts...>::value;
    static constexpr int rest = most_common<Ts...>::value;
public: 
    static constexpr int value = current > rest ? current : rest; 
    using type = typename std::conditional_t<(current >= rest), 
                            T,
                            typename most_common<Ts...>::type>; 
};  



template <typename... Ts>
struct most_common_t
{
    using type = typename most_common<Ts...>::type;
};  


int main()
{
    static_assert( occurance_count<int, float, double>::value == 0 );
    static_assert( occurance_count<int, float, int>::value == 1 );
    static_assert( occurance_count<float, float, int, int , float>::value == 2 );

    static_assert( most_common<int>::value == 1 );
    static_assert( most_common<int, float>::value == 1 );
    static_assert( most_common<int, float, float, double, double,double >::value == 3 );

    static_assert( std::is_same_v<most_common_t<int, float, double>::type, int> );
    static_assert( most_common<int, float, double>::value == 1 );
    
    static_assert( std::is_same_v<most_common_t<int, float, double, int>::type, int> );
    static_assert( most_common<int, float, double, int>::value == 2 );
    
    static_assert( std::is_same_v<most_common_t<float, int, double, int>::type, int> );
    static_assert( most_common<float, int, double, int>::value == 2 );
    
    static_assert( std::is_same_v<most_common_t<float, int, float, double, int>::type, float> );
    static_assert( most_common<float, int, float, double, int>::value == 2 );

    static_assert( std::is_same_v<most_common_t<int, float, int, double, int>::type, int> );
    static_assert( most_common<int, float, int, double, int>::value == 3 );
}
