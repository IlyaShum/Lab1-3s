#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
struct StackNode {
    T data;
    StackNode* next;
};

template<typename T>
struct Stack {
    StackNode<T>* head;
    size_t size;
    size_t capacity;
};

template<typename T>
void stack_init(Stack<T>& s, size_t capacity = 100) {
    s.head = nullptr;
    s.size = 0;
    s.capacity = capacity;
}

template<typename T>
void stack_push(Stack<T>& s, const T& value) {
    if (s.size >= s.capacity) {
        cerr << "Stack is full, cannot push new value: " << value << endl;
        return;
    }
    StackNode<T>* new_node = new StackNode<T>{value, s.head};
    s.head = new_node;
    s.size++;
}

template<typename T>
void stack_pop(Stack<T>& s) {
    if (!s.head) throw out_of_range("Stack is empty");
    StackNode<T>* temp = s.head;
    s.head = s.head->next;
    delete temp;
    s.size--;
}

template<typename T>
T stack_head_value(const Stack<T>& s) {
    if (!s.head) throw out_of_range("Stack is empty");
    return s.head->data;
}

template<typename T>
size_t stack_get_size(const Stack<T>& s) {
    return s.size;
}

template<typename T>
void stack_print(const Stack<T>& s) {
    StackNode<T>* current = s.head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
void stack_load_from_file(Stack<T>& s, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        // Очищаем текущий стек
        while (s.head) {
            stack_pop(s);
        }
        
        // Читаем все элементы из файла в вектор
        vector<T> elements;
        T value;
        while (file >> value) {
            elements.push_back(value);
        }
        file.close();

        // Добавляем элементы в стек в обратном порядке
        // чтобы первый элемент файла стал дном стека
        for (int i = elements.size() - 1; i >= 0; i--) {
            if (s.size < s.capacity) {
                stack_push(s, elements[i]);
            }
        }
    } else {
        throw runtime_error("Unable to open file for loading");
    }
}

template<typename T>
void stack_save_to_file(const Stack<T>& s, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Сохраняем стек в правильном порядке (вершина первая)
        StackNode<T>* current = s.head;
        while (current) {
            file << current->data << " ";
            current = current->next;
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file for saving");
    }
}

#endif // STACK_H
