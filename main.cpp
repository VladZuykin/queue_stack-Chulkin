#include <iostream>
#include "queue_stack.h"

using namespace std;


int main()
{

    Queue<int> queue = Queue<int>();
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    queue.Push(4);

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

    Queue<int> queue1(queue);

    cout << queue;
    cout << queue1;

//    cin >> queue;


    queue1.Pop();
    queue1.Pop();

    queue.Pop();
    queue.Push(5);
    queue.Push(6);

    queue1.Push(7);

    cout << endl << queue << " " << queue1 << endl;

    queue1 = queue;
    cout << queue1;
    queue1.Pop();
    queue1.Push(100);
    cout << endl << queue1 << " " << queue << endl;



    Stack<int> stack = Stack<int>();
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);

    Stack<int> stack1(stack);

    cout << stack;
    cout << stack1;


    stack1.Pop();
    stack1.Pop();

    stack.Pop();
    stack.Push(5);
    stack.Push(6);

    stack1.Push(7);

    cout << endl << stack << " " << stack1 << endl;

    stack1 = stack;
    cout << stack1;
    stack1.Pop();
    stack1.Push(100);
    cout << endl << stack1 << " " << stack << endl;




//    cin >> queue1;
//    queue = Queue<int>();


//    cout << queue.GetFront() << endl << queue.GetFront() << endl;
//    cout << queue.Size();


//    Queue<int> queue = Queue<int>(), queue1;

//    cin >> queue;

//    cout << endl << queue << endl;

//    queue.Pop();
//    cout <<  queue << " " << queue.IsEmpty() << " " << queue.Size();
//    Queue<int> queue = Queue<int>(), queue1;
//    queue.Push(5);
//    cout << queue;
//
////    cin >> queue;
//
////    cout << endl << queue << " " << queue1 << endl;
//
////    cin >> queue1;
////    queue = Queue<int>();
//
//
////    cout << queue.GetFront() << endl << queue.GetFront() << endl;
////    cout << queue.Size();
//
//
//    Queue<int> queue = Queue<int>(), queue1;
//
//    cin >> queue;
//
//    cout << endl << queue << endl;
//
//    queue.Pop();
//    cout <<  queue << " " << queue.IsEmpty() << " " << queue.Size();

    return 0;
}
