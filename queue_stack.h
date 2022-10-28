#ifndef QUEUE_STACK_H_INCLUDED
#define QUEUE_STACK_H_INCLUDED

#include <iostream>
#include <stddef.h>
#include <stdexcept>

template <class T>
class OneLinkedList
{
public:
    virtual ~OneLinkedList() {};

    virtual void Push(const T) = 0;
    virtual T Pop() = 0;
    virtual T GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
//    virtual OneLinkedList<T>& operator =(const OneLinkedList<T>& other) = 0;
//    virtual OneLinkedList<T>& operator =(OneLinkedList<T>&& other) = 0;

    template<class F> friend std::istream& operator >>(std::istream& stream, OneLinkedList<F>& lst);
    template<class F> friend std::ostream& operator <<(std::ostream& stream, const OneLinkedList<F>& lst);

protected:
    virtual void Print() const = 0;
    typedef struct link
    {
        T value;
        struct link* next;
    } Node;
};


template<class T>
std::istream& operator >>(std::istream& stream, OneLinkedList<T>& lst)
{
    size_t n;
    T value;
    std::cout << "Please, enter the number of elements." << std::endl;
    std::cin >> n;
    std::cout << "Please, input "<< n <<" elements." << std::endl;
    for(size_t i = 0; i < n; ++i)
    {
        std::cin >> value;
        lst.Push(value);
    }
    return stream;
}

template<class T>
std::ostream& operator <<(std::ostream& stream, const OneLinkedList<T>& lst)
{
    std::cout << "[";
    lst.Print();
    std::cout << "]";
    return stream;
}


// Stack class//
//////////////////////////////////////////////

template <class T>
class Stack: public OneLinkedList<T>
{
public:
    Stack();
    ~Stack();
    Stack(const Stack& other);
    Stack(Stack&& other);

    void Push(const T);
    T Pop();
    T GetFront() const;
    bool IsEmpty() const;
    size_t Size() const;
    Stack<T>& operator =(const Stack<T>& other);
    Stack<T>& operator =(Stack<T>&& other);
protected:
    void Print() const;
    typename OneLinkedList<T>::Node *head;
};

// Stack constructors and operators //
//////////////////////////////////////////////

template <class T>
Stack<T>::Stack()
{
    head = nullptr;
}

template <class T>
Stack<T>::~Stack()
{
    while(!this->IsEmpty())
    {
        this->Pop();
    };
}

template <class T>
Stack<T>::Stack(const Stack& other)
{
    if(other.IsEmpty())
    {
        this->head = nullptr;
        return;
    }

    this->head = new typename OneLinkedList<T>::Node;
    typename OneLinkedList<T>::Node* src_node = other.head;
    this->head->value = src_node->value;
    this->head->next = nullptr;

    for(typename OneLinkedList<T>::Node* tmp_node = this->head;
            src_node->next;
            tmp_node = tmp_node->next, src_node = src_node->next)
    {
        tmp_node->next = new typename OneLinkedList<T>::Node;
        tmp_node = tmp_node->next;
        src_node = src_node->next;

        tmp_node->value = src_node->value;
        tmp_node->next = nullptr;
    }
}

template <class T>
Stack<T>::Stack(Stack&& other)
{
    this->head = other.head;
    other.head = nullptr;
}

