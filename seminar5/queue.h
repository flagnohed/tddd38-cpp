#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdexcept>
class queue_error : std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

template <typename T, int N>
class Queue
{
public:
    static_assert(N>0, "A queue must have space for atleast 1 value.");
    void enqueue(T value);
    T dequeue();
    bool empty() const;
    bool full() const;
    void clear(); // make queue empty
    T const& front() const;

    template<int M>
    Queue<T, N+M> copy_and_expand();
private:
    T data[N]{};
    int head, tail = 0;
};




#include "queue.tcc"
#endif