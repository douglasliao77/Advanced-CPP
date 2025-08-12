#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int haming_distance(std::string s1, std::string s2)
{
    if (s1.size() > s2.size())
    {
        std::swap(s1, s2);
    }
    int distance { std::inner_product(s1.begin(), s1.end(), 
        s2.begin(),0, std::plus<>(), std::not_equal_to<>()) };

    return distance + (s2.size() - s1.size());
}

int main()
{   

    // Fetch wordlist
    std::ifstream ifs { "wordlist.txt" };

    std::vector<std::string> wordlist {
        std::istream_iterator<std::string> { ifs },
        std::istream_iterator<std::string> { }
    };

    // Read input
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    
    std::sort(std::begin(wordlist), std::end(wordlist), 
        [&word](std::string s1, std::string s2) 
        {
            int a_dist { haming_distance(word, s1) };
            int b_dist { haming_distance(word, s2) };
            return a_dist < b_dist;
        }
    );

    std::copy_n(std::begin(wordlist), 5, 
        std::ostream_iterator<std::string>{std::cout, "\n"});


    return 1;
}

// Example runs:
//
// $ ./a.out 
// Enter your word: zest
// The five closest words are: 
// zesty
// zebra
// zonal
// quota
// mirth
//
// $ ./a.out 
// Enter your word: quilt
// The five closest words are: 
// guilt
// quiet
// quirk
// hoist
// quash
//
// $ ./a.out 
// Enter your word: brick
// The five closest words are: 
// brick
// price
// truce
// crisp
// braid
//
// $ ./a.out 
// Enter your word: vigorously
// The five closest words are: 
// vigor
// vapor
// lemon
// under
// rival
