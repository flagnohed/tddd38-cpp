#ifndef DEQUE_H_
#define DEQUE_H_

template<typename T, int chunk_size>
class deque {
public:
    deque() =default;
    ~deque() =default;
    deque(deque& d) =default;
    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
    int size() const;
    T& at(int index);
    T const& at(int index) const;
    T& operator[](int index);
    T const& operator[](int index) const;
    
    
private:
    int capacity{chunk_size};
    int start_index{}; // första lediga platsen till vänster. om -1 --> ny chunk till vänster
    int end_index{}; // första lediga platsen till höger. om capacity --> ny chunk till höger
    int item_counter{};
    T* storage = new T[chunk_size] {};
    void add_chunk_before();
    void add_chunk_after();
    void reallocate_array(int start_i);
   
};


#include "deque.tcc"
#endif