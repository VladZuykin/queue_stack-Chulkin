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

    template<class F> friend std::istream& operator >>(std::istream& stream, OneLinkedList<F>& lst);
    template<class F> friend std::ostream& operator <<(std::ostream& stream, const OneLinkedList<F>& lst);

    class const_iterator;
    class iterator;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    class iterator
    {
    private:
        typename OneLinkedList<T>::Node *cur;
    public:
    iterator(typename OneLinkedList<T>::Node* cur = nullptr)
        {
            this->cur = cur;
        }
        ~iterator() {};

        T& operator  *() const
        {
            return cur->value;
        }
        T* operator ->() const
        {
            return &cur->value;
        }

        iterator& operator++()
        {
            this->cur = this->cur->next;    // Небезопасная
            return *this;
        }
        iterator operator++(int) // Небезопасная
        {
            iterator a = *this;
            ++*this;
            return a;
        }

        iterator operator +(unsigned n) const
        {
            if (n == 0)
                return *this;
            else if (n > 0)
            {
                iterator it2 = *this;
                for(unsigned int i= 0; i < n; ++i, ++it2);
                return it2;
            }
            else
            {
                throw(std::invalid_argument("Stack iterator: sum require positive num."));
            }
        }

        iterator& operator += (unsigned n)
        {
            return *this + n;
        }
        bool operator == (const iterator& it) const
        {
            return this->cur == it.cur;
        }
        bool operator != (const iterator& it) const
        {
            return this->cur != it.cur;
        }

        bool operator == (const const_iterator& it) const
        {
            return this->cur == it.cur;
        }

        bool operator != (const const_iterator& it) const
        {
            return this->cur != it.cur;
        }


        friend const_iterator;
    };
/////////////////////////////////////////////////////////
    class const_iterator
    {
    private:
        typename OneLinkedList<T>::Node *cur;
    public:

        const_iterator(typename OneLinkedList<T>::Node* cur = nullptr)
        {
            this->cur = cur;
        }
        ~const_iterator() {};

        const T& operator  *() const
        {
            return cur->value;
        }
        const T* operator ->() const
        {
            return &cur->value;
        }

        const_iterator& operator++()
        {
            this->cur = this->cur->next;    // Небезопасная
            return *this;
        }
        const_iterator operator++(int) // Небезопасная
        {
            const_iterator a = *this;
            ++*this;
            return a;
        }

        const_iterator operator +(unsigned n) const
        {
            if (n == 0)
                return *this;
            else if (n > 0)
            {
                const_iterator it2 = *this;
                for(unsigned int i= 0; i < n; ++i, ++it2);
                return it2;
            }
            else
            {
                throw(std::invalid_argument("Stack iterator: sum require positive num."));
            }
        }

        const_iterator& operator += (unsigned n)
        {
            return *this + n;
        }
        bool operator == (const const_iterator& it) const
        {
            return this->cur == it.cur;
        }
        bool operator != (const const_iterator& it) const
        {
            return this->cur != it.cur;
        }

        bool operator == (const iterator& it) const
        {
            return this->cur == it.cur;
        }

        bool operator != (const iterator& it) const
        {
            return this->cur != it.cur;
        }
    };

protected:
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
    if(lst.cbegin() != lst.end())
    {

        std::cout << *lst.cbegin();
        for(typename OneLinkedList<T>::const_iterator it = ++lst.cbegin(); it != lst.end();++it)
        {
            std::cout << " " << *it;
        }
    }
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

    void Clear();
    void Push(const T);
    T Pop();
    T GetFront() const;
    bool IsEmpty() const;
    size_t Size() const;
    Stack<T>& operator =(const Stack<T>& other);
    Stack<T>& operator =(Stack<T>&& other);
/////////////////////////////////////////////////
typedef typename OneLinkedList<T>::iterator iterator;
iterator begin()
    {
        return iterator(head);
    }
    iterator end()
    {
        return nullptr;
    }