template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& other)
{
    if(this == &other)
        return *this;

    if(other.IsEmpty())
    {
        while(!this->IsEmpty())
        {
            this->Pop();
        }
        return *this;
    }

    if(!this->head)
    {
        this->head = new typename OneLinkedList<T>::Node;
        this->head->value = other.head->value;
    }

    typename OneLinkedList<T>::Node* tmp_node = this->head;
    typename OneLinkedList<T>::Node* src_node = other.head;
    for(; src_node->next && tmp_node->next; src_node = src_node->next, tmp_node = tmp_node->next)
        tmp_node->value = src_node->value;
    tmp_node->value = src_node->value;

    if(!src_node->next && tmp_node->next)
    {
        typename OneLinkedList<T>::Node* tmp_node2 = tmp_node->next;
        tmp_node->next = nullptr;

        while(tmp_node2)
        {
            tmp_node = tmp_node2->next;
            delete tmp_node2;
            tmp_node2 = tmp_node;
        }
    }
    else if(src_node->next && !tmp_node->next)
    {
        do
        {
            tmp_node->next = new typename OneLinkedList<T>::Node;
            tmp_node = tmp_node->next;
            src_node = src_node->next;
            tmp_node->value = src_node->value;
        }
        while(src_node->next);
        tmp_node->next = nullptr;
    }
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator =(Stack<T>&& other)
{
    this->head = other.head;
    other.head = nullptr;
    return *this;
}

// Stack methods //
//////////////////////////////////////////////

template <class T>
void Stack<T>::Print() const
{
    if (this->head)
    {
        typename OneLinkedList<T>::Node* ptr = this->head;
        for(; ptr->next; ptr = ptr->next)
        {
            std::cout << ptr->value << " ";
        }
        std::cout << ptr->value;
    };
}

template <class T>
void Stack<T>::Push(const T value)
{
    typename OneLinkedList<T>::Node* tmp;
    tmp = this->head;
    this->head = new typename OneLinkedList<T>::Node;
    this->head->value = value;
    this->head->next = tmp;
}

template <class T>
T Stack<T>::Pop()
{
    if(this->IsEmpty())
        throw std::length_error("There is no elements in stack.");
    T value = this->head->value;
    typename OneLinkedList<T>::Node* tmp;
    tmp = this->head->next;
    delete this->head;
    this->head = tmp;
    return value;
}

template <class T>
T Stack<T>::GetFront() const
{
    if(this->IsEmpty())
        throw std::length_error("There is no elements in stack.");
    return this->head->value;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return !this->head;
}

template <class T>
size_t Stack<T>::Size() const
{
    size_t i = 0;
    for(typename OneLinkedList<T>::Node* node = this->head;
            node;
            node = node->next, ++i);
    return i;
}

// Queue class //
//////////////////////////////////////////////

template <class T>
class Queue: public OneLinkedList<T>
{
public:
    Queue();
    ~Queue();
    Queue(const Queue& other);
    Queue(Queue&& other);
    Queue<T>& operator =(const Queue<T>& other);
    Queue<T>& operator =(Queue<T>&& other);

    void Push(const T);
    T Pop();
    T GetFront() const;
    bool IsEmpty() const;
    size_t Size() const;

protected:
    void Print() const;
    typename OneLinkedList<T>::Node *head, *tail;
};

// Queue constructors and operators //
//////////////////////////////////////////////

template <class T>
Queue<T>::Queue()
{
    this->head = nullptr;
    this->tail = nullptr;
}

template <class T>
Queue<T>::~Queue()
{
    while(!this->IsEmpty())
    {
        this->Pop();
    }
}

template <class T>
Queue<T>::Queue(const Queue& other)
{
    if(other.IsEmpty())
    {
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }

    this->head = new typename OneLinkedList<T>::Node;
    typename OneLinkedList<T>::Node* src_node = other.head;
    this->head->value = src_node->value;
    this->head->next = nullptr;

    typename OneLinkedList<T>::Node* tmp_node = this->head;
    for(;
            src_node->next;
            tmp_node = tmp_node->next, src_node = src_node->next)
    {
        tmp_node->next = new typename OneLinkedList<T>::Node;
        tmp_node = tmp_node->next;
        src_node = src_node->next;

        tmp_node->value = src_node->value;
        tmp_node->next = nullptr;
    }
    this->tail = tmp_node;
}

template <class T>
Queue<T>::Queue(Queue&& other)
{
    this->head = other.head;
    this->tail = other.tail;
    other.head = nullptr;
}

template <class T>
Queue<T>& Queue<T>::operator =(const Queue<T>& other)
{
    if(this == &other)
        return *this;

    if(other.IsEmpty())
    {
        while(!this->IsEmpty())
        {
            this->Pop();
        }
        return *this;
    }

    if(!this->head)
    {
        this->head = new typename OneLinkedList<T>::Node;
        this->head->value = other.head->value;
    }

    typename OneLinkedList<T>::Node* tmp_node = this->head;
    typename OneLinkedList<T>::Node* src_node = other.head;
    for(; src_node->next && tmp_node->next; src_node = src_node->next, tmp_node = tmp_node->next)
        tmp_node->value = src_node->value;
    tmp_node->value = src_node->value;
    this->tail = tmp_node;

    if(!src_node->next && tmp_node->next)
    {
        typename OneLinkedList<T>::Node* tmp_node2 = tmp_node->next;
        tmp_node->next = nullptr;
        while(tmp_node2)
        {
            tmp_node = tmp_node2->next;
            delete tmp_node2;
            tmp_node2 = tmp_node;
        }
    }
    else if(src_node->next && !tmp_node->next)
    {
        do
        {
            tmp_node->next = new typename OneLinkedList<T>::Node;
            tmp_node = tmp_node->next;
            src_node = src_node->next;
            tmp_node->value = src_node->value;
        }
        while(src_node->next);
        this->tail = tmp_node;
        tmp_node->next = nullptr;
    }
    return *this;
}

template <class T>
Queue<T>& Queue<T>::operator =(Queue<T>&& other)
{
    this->head = other.head;
    this->tail = other.tail;
    other.head = nullptr;
    *this;
}

// Queue methods //
//////////////////////////////////////////////

template <class T>
void Queue<T>::Push(const T value)
{
    if(this->head)
    {
        this->tail->next = new typename OneLinkedList<T>::Node;
        this->tail = this->tail->next;
    }
    else
    {
        this->head = new typename OneLinkedList<T>::Node;
        this->tail = this->head;
    }
    this->tail->value = value;
    this->tail->next = nullptr;
}

template <class T>
T Queue<T>::Pop()
{
    if(this->IsEmpty())
        throw std::length_error("There is no elements in stack.");

    T res = this->head->value;
    if(this->head == this->tail)
    {
        this->head = nullptr;
        this->tail = nullptr;
        return res;
    }

    typename OneLinkedList<T>::Node* tmp_ptr;
    tmp_ptr = this->head->next;
    delete this->head;
    this->head = tmp_ptr;
    return res;
}

template <class T>
T Queue<T>::GetFront() const
{
    if(this->IsEmpty())
        throw std::length_error("There is no elements in stack.");
    return this->head->value;
}

template <class T>
bool Queue<T>::IsEmpty() const
{
    return !this->head;
}

template <class T>
size_t Queue<T>::Size() const
{
    size_t i = 0;
    for(typename OneLinkedList<T>::Node* node = this->head;
            node;
            node = node->next, ++i);
    return i;
}

template <class T>
void Queue<T>::Print() const
{
    if (this->head)
    {
        typename OneLinkedList<T>::Node* ptr = this->head;
        for(; ptr->next; ptr = ptr->next)
        {
            std::cout << ptr->value << " ";
        }
        std::cout << ptr->value;
    };
}



#endif // QUEUE_STACK_H_INCLUDED
