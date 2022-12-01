#include <iostream>
#include "queue_stack.h"

using namespace std;


void foo (const Queue<int>& s)
{

}

int main()
{

    Queue<int> queue;
    std::cin >> queue;
    Queue<int>::iterator it = queue.begin();
    while(it != queue.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << endl;
    it = queue.begin();
    while(it !=  queue.end())
    {
        *it += 50;
        std::cout << *it << " ";
        ++it;
    }
//    std::cout << *(it + (-3));
    std::cout << std::endl;

    const Queue<int> q1 = queue;

//    it = q1.begin();

    Queue<int>::const_iterator it1 = q1.begin(), it2 = q1.cbegin();
    std::cout << (it1 == it2) << std::endl;
    while(it1 != q1.cend())
    {
//        *it1 += 50;
        std::cout << *it1 << " ";
        ++it1;
    }


    return 0;
}
