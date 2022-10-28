#include <iostream>
#include "queue_stack.h"

using namespace std;

int main()
{
    Stack<int> stack = Stack<int>(), stack1;
    stack.Push(5);
    cout << stack;

//    cin >> stack;

//    cout << endl << stack << " " << stack1 << endl;

//    cin >> stack1;
//    stack = Stack<int>();


//    cout << stack.GetFront() << endl << stack.GetFront() << endl;
//    cout << stack.Size();


    Queue<int> queue = Queue<int>(), queue1;

    cin >> queue;

    cout << endl << queue << endl;

    queue.Pop();
    cout <<  queue << " " << queue.IsEmpty() << " " << queue.Size();

    return 0;
}
