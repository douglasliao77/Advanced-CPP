# Template Metaprogramming

This folder contains 20+ C++ template metaprogramming exercises focused on type traits and template parameter pack manipulation.

---

## Exercises

1. **Reverse.cpp**  
   Implement a type trait `Reverse` that reverses a template parameter pack. Uses partial specialization and recursion.

2. **Interleave.cpp**  
   Implement `Interleave` to merge two `Pack`s by alternating their elements.

3. **Count_Unique.cpp**
    Implement Count_Unique to count unique types in a variadic pack by building a Pack of unique types with Make_Unique and checking membership with Contains. The count is stored in value.

4. **Are_Equal.cpp**  
   Implement `Are_Equal` to determine if two `Pack`s contain exactly the same types (order does not matter). Use `Is_Subset` in both directions to check equality, resulting in a boolean `value`.

5. **Most_Common.cpp**
    Find the most frequent type in a pack using occurance_count and std::conditional_t to set value and type.

6. **Largest_Type.cpp**
    Implement Largest_Type to find the type with the largest size (sizeof) in a pack. Provide a nested type alias and a value for the size.