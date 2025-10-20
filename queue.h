#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
struct QueueNode {
    T data;
    QueueNode* next;
};

template<typename T>
struct Queue {
    QueueNode<T>* front;
    QueueNode<T>* rear;
    size_t size;
};

template<typename T>
void queue_init(Queue<T>& q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.size = 0;
}

template<typename T>
void queue_push(Queue<T>& q, const T& value) {
    QueueNode<T>* new_node = new QueueNode<T>{value, nullptr};
    if (!q.rear) {
        q.front = q.rear = new_node;
    } else {
        q.rear->next = new_node;
        q.rear = new_node;
    }
    q.size++;
}

template<typename T>
void queue_pop(Queue<T>& q) {
    if (!q.front) throw out_of_range("Queue is empty");
    QueueNode<T>* temp = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete temp;
    q.size--;
}

template<typename T>
T queue_front_value(const Queue<T>& q) {
    if (!q.front) throw out_of_range("Queue is empty");
    return q.front->data;
}

template<typename T>
size_t queue_get_size(const Queue<T>& q) {
    return q.size;
}

template<typename T>
void queue_print(const Queue<T>& q) {
    QueueNode<T>* current = q.front;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
void queue_load_from_file(Queue<T>& q, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        // Clear existing queue
        while (q.front) {
            queue_pop(q);
        }
        
        T value;
        while (file >> value) {
            queue_push(q, value);
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file for loading");
    }
}

template<typename T>
void queue_save_to_file(const Queue<T>& q, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        QueueNode<T>* current = q.front;
        while (current) {
            file << current->data << " ";
            current = current->next;
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file for saving");
    }
}

#endif // QUEUE_H
