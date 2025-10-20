#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
struct DListNode {
    T data;
    DListNode* next;
    DListNode* prev;
};

template<typename T>
struct DoublyLinkedList {
    DListNode<T>* head;
    DListNode<T>* tail;
    size_t size;
};

template<typename T>
void dlist_init(DoublyLinkedList<T>& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

template<typename T>
void dlist_push_front(DoublyLinkedList<T>& list, const T& value) {
    DListNode<T>* new_node = new DListNode<T>{value, nullptr, nullptr};
    if (!list.head) {
        list.head = list.tail = new_node;
    } else {
        new_node->next = list.head;
        list.head->prev = new_node;
        list.head = new_node;
    }
    list.size++;
}

template<typename T>
void dlist_push_back(DoublyLinkedList<T>& list, const T& value) {
    DListNode<T>* new_node = new DListNode<T>{value, nullptr, nullptr};
    if (!list.head) {
        list.head = list.tail = new_node;
    } else {
        list.tail->next = new_node;
        new_node->prev = list.tail;
        list.tail = new_node;
    }
    list.size++;
}

template<typename T>
void dlist_pop_front(DoublyLinkedList<T>& list) {
    if (!list.head) throw out_of_range("List is empty");
    DListNode<T>* temp = list.head;
    list.head = list.head->next;
    if (list.head) list.head->prev = nullptr;
    else list.tail = nullptr;
    delete temp;
    list.size--;
}

template<typename T>
void dlist_pop_back(DoublyLinkedList<T>& list) {
    if (!list.tail) throw out_of_range("List is empty");
    DListNode<T>* temp = list.tail;
    list.tail = list.tail->prev;
    if (list.tail) list.tail->next = nullptr;
    else list.head = nullptr;
    delete temp;
    list.size--;
}

template<typename T>
void dlist_remove(DoublyLinkedList<T>& list, const T& value) {
    DListNode<T>* current = list.head;
    while (current) {
        if (current->data == value) {
            if (current == list.head) {
                dlist_pop_front(list);
            } else if (current == list.tail) {
                dlist_pop_back(list);
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                list.size--;
            }
            cout << "Removed " << value << " from the doubly linked list.\n";
            return;
        }
        current = current->next;
    }
    cout << "Element not found.\n";
}

template<typename T>
DListNode<T>* dlist_find(DoublyLinkedList<T>& list, const T& value) {
    DListNode<T>* current = list.head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void dlist_print(const DoublyLinkedList<T>& list) {
    DListNode<T>* current = list.head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
size_t dlist_get_size(const DoublyLinkedList<T>& list) {
    return list.size;
}

template<typename T>
void dlist_load_from_file(DoublyLinkedList<T>& list, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        // Clear existing list
        while (list.head) {
            dlist_pop_front(list);
        }
        
        T value;
        while (file >> value) {
            dlist_push_back(list, value);
        }
        file.close();
    }
}

template<typename T>
void dlist_save_to_file(const DoublyLinkedList<T>& list, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        DListNode<T>* current = list.head;
        while (current) {
            file << current->data << " ";
            current = current->next;
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file");
    }
}

#endif // DOUBLY_LINKED_LIST_H
