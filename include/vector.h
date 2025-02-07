#pragma once
#include <cctype>
#include <stdexcept>

template <typename T>
class TVector {
 private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

 public:
    TVector(size_t initCapacity = 10) : size(0), capacity(initCapacity) {
        data = new T[capacity];
    }

    ~TVector() { delete[] data; }

    void push_back(const T& value) {
        if (size == capacity)
            resize(capacity * 2);
        data[size++] = value;
    }

    T pop_back() {
        if (size == 0) throw std::runtime_error("Vector is empty");
        size--;
        return data[size];
    }

    T& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& operator[](size_t index) {
        return at(index);
    }

    T& back() {
        if (size == 0) throw std::runtime_error("Vector is empty");
        return data[size - 1];
    }

    size_t get_size() const { return size; }

    bool empty() const { return size == 0; }

    void clear() {
        size = 0;
        resize(10);
    }
};
