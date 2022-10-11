#include <iostream>
template <typename T, int N>
void Queue<T, N>::enqueue(T value){
    if (full()){
        throw queue_error{"Cannot enqueue to a full queue."};
    }
    data[tail % N] = value;
    tail++;
}

template <typename T, int N>
T Queue<T, N>::dequeue(){

    if (empty()){
        throw queue_error{"Cannot dequeue from an empty queue."};
    }
    T first = data[head % N];
    head++;
    return first;
}

template <typename T, int N>
bool Queue<T, N>::empty() const{
    return head == tail;
}

template <typename T, int N>
bool Queue<T, N>::full() const{
    return tail >= head + N;
}

template <typename T, int N>
void Queue<T, N>::clear(){
    head = tail = 0;
}

template <typename T, int N>
T const& Queue<T, N>::front() const{
    if (empty()){
        throw queue_error{"Queue is empty."};
    }
    return data[head % N];
}

template <typename T, int N>
template <int M>
Queue<T, N+M> Queue<T, N>::copy_and_expand(){
    Queue<T, N+M> new_q{};
    for (int i = head; i < tail; i++){
        new_q.enqueue(data[i % N]);
    }
    return new_q;
}