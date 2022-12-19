#include <stdexcept>
#include <iostream>

//todo: fix memory leak

template<typename T, int chunk_size>
void deque<T, chunk_size>::push_back(T value){
    if (end_index == capacity) {
        add_chunk_after();
    }

    storage[end_index] = value;
    item_counter++;
    if (item_counter == 1) {
        start_index--;
    }
    end_index++;

}

template<typename T, int chunk_size>
void deque<T, chunk_size>::add_chunk_after(){
    reallocate_array(0);
}

template<typename T, int chunk_size>
void deque<T, chunk_size>::push_front(T value){
    if (start_index == -1) {
        add_chunk_before();
    }

    storage[start_index] = value;
    item_counter++;
    if (item_counter == 1) {
        end_index++;
    }
    start_index--;
    
}

template<typename T, int chunk_size>
void deque<T, chunk_size>::add_chunk_before() {
    start_index += capacity;  // sets to capacity - 1, BEFORE capacity doubles.
    end_index += capacity;
    reallocate_array(capacity);
    
}

template<typename T, int chunk_size>
void deque<T, chunk_size>::reallocate_array(int start_i) {
    T* new_array {new T[2 * capacity] {}};
    // jag tror det här är shallow copy, måste vara deep
    
    for (int i{start_i}; i < start_i + capacity; i++){
        new_array[i] = storage[i % capacity];
    }
    // std::copy(storage, storage + item_counter/chunk_size, new_array);
    capacity *= 2;
    //sannolikt memory leak här
    //delete[] storage;
    // storage = nullptr;
    storage = new_array;
    
}

template<typename T, int chunk_size>
void deque<T, chunk_size>::pop_back(){
    if (!item_counter) {
        throw std::out_of_range("Deque is empty!");
    } else {
        item_counter--;
        end_index--;
    }   
}

template<typename T, int chunk_size>
void deque<T, chunk_size>::pop_front(){
    if (!item_counter) {
        throw std::out_of_range("Deque is empty!");
    } else {
        item_counter--;
        start_index++;
    }
}

template<typename T, int chunk_size>
T& deque<T, chunk_size>::at(int index) {
    if (index >= item_counter) {
        throw std::out_of_range("Out of range!");
    } else {
        // start_index + 1 is the first element
        return storage[start_index + 1 + index];
    }
}

template<typename T, int chunk_size>
T const& deque<T, chunk_size>::at(int index) const{ 
    if (index >= item_counter) {
        throw std::out_of_range("Out of range!");
    } else {
        // start_index + 1 is the first element
        return storage[start_index + 1 + index];
    }
}

template<typename T, int chunk_size>
T& deque<T, chunk_size>::operator[](int index) {
    if (index >= item_counter) {
        throw std::out_of_range("Out of range!");
    } else {
        
        return at(index);
    }
}

template<typename T, int chunk_size>
T const& deque<T, chunk_size>::operator[](int index) const{
    if (index >= item_counter) {
        throw std::out_of_range("Out of range!");
    } else {
       
        return at(index);
    }
}

template<typename T, int chunk_size>
int deque<T, chunk_size>::size() const{
    return item_counter;
}
