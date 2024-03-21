#include <iostream>
#include <list>
#include "linked_list.h"


using std::cout;
using std::endl;


// struct
struct node {
    int value;
    node* next_node;
};

struct linked_list {
    node* primary_node;
    int length;
};


// functions
void init(linked_list *obj) {
    obj->length = 0;
    obj->primary_node = nullptr;
}

void release(linked_list *obj) {
    node *current_node = obj->primary_node;

    while (current_node) {
        // 미리 다음 노드의 주소값을 가지고 있지 않으면, 현재 노드가 해제되면서 다음 노드의 위치를 알 수 없게 됨
        node *next_node = current_node->next_node;
        printf("memory freeing...(node=%p)\n", current_node);
        free(current_node);
        current_node = next_node;
    }

    init(obj);
}

void add(linked_list *obj, int value) {
    // new node
    node *new_node = (node*) malloc(sizeof(node));
    new_node->value = value;
    new_node->next_node = nullptr;

    // primary_node not defined
    if (nullptr == obj->primary_node) {
        printf("generate primary_node to %p\n", new_node);
        obj->primary_node = new_node;

    // primary_node defined
    } else {
        node *current_node = obj->primary_node;
        while (current_node->next_node) {
            current_node = current_node->next_node;
        }
        printf("generate next_node from %p to %p\n", current_node, new_node);
        current_node->next_node = new_node;
    }

    ++obj->length;
}

// main
int test_linked_list() {
    // c-style
    {
        linked_list list = {};
        init(&list);

        for (int outter_private = 0; outter_private < 4; ++outter_private) {
            add(&list, (int) (random() % 100L));
        }

        release(&list);
    }

    // cpp-style
    {
        LinkedList<int> list = LinkedList<int>();
        for (int i = 0; i < 4; ++i) {
            list.add_first((int) (random() % 100L));
        }
        for (int i = 0; i < 4; ++i) {
            list.add_last((int) (random() % 100L));
        }
        list.print();

        LinkedList<int>::iterator iter = list.begin();
        for (; iter != list.end(); ++iter) {
            cout << *iter << endl;
        }

        list.print();
        iter = list.begin();
        cout << *iter << endl;
        cout << *(++iter) << endl;
        cout << *(iter++) << endl;
        cout << *iter << endl;
    }

    // STL (Standard Template Library)
    {
        using std::list;
        using size = std::size_t;

        list<int> intList1 = list<int>();

        for (int outter_private = 0; outter_private < 4; ++outter_private) {
            intList1.push_back((int) (random() % 100L));
        }

        size length = intList1.size();
        cout << "length: " << length << endl;
    }
    return 0;
}