/////////////////////////////////////////////////////////
        typedef typename OneLinkedList<T>::const_iterator const_iterator;

        const_iterator begin() const
        {
            return const_iterator(head);
        }
        const_iterator end() const
        {
            return nullptr;
        }

        const_iterator cbegin() const
        {
            return const_iterator(head);
        }
        const_iterator cend() const
        {
            return nullptr;
        }

protected:
    typename OneLinkedList<T>::Node *head;
private:
    void CopyFromOther(const Stack<T>& other);
};

// Stack constructors and operators //
//////////////////////////////////////////////

template <class T>
Stack<T>::Stack()
{
    head = nullptr;
}

template <class T>
void Stack<T>::Clear()
{
    while(!this->IsEmpty())
        {
            this->Pop();
        };
        this->head = nullptr;
}

template <class T>
Stack<T>::~Stack()
{
    this->Clear();
}

template <class T>
void Stack<T>::CopyFromOther(const Stack& other)
{
    if(other.IsEmpty())
    {
        this->head = nullptr;
        return;
    }

    this->head = new typename OneLinkedList<T>::Node;
    typename OneLinkedList<T>::Node* src_node = other.head;
    this->head->value = src_node->value;

    typename OneLinkedList<T>::Node* tmp_node = this->head;
    for(; src_node->next;)
    {
        tmp_node->next = new typename OneLinkedList<T>::Node;
        tmp_node = tmp_node->next;
        src_node = src_node->next;

        tmp_node->value = src_node->value;
    }
    tmp_node->next = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack& other)
{
    this->CopyFromOther(other);
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

    this->Clear();
    this->CopyFromOther(other);
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator =(Stack<T>&& other)
{
    this->Clear();
    this->head = other.head;
    other.head = nullptr;
    return *this;
}

// Stack methods //
//////////////////////////////////////////////

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
    for(typename OneLinkedList<T>::Node* node = this->head; node; node = node->next, ++i);
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

    void Clear();
    void Push(const T);
    T Pop();
    T GetFront() const;
    bool IsEmpty() const;
    size_t Size() const;

    typedef typename OneLinkedList<T>::iterator iterator;
    iterator begin()
    {
        return iterator(head);
    }
    iterator end()
    {
        return nullptr;
    }
/////////////////////////////////////////////////////////
    typedef typename OneLinkedList<T>::const_iterator const_iterator;
        const_iterator begin() const
        {
            return const_iterator(head);
        }
        const_iterator end() const
        {
            return nullptr;
        }

        const_iterator cbegin() const
        {
            return const_iterator(head);
        }
        const_iterator cend() const
        {
            return nullptr;
        }

protected:
    typename OneLinkedList<T>::Node *head, *tail;

private:
    void CopyFromOther(const Queue& other);
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
void Queue<T>::Clear()
{
    while(!this->IsEmpty())
        {
            this->Pop();
        }
        this->head = nullptr;
        this->tail = nullptr;
}

template <class T>
Queue<T>::~Queue()
{
    this->Clear();
}

template <class T>
void Queue<T>::CopyFromOther(const Queue& other)
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

    typename OneLinkedList<T>::Node* tmp_node = this->head;
    for(; src_node->next;)
    {
        tmp_node->next = new typename OneLinkedList<T>::Node;
        tmp_node = tmp_node->next;
        src_node = src_node->next;

        tmp_node->value = src_node->value;
    }
    tmp_node->next = nullptr;
    this->tail = tmp_node;
}

template <class T>
Queue<T>::Queue(const Queue& other)
{
    this->CopyFromOther(other);
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

    this->Clear();
    this->CopyFromOther(other);
    return *this;
}

template <class T>
Queue<T>& Queue<T>::operator =(Queue<T>&& other)
{
    this->Clear();
    this->head = other.head;
    this->tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    return *this;
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
        throw std::length_error("There is no elements in queue.");

    T res = this->head->value;
    if(this->head == this->tail)
    {
        delete this->head;
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
        throw std::length_error("There is no elements in queue.");
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


#endif // QUEUE_STACK_H_INCLUDED
