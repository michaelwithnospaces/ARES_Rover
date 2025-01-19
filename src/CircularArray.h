#include <iostream>

using std::cout, std::endl;

template <typename T>
class CircularArray {
public:
    int capacity; // capacity of array

    CircularArray(int capacity) {
        this->capacity = capacity;
        this->arr = new T[capacity];
        this->start = 0;
        this->size = 0;
    }

    ~CircularArray() {
        delete[] this->arr;
    }

    void push(T element) {
        if (this->size < this->capacity) {
            int index = (this->start + this->size) % this->capacity;
            this->arr[index] = element;
            this->size += 1;
        } else {
            this->arr[this->start] = element;
            this->start = (this->start + 1 + this->capacity) % this->capacity;
        }
    } // 0 oldest, last newe

    T pop() {
        if (this->size == 0) {
            throw "can't";
        }

        T el = this->arr[this->start];
        this->size -= 1;
        this->start = (this->start + 1) % this->capacity;
        return el;
    }

    T& operator[](const int i) {
        int j = (i + this->start) % this->capacity;
        return this->arr[j];
    }

    const T& operator[](const int i) const {
        int j = (i + this->start) % this->capacity;
        return this->arr[j];
    }

    
    int start;
    int size;

private:
    T* arr;

};
