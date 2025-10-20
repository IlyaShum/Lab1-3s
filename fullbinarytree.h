#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Реализация очереди на основе связного списка (для внутреннего использования в дереве)
template<typename T>
struct FullTreeQueueNode {
    T data;
    FullTreeQueueNode* next;
};

template<typename T>
struct FullTreeQueue {
    FullTreeQueueNode<T>* front_node;
    FullTreeQueueNode<T>* back_node;
    size_t size;
};

template<typename T>
void full_tree_queue_init(FullTreeQueue<T>& queue) {
    queue.front_node = nullptr;
    queue.back_node = nullptr;
    queue.size = 0;
}

template<typename T>
void full_tree_queue_push(FullTreeQueue<T>& queue, const T& value) {
    FullTreeQueueNode<T>* new_node = new FullTreeQueueNode<T>{value, nullptr};
    if (!queue.back_node) {
        queue.front_node = queue.back_node = new_node;
    } else {
        queue.back_node->next = new_node;
        queue.back_node = new_node;
    }
    queue.size++;
}

template<typename T>
void full_tree_queue_pop(FullTreeQueue<T>& queue) {
    if (queue.size == 0) throw out_of_range("Queue is empty");
    FullTreeQueueNode<T>* temp = queue.front_node;
    queue.front_node = queue.front_node->next;
    if (!queue.front_node) queue.back_node = nullptr;
    delete temp;
    queue.size--;
}

template<typename T>
T& full_tree_queue_front(FullTreeQueue<T>& queue) {
    if (queue.size == 0) throw out_of_range("Queue is empty");
    return queue.front_node->data;
}

template<typename T>
bool full_tree_queue_is_empty(const FullTreeQueue<T>& queue) {
    return queue.size == 0;
}

// Реализация полного бинарного дерева
template<typename T>
struct FullTreeNode {
    T data;
    FullTreeNode* left;
    FullTreeNode* right;
};

template<typename T>
struct FullBinaryTree {
    FullTreeNode<T>* root;
    size_t size;
};

template<typename T>
void full_tree_init(FullBinaryTree<T>& tree) {
    tree.root = nullptr;
    tree.size = 0;
}

template<typename T>
FullTreeNode<T>* create_full_tree_node(const T& value) {
    FullTreeNode<T>* new_node = new FullTreeNode<T>{value, nullptr, nullptr};
    return new_node;
}

template<typename T>
void full_tree_add_node(FullBinaryTree<T>& tree, FullTreeNode<T>* new_node) {
    if (!tree.root) {
        tree.root = new_node;
        return;
    }

    FullTreeQueue<FullTreeNode<T>*> queue;
    full_tree_queue_init(queue);
    full_tree_queue_push(queue, tree.root);

    while (!full_tree_queue_is_empty(queue)) {
        FullTreeNode<T>* current = full_tree_queue_front(queue);
        full_tree_queue_pop(queue);

        if (!current->left) {
            current->left = new_node;
            return;
        } else {
            full_tree_queue_push(queue, current->left);
        }

        if (!current->right) {
            current->right = new_node;
            return;
        } else {
            full_tree_queue_push(queue, current->right);
        }
    }
}

template<typename T>
void full_tree_add(FullBinaryTree<T>& tree, const T& value) {
    FullTreeNode<T>* new_node = create_full_tree_node(value);
    if (!tree.root) {
        tree.root = new_node;
    } else {
        full_tree_add_node(tree, new_node);
    }
    tree.size++;
}

template<typename T>
bool full_tree_find_node(FullTreeNode<T>* node, const T& value) {
    if (!node) return false;
    if (node->data == value) return true;
    return full_tree_find_node(node->left, value) || full_tree_find_node(node->right, value);
}

template<typename T>
bool full_tree_find(const FullBinaryTree<T>& tree, const T& value) {
    return full_tree_find_node(tree.root, value);
}

template<typename T>
void full_tree_clear_node(FullTreeNode<T>* node) {
    if (!node) return;
    full_tree_clear_node(node->left);
    full_tree_clear_node(node->right);
    delete node;
}

template<typename T>
void full_tree_clear(FullBinaryTree<T>& tree) {
    full_tree_clear_node(tree.root);
    tree.root = nullptr;
    tree.size = 0;
}

// Функция проверки является ли дерево полным бинарным деревом
template<typename T>
bool full_tree_is_full_node(FullTreeNode<T>* node) {
    if (!node) return true;
    
    // Если у узла нет детей - это лист, всё ок
    if (!node->left && !node->right) return true;
    
    // Если у узла оба ребенка - проверяем рекурсивно оба поддерева
    if (node->left && node->right) {
        return full_tree_is_full_node(node->left) && full_tree_is_full_node(node->right);
    }
    
    // Если только один ребенок - дерево не полное
    return false;
}

template<typename T>
bool full_tree_is_full(const FullBinaryTree<T>& tree) {
    return full_tree_is_full_node(tree.root);
}

template<typename T>
void full_tree_print(const FullBinaryTree<T>& tree) {
    if (!tree.root) return;

    FullTreeQueue<FullTreeNode<T>*> queue;
    full_tree_queue_init(queue);
    full_tree_queue_push(queue, tree.root);

    while (!full_tree_queue_is_empty(queue)) {
        FullTreeNode<T>* current = full_tree_queue_front(queue);
        full_tree_queue_pop(queue);
        cout << current->data << " ";

        if (current->left) full_tree_queue_push(queue, current->left);
        if (current->right) full_tree_queue_push(queue, current->right);
    }
    cout << endl;
}

template<typename T>
void full_tree_load_from_file(FullBinaryTree<T>& tree, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        full_tree_clear(tree);
        T value;
        while (file >> value) {
            full_tree_add(tree, value);
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file for loading");
    }
}

template<typename T>
void full_tree_save_to_file(const FullBinaryTree<T>& tree, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        if (!tree.root) {
            file.close();
            return;
        }

        FullTreeQueue<FullTreeNode<T>*> queue;
        full_tree_queue_init(queue);
        full_tree_queue_push(queue, tree.root);

        while (!full_tree_queue_is_empty(queue)) {
            FullTreeNode<T>* current = full_tree_queue_front(queue);
            full_tree_queue_pop(queue);
            file << current->data << " ";

            if (current->left) full_tree_queue_push(queue, current->left);
            if (current->right) full_tree_queue_push(queue, current->right);
        }
        file.close();
    } else {
        throw runtime_error("Unable to open file for saving");
    }
}

#endif // FULL_BINARY_TREE_H
