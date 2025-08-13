#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>

using Task = std::pair<int, int>;

bool overlap(Task const& a, Task const& b)
{
    return !(a.second < b.first || a.first > b.second);
}

Task merge_or_split(Task const& burst, Task const& next)
{
    if (overlap(burst, next))
    {
	// merge the next task into the burst
        Task result { std::min(burst.first, next.first),
		      std::max(burst.second, next.second) };
	return result;
    }
    // split the timeline so that 'next' is the start of the next
    // burst.
    return next;
}

void read(std::istream& is, Task& task)
{
    is >> task.first >> task.second;
}

void write(std::ostream& os, Task const& task)
{
    os << task.first << " " << task.second;
}


namespace std
{
    std::istream& operator>>(std::istream& is, Task& task)
    {
        read(is, task);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Task& task)
    {
        write(os, task);
        return os;
    }
}


int main()
{
    std::ifstream ifs { "tasks.txt" };


    std::vector<Task> tasks {
        std::istream_iterator<Task> { ifs },
        std::istream_iterator<Task> { }
    };

    

    std::sort(std::begin(tasks), std::end(tasks));

    std::partial_sum(std::begin(tasks), std::end(tasks), std::begin(tasks), 
        merge_or_split);

    

    std::sort(std::begin(tasks), std::end(tasks), 
        [](const Task& t1, const Task& t2) 
        {
            if (t1.first < t2.first)
            {
                return true;
            }
            else if (t1.first == t2.first )
            {
                return t2.second < t1.second;
            } 
            return false;

        });

    tasks.erase(std::unique(std::begin(tasks), std::end(tasks),
        [](const Task& t1, const Task& t2)
        {
            return t1.first == t2.first;
        } 
        ) , 
    std::end(tasks));
    std::copy(std::begin(tasks), std::end(tasks), 
        std::ostream_iterator<Task> { std::cout, "\n"});

}

/* Example evaluation of the algorithm

Suppose we have the following list of (sorted) tasks:

1 5
2 7
6 8
9 12
11 14

Then we calculate the partial bursts as follows:

1. Pick 1 5 as the current burst => save 1 5
2. 2 7 overlaps with 1 5, so we extend the burst to 1 7 => save 1 7
3. 6 8 overlaps with 1 7, so we extend the burst to 1 8 => save 1 8
4. 9 12 does NOT overlap with 1 8, so we set 9 12 to be the next burst => save 9 12
5. 11 14 overlaps with 9 12, so we extend the burst to 9 14 => save 9 14

This will result in the following partial bursts [1 5, 1 7, 1 8, 9 12, 9 14].

We can then sort these burst based on start point primarily, and the
endpoint secondarily, which results in:

[1 8, 1 7, 1 5, 9 14, 9 12]

Note that the longest burst (which is the burst that cover the most
tasks) with a particular start point always occurs first due to how we
sort them.

We then remove all elements that share the same start point as a
previous element, making sure that each element has a unique start
point, resulting in:

[1 8, 9 14]

Which are the two bursts that occur in the CPU when it runs all the
initial tasks (intervals the CPU is /not/ idle).

Visually:

 Task5 |                     <----->         [ 11 14 ]
 Task4 |                 <----->   .         [  9 12 ]
 Task3 |           <---> .         .         [  6  8 ]
 Task2 |   <---------> . .         .         [  2  7 ]
 Task1 | <------->     . .         .         [  1  5 ]
       | .             . .         .
Result | <-------------> <--------->         [  1  8, 9 14 ]
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--> Time
       0         5         10        15
*/

/* Expected output of the given tasks.txt

1 17
19 31
37 61
67 85
87 98

*/
