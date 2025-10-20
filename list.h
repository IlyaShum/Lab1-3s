#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
struct SListNode {
    T data;
    SListNode* next;
};

template<typename T>
struct SinglyLinkedList {
    SListNode<T>* head;
    size_t size;
};

template<typename T>
void slist_init(SinglyLinkedList<T>& list) {
    list.head = nullptr;
    list.size = 0;
}

template<typename T>
void slist_push_front(SinglyLinkedList<T>& list, const T& value) {
    SListNode<T>* new_node = new SListNode<T>{value, list.head};
    list.head = new_node;
    list.size++;
}

template<typename T>
void slist_push_back(SinglyLinkedList<T>& list, const T& value) {
    SListNode<T>* new_node = new SListNode<T>{value, nullptr};
    if (!list.head) {
        list.head = new_node;
    } else {
        SListNode<T>* current = list.head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    list.size++;
}

template<typename T>
void slist_pop_front(SinglyLinkedList<T>& list) {
    if (!list.head) throw out_of_range("List is empty");
    SListNode<T>* temp = list.head;
    list.head = list.head->next;
    delete temp;
    list.size--;
}

template<typename T>
void slist_pop_back(SinglyLinkedList<T>& list) {
    if (!list.head) throw out_of_range("List is empty");
    if (!list.head->next) {
        delete list.head;
        list.head = nullptr;
    } else {
        SListNode<T>* current = list.head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    list.size--;
}

template<typename T>
void slist_remove(SinglyLinkedList<T>& list, const T& value) {
    if (!list.head) return;

    if (list.head->data == value) {
        slist_pop_front(list);
        cout << "Removed " << value << " from the singly linked list.\n";
        return;
    }

    SListNode<T>* current = list.head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        SListNode<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
        list.size--;
        cout << "Removed " << value << " from the singly linked list.\n";
    } else {
        cout << "Element not found.\n";
    }
}

template<typename T>
SListNode<T>* slist_find(SinglyLinkedList<T>& list, const T& value) {
    SListNode<T>* current = list.head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void slist_print(const SinglyLinkedList<T>& list) {
    SListNode<T>* current = list.head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
size_t slist_get_size(const SinglyLinkedList<T>& list) {
    return list.size;
}

template<typename T>
void slist_load_from_file(SinglyLinkedList<T>& list, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        // Clear existing list
        while (list.head) {
            slist_pop_front(list);
        }
        
        T value;
        while (file >> value) {
            slist_push_back(list, value);
        }
        file.close();
    }
}

template<typename T>
void slist_save_to_file(const SinglyLinkedList<T>& list, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        SListNode<T>* current = list.head;
        while (current) {
            file << current->data << " ";
            current = current->next;
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file");
    }
}

#endif // SINGLY_LINKED_LIST_H
