#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <set>
#include <algorithm>

struct Process
{
    std::string name { };
    std::vector<std::string> resources { };
};

std::istream& operator>>(std::istream& is, Process& process)
{
    std::string str, resource { };
    std::getline(is, str, '\n');
    std::istringstream iss { str };

    std::getline(iss, process.name, ':');

    process.resources = {
        std::istream_iterator<std::string>{ iss },
        std::istream_iterator<std::string>{ }
    };
    std::sort(process.resources.begin(), process.resources.end());

    return is;
}

std::ostream& operator<<(std::ostream& os, const Process& process)
{
    os << process.name << " : ";
    std::copy(std::begin(process.resources), std::end(process.resources),
        std::ostream_iterator<std::string> { os, " "} 
    );
    return os;
}



int main ()
{

    std::ifstream ifs { "processes.txt" };

    std::vector<Process> process {
        std::istream_iterator<Process> { ifs },
        std::istream_iterator<Process> { }
    };

    
    std::cout << "Enter resources that are busy: ";
    std::string input { };
    std::getline(std::cin, input);
    std::istringstream iss { input };

    std::vector<std::string> busy {
        std::istream_iterator<std::string> { iss },
        std::istream_iterator<std::string> { }
    };

    std::sort(std::begin(busy), std::end(busy));

    process.erase(remove_if(std::begin(process), std::end(process), 
        [&busy](const Process& p)
        {
            std::vector<std::string> v_intersection;
            std::set_intersection(p.resources.begin(), p.resources.end(), 
                                busy.begin(), busy.end(),
                                std::back_inserter(v_intersection));

            return v_intersection.size() > 0;
        })
    , std::end(process));


    std::copy(std::begin(process), std::end(process),
        std::ostream_iterator<Process> { std::cout, "\n"} 
    );


}

/* Example 1:

$ ./a.out
Enter resources that are busy: disk <ctrl+D>
Processs that can run unhindered:
Web Browser: network
Print Manager: network printer
Input Handler: keyboard
Image Processing: GPU display
Video Streaming: display network speakers
Print Driver Service: printer
Photo Viewer: display
Scientific Computation Module: GPU
Text Editor: display keyboard
Network Scanning Tool: USB network
Audio Playback: speakers
System Update Service: GPU USB network
Document Conversion Tool: display printer
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network

Example 2:

$ ./a.out 
Enter resources that are busy: network display printer GPU <ctrl+D>
Processs that can run unhindered:
Input Handler: keyboard
File Management Tool: USB disk
Audio Playback: speakers
Disk Cleaning Utility: disk

Example 3:

$ ./a.out 
Enter resources that are busy: USB speakers keyboard <ctrl+D>
Processs that can run unhindered:
Data Analysis Tool: disk network
Web Browser: network
Print Manager: network printer
Image Processing: GPU display
Print Driver Service: printer
Photo Viewer: display
Database Management System: disk network
Scientific Computation Module: GPU
Document Conversion Tool: display printer
Disk Cleaning Utility: disk
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network
*/