#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>

// TODO: Figure out what containers to use

auto read_table(std::istream& is)
{
    std::map<std::string, std::set<std::string>> result { };
    
    std::string line;
    while (std::getline(is, line))
    {
	std::istringstream iss { line };
	std::string entry { };
	std::string tag   { };
    std::set<std::string> tags { };
	
	iss >> entry;
	while (iss >> tag){
        tags.insert(tag);
    }
    result[entry] = tags;
    }

    return result;
}


int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
	std::cerr << "Usage: " << argv[0] << " FILE [TAGS...]" << std::endl;
	return 1;
    }
    
    std::ifstream ifs { argv[1] };
    std::set<std::string> tags { &argv[2], &argv[argc] };

    auto table = read_table(ifs);

    std::vector<std::pair<std::string, std::set<std::string>>> filtered {
        table.begin(), table.end()
    };


    filtered.erase(std::remove_if(filtered.begin(), filtered.end(), 
        [&tags](auto pair) 
        {
            return !std::includes(pair.second.begin(), pair.second.end(),
					      tags.begin(), tags.end());
        }
    ), filtered.end());

    std::vector<std::string> result ;

    std::transform(filtered.begin(), filtered.end(), std::back_inserter(result), 
        [](auto pair)
        {
            return pair.first; 
        });

    std::sort(result.begin(), result.end());

    std::copy(result.begin(), result.end(), 
        std::ostream_iterator<std::string> { std::cout, "\n"});

}


/* Expected output:

$ ./a.out names.txt Male Female
Alex
Austin
Avery
Blake
Brooklyn
Charlie
Drew
Jordan
Kennedy
Parker
Taylor

$ ./a.out names.txt Female
Abigail
Alex
Amelia
Austin
Ava
Avery
Blake
Brooklyn
Camila
Charlie
Charlotte
Drew
Eleanor
Elizabeth
Ella
Emma
Evelyn
Gianna
Harper
Isabella
Jordan
Kennedy
Luna
Mia
Olivia
Parker
Scarlett
Sofia
Sophia
Taylor

 */