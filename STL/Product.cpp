#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

struct Product
{
    std::string name { };
    double price { };
    int stock { };

};

std::istream& operator>>(std::istream& is, Product& product)
{
    is >> product.name >> product.price >> product.stock;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
    os << product.name << " (" << product.price << " SEK)\n";
    return os;
}

/* Expected output:

Total value of stock: 3381.1
Products in-stock: 
Fryer (249 SEK)
Mat (199.5 SEK)
Mop (129.9 SEK)
Broom (49.9 SEK)
Soap (39.9 SEK)
Wrap (29.5 SEK)
Bags (25.5 SEK)
Towel (19.8 SEK)
Brush (15 SEK)
Sponge (12.5 SEK)
Products out-of-stock: 
Iron (399 SEK)
Pot (299.5 SEK)
Trashcan (149 SEK)
Toilet (99.9 SEK)
Laundry (89.9 SEK)
Vacuum (79 SEK)
Cloth (79 SEK)
Cleaner (45 SEK)
Detergent (35.5 SEK)
Spray (25 SEK)

*/

int main()
{
    std::ifstream ifs { "products.txt" };

    // Read each product 
    std::vector<Product> products
    {
        std::istream_iterator<Product> { ifs },
        std::istream_iterator<Product> { }
    };


    double total_value = std::accumulate(std::begin(products), std::end(products), 0.0,
        [](double sum , const Product& p )
        {
            return sum + p.price*p.stock;
        } 
    );

    std::cout << total_value << "\n";

    auto It { std::partition(std::begin(products), std::end(products),
        [](const Product& p ) 
        {
            return p.stock > 0;
        } 
        )
    };

    std::sort(std::begin(products), It, [](const Product& p1, const Product& p2)
    {
        return p1.price > p2.price;
    });

    std::sort(std::next(It), std::end(products), [](const Product& p1, const Product& p2)
    {
        return p1.price > p2.price;
    });

    std::copy(std::begin(products), It, 
        std::ostream_iterator<Product>{std::cout, ""});

    std::cout << "Products out-of-stock: \n";

    std::copy(std::next(It), std::end(products), 
        std::ostream_iterator<Product>{std::cout, ""});

}
