#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array.h"
#include "list.h"
#include "twolist.h"
#include "queue.h"
#include "stack.h"
#include "fullbinarytree.h"

using namespace std;

void execute_query(const string& query, Array<string>& array, SinglyLinkedList<string>& singly_list, 
                  DoublyLinkedList<string>& doubly_list, Queue<string>& queue, Stack<string>& stack, 
                  FullBinaryTree<int>& tree, string& filename) {
    istringstream iss(query);
    string command;
    iss >> command;

    if (command == "MPUSH") {
        array_load_from_file(array, filename);
        string value;
        iss >> value;
        array_push_back(array, value);
        array_save_to_file(array, filename);
        cout << "Added " << value << " to the array.\n";
    } else if (command == "MINSERT") {
        array_load_from_file(array, filename);
        string value;
        size_t index;
        iss >> index >> value;
        try {
            array_insert_at(array, index, value);
            array_save_to_file(array, filename);
            cout << "Inserted " << value << " at index " << index << " in the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MDEL") {
        array_load_from_file(array, filename);
        size_t index;
        iss >> index;
        try {
            array_remove_at(array, index);
            array_save_to_file(array, filename);
            cout << "Removed element at index " << index << " from the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MREPLACE") {
        array_load_from_file(array, filename);
        size_t index;
        string value;
        iss >> index >> value;
        try {
            array_replace_at(array, index, value);
            array_save_to_file(array, filename);
            cout << "Replaced element at index " << index << " with " << value << " in the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MGET") {
        array_load_from_file(array, filename);
        size_t index;
        iss >> index;
        try {
            string value = array_get_at(array, index);
            cout << "Element at index " << index << " in the array: " << value << "\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MLENGTH") {
        array_load_from_file(array, filename);
        cout << "Array length: " << array_size(array) << "\n";
    } else if (command == "LPUSH_HEAD") {
        slist_load_from_file(singly_list, filename);
        string value;
        iss >> value;
        slist_push_front(singly_list, value);
        slist_save_to_file(singly_list, filename);
        cout << "Added " << value << " to the front of the singly linked list.\n";
    } else if (command == "LPUSH_TAIL") {
        slist_load_from_file(singly_list, filename);
        string value;
        iss >> value;
        slist_push_back(singly_list, value);
        slist_save_to_file(singly_list, filename);
        cout << "Added " << value << " to the back of the singly linked list.\n";
    } else if (command == "LPOP_HEAD") {
        slist_load_from_file(singly_list, filename);
        try {
            slist_pop_front(singly_list);
            slist_save_to_file(singly_list, filename);
            cout << "Removed the front element from the singly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "LPOP_TAIL") {
        slist_load_from_file(singly_list, filename);
        try {
            slist_pop_back(singly_list);
            slist_save_to_file(singly_list, filename);
            cout << "Removed the back element from the singly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "LREMOVE") {
        slist_load_from_file(singly_list, filename);
        string value;
        iss >> value;
        slist_remove(singly_list, value);
        slist_save_to_file(singly_list, filename);
    } else if (command == "LFIND") {
        slist_load_from_file(singly_list, filename);
        string value;
        iss >> value;
        auto node = slist_find(singly_list, value);
        if (node) {
            cout << "Found: " << node->data << " in singly linked list.\n";
        } else {
            cout << "Not found in singly linked list.\n";
        }
    } else if (command == "LPRINT") {
        slist_load_from_file(singly_list, filename);
        slist_print(singly_list);
    } else if (command == "LGET_SIZE") {
        slist_load_from_file(singly_list, filename);
        cout << "Singly linked list size: " << slist_get_size(singly_list) << "\n";
    } else if (command == "L2PUSH_HEAD") {
        dlist_load_from_file(doubly_list, filename);
        string value;
        iss >> value;
        dlist_push_front(doubly_list, value);
        dlist_save_to_file(doubly_list, filename);
        cout << "Added " << value << " to the front of the doubly linked list.\n";
    } else if (command == "L2PUSH_TAIL") {
        dlist_load_from_file(doubly_list, filename);
        string value;
        iss >> value;
        dlist_push_back(doubly_list, value);
        dlist_save_to_file(doubly_list, filename);
        cout << "Added " << value << " to the back of the doubly linked list.\n";
    } else if (command == "L2POP_HEAD") {
        dlist_load_from_file(doubly_list, filename);
        try {
            dlist_pop_front(doubly_list);
            dlist_save_to_file(doubly_list, filename);
            cout << "Removed the front element from the doubly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "L2POP_TAIL") {
        dlist_load_from_file(doubly_list, filename);
        try {
            dlist_pop_back(doubly_list);
            dlist_save_to_file(doubly_list, filename);
            cout << "Removed the back element from the doubly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "L2REMOVE") {
        dlist_load_from_file(doubly_list, filename);
        string value;
        iss >> value;
        dlist_remove(doubly_list, value);
        dlist_save_to_file(doubly_list, filename);
    } else if (command == "L2FIND") {
        dlist_load_from_file(doubly_list, filename);
        string value;
        iss >> value;
        auto node = dlist_find(doubly_list, value);
        if (node) {
            cout << "Found: " << node->data << " in doubly linked list.\n";
        } else {
            cout << "Not found in doubly linked list.\n";
        }
    } else if (command == "L2PRINT") {
        dlist_load_from_file(doubly_list, filename);
        dlist_print(doubly_list);
    } else if (command == "L2GET_SIZE") {
        dlist_load_from_file(doubly_list, filename);
        cout << "Doubly linked list size: " << dlist_get_size(doubly_list) << "\n";
    } else if (command == "QPUSH") {
        queue_load_from_file(queue, filename);
        string value;
        iss >> value;
        queue_push(queue, value);
        queue_save_to_file(queue, filename);
        cout << "Added " << value << " to the queue.\n";
    } else if (command == "QPOP") {
        queue_load_from_file(queue, filename);
        try {
            queue_pop(queue);
            queue_save_to_file(queue, filename);
            cout << "Removed the front element from the queue.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "QFRONT") {
        queue_load_from_file(queue, filename);
        try {
            cout << "Front of queue: " << queue_front_value(queue) << "\n";
            queue_save_to_file(queue, filename);
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "QPRINT") {
        queue_load_from_file(queue, filename);
        queue_print(queue);
    } else if (command == "QGET_SIZE") {
        queue_load_from_file(queue, filename);
        cout << "Queue size: " << queue_get_size(queue) << "\n";
    } else if (command == "SPUSH") {
        stack_load_from_file(stack, filename);
        string value;
        iss >> value;
        stack_push(stack, value);
        stack_save_to_file(stack, filename);
        cout << "Added " << value << " to the stack.\n";
    } else if (command == "SPOP") {
        stack_load_from_file(stack, filename);
        try {
            stack_pop(stack);
            stack_save_to_file(stack, filename);
            cout << "Removed the top element from the stack.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "SHEAD") {
        stack_load_from_file(stack, filename);
        try {
            cout << "Top of stack: " << stack_head_value(stack) << "\n";
            stack_save_to_file(stack, filename);
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "SPRINT") {
        stack_load_from_file(stack, filename);
        stack_print(stack);
    } else if (command == "SGET_SIZE") {
        stack_load_from_file(stack, filename);
        cout << "Stack size: " << stack_get_size(stack) << "\n";
    } else if (command == "TPUSH") {
        full_tree_load_from_file(tree, filename);
        int value;
        iss >> value;
        full_tree_add(tree, value);
        full_tree_save_to_file(tree, filename);
        cout << "Added: " << value << endl;
    } else if (command == "TFIND") {
        full_tree_load_from_file(tree, filename);
        int value;
        iss >> value;
        bool found = full_tree_find(tree, value);
        cout << "Element " << value << (found ? " found" : " not found") << endl;
    } else if (command == "TFULL") {
        full_tree_load_from_file(tree, filename);
        bool is_full = full_tree_is_full(tree);
        cout << "Tree is " << (is_full ? "full binary tree." : "not full binary tree.") << endl;
    } else if (command == "TPRINT") {
        full_tree_load_from_file(tree, filename);
        full_tree_print(tree);
    } else {
        cerr << "Unknown command: " << command << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./dbms --file <file.data> --query '<command>'\n";
        return 1;
    }

    Array<string> array;
    array_init(array);
    
    SinglyLinkedList<string> singly_list;
    slist_init(singly_list);
    
    DoublyLinkedList<string> doubly_list;
    dlist_init(doubly_list);
    
    Queue<string> queue;
    queue_init(queue);
    
    Stack<string> stack;
    stack_init(stack);
    
    FullBinaryTree<int> tree;
    full_tree_init(tree);

    string filename;
    string query;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    execute_query(query, array, singly_list, doubly_list, queue, stack, tree, filename);

    return 0;
}
