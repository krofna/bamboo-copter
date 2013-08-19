#ifndef STACK_HPP
#define STACK_HPP

template <class T>
class Stack
{
public:
    Stack(size_t Size);
    ~Stack();

    void Push(T pWhat);
    void Pop();
    T Top();

private:
    size_t Curr;
    T* pData;
};

template <class T>
Stack<T>::Stack(size_t Size) :
Curr(0),
pData(new T[Size])
{
}

template <class T>
Stack<T>::~Stack()
{
    delete[] pData;
}

template <class T>
void Stack<T>::Push(T pWhat)
{
    pData[Curr++] = pWhat;
}

template <class T>
void Stack<T>::Pop()
{
    --Curr;
}

template <class T>
T Stack<T>::Top()
{
    return pData[Curr - 1];
}

#endif
