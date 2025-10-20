#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
struct Array {
    T* data;
    size_t capacity;
    size_t length;
};

template <typename T>
void array_init(Array<T>& arr, size_t cap = 100) {
    arr.capacity = cap;
    arr.length = 0;
    arr.data = new T[arr.capacity];
}

template <typename T>
void array_destroy(Array<T>& arr) {
    delete[] arr.data;
}

template <typename T>
void array_push_back(Array<T>& arr, const T& value) {
    if (arr.length >= arr.capacity) {
        throw overflow_error("Array is full");
    }
    arr.data[arr.length++] = value;
}

template <typename T>
void array_insert_at(Array<T>& arr, size_t index, const T& value) {
    if (index > arr.length || arr.length >= arr.capacity) {
        throw out_of_range("Index out of range or array is full");
    }
    for (size_t i = arr.length; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    ++arr.length;
}

template <typename T>
void array_remove_at(Array<T>& arr, size_t index) {
    if (index >= arr.length) {
        throw out_of_range("Index out of range");
    }
    for (size_t i = index; i < arr.length - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    --arr.length;
}

template <typename T>
void array_replace_at(Array<T>& arr, size_t index, const T& value) {
    if (index >= arr.length) {
        throw out_of_range("Index out of range");
    }
    arr.data[index] = value;
}

template <typename T>
T array_get_at(const Array<T>& arr, size_t index) {
    if (index >= arr.length) {
        throw out_of_range("Index out of range");
    }
    return arr.data[index];
}

template <typename T>
size_t array_size(const Array<T>& arr) {
    return arr.length;
}

template <typename T>
void array_load_from_file(Array<T>& arr, const std::string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        arr.length = 0;
        T value;
        while (file >> value) {
            if (arr.length >= arr.capacity) break;
            arr.data[arr.length++] = value;
        }
        file.close();
    }
}

template <typename T>
void array_save_to_file(const Array<T>& arr, const std::string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < arr.length; ++i) {
            file << arr.data[i] << " ";
        }
        file.close();
    }
}



#endif // ARRAY_H
