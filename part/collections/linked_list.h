// (doubly) linked list implementation (cpp-style)
#pragma once

#define DEBUG_MODE false


// decl: Node
// struct의 경우, 접근제어자를 지정하지 않으면 public
template<typename T>
struct Node {
    T value;
    Node<T>* next_node;
    Node<T>* prev_node;

    Node();
    Node(const T& value);
    Node(const T& value, Node<T>* next_node, Node<T>* prev_node);
};


// impl: Node
template<typename T>
Node<T>::Node() : value(), next_node(nullptr), prev_node(nullptr) {}

template<typename T>
Node<T>::Node(const T& value) : value(value), next_node(nullptr), prev_node(nullptr) {}

template<typename T>
Node<T>::Node(const T& value, Node<T>* next_node, Node<T>* prev_node)
        : value(value), next_node(next_node), prev_node(prev_node) {};


// decl: LinkedList
// class의 경우, 접근제어자를 지정하지 않으면 private
template<typename T>
class LinkedList {
private:
    Node<T>* head_node;
    Node<T>* tail_node;
    int length;

public:
    LinkedList();
    ~LinkedList();

public:
    void add_first(const T& value);
    void add_last(const T& value);
    void print();

    class iterator;
    iterator begin();
    iterator end();

public:
    // decl: LinkedList::iterator
    class iterator {
    private:
        LinkedList<T>* list_ptr;
        Node<T>* target_node;
        bool is_valid = false;

    public:
        iterator();
        iterator(LinkedList<T>* list_ptr, Node<T>* target_node);

    private:
        void validate();

    public:
        T& operator*();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(iterator other);
        bool operator!=(iterator other);
    };
};


// impl: LinkedList
template<typename T>
LinkedList<T>::LinkedList() : head_node(nullptr), tail_node(nullptr), length(0) {}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current_node = head_node;

    for (int i = 0; i < length; ++i) {
        // 미리 다음 노드의 주소값을 가지고 있지 않으면, 현재 노드가 해제되면서 다음 노드의 위치를 알 수 없게 됨
        Node<T>* next_node = current_node->next_node;
        if (DEBUG_MODE) {
            printf("memory freeing...(node=%p)\n", current_node);
        }
        delete current_node;
        current_node = next_node;
    }

    head_node = nullptr;
    tail_node = nullptr;
    length = 0;
}

template<typename T>
void LinkedList<T>::add_first(const T& value) {
    Node<T>* new_node = new Node<T>(value, head_node, tail_node);

    if (DEBUG_MODE) {
        std::cout << "generate first_node from " << tail_node << " to " << new_node << std::endl;
    }

    if (nullptr == tail_node) {
        tail_node = new_node;
    }

    head_node = new_node;
    ++length;
}

template<typename T>
void LinkedList<T>::add_last(const T& value) {
    Node<T>* new_node = new Node<T>(value, head_node, tail_node);

    if (DEBUG_MODE) {
        std::cout << "generate last_node from " << tail_node << " to " << new_node << std::endl;
    }

    if (nullptr == head_node) {
        head_node = new_node;
    } else {
        tail_node->next_node = new_node;
    }

    tail_node = new_node;
    ++length;
}

template<typename T>
void LinkedList<T>::print()
{
    std::cout << "LinkedList(length=" << length << ", head_node=" << head_node << ", tail_node=" << tail_node << ") [ ";
    Node<T> current_node = *head_node;
    for (int i = 0; i < length; ++i) {
        std::cout << current_node.value << " ";
        current_node = *current_node.next_node;
    }
    std::cout << "]" << std::endl;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin()
{
    return LinkedList::iterator(this, head_node);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return LinkedList::iterator(this, nullptr);
}


// impl: LinkedList::iterator
template<typename T>
LinkedList<T>::iterator::iterator() : list_ptr(nullptr), target_node(nullptr)
{
    validate();
}

template<typename T>
LinkedList<T>::iterator::iterator(LinkedList<T>* list_ptr, Node<T>* target_node)
    : list_ptr(list_ptr), target_node(target_node)
{
    validate();
}

template<typename T>
void LinkedList<T>::iterator::validate()
{
    if (nullptr != list_ptr || nullptr != target_node) {
        is_valid = true;
    } else {
        is_valid = false;
    }

}

template<typename T>
T& LinkedList<T>::iterator::operator*()
{
    if (!is_valid) {
        assert(nullptr);
    }
    return target_node->value;
}

template<typename T>
bool LinkedList<T>::iterator::operator==(LinkedList::iterator other)
{
    return (list_ptr == other.list_ptr) && (target_node == other.target_node);
}

template<typename T>
bool LinkedList<T>::iterator::operator!=(LinkedList::iterator other)
{
    return !(*this == other);
}

template<typename T>
typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++()
{
    if (nullptr == target_node || !is_valid) {
        assert(nullptr);
    } else if (target_node == list_ptr->tail_node) {
        target_node = nullptr;
    } else {
        target_node = target_node->next_node;
    }
    return *this;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int) {
    iterator copy = iterator(list_ptr, target_node);
    ++(*this);
    return copy;
}

template<typename T>
typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator--()
{
    if (target_node == list_ptr->head_node) {
        target_node = nullptr;
    } else {
        target_node = target_node->prev_node;
    }
    return *this;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator--(int) {
    iterator copy = iterator(list_ptr, target_node);
    --(*this);
    return copy;
}
