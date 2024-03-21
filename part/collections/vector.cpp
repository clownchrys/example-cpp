#include <iostream>
#include <vector>
#include "vector.h"
#include "collections.h"
#include "../../utils/func.h"

using std::cout;
using std::endl;


// struct (c-style impelementation)
typedef struct dynamic_array_ {
    int* ptr{};
    int length{}; // length == next_index;
    int capacity{};
    int step = 3;
} dynamic_array;


// util functions
void init(dynamic_array* obj) {
    obj->length = 0;
    obj->capacity = obj->step;
    obj->ptr = (int*) malloc(sizeof(int) * obj->step);
}

void release(dynamic_array* obj) {
    free(obj->ptr);
    obj->capacity = 0;
    obj->length = -1;
}

void reallocate(dynamic_array* obj) {
    int new_capacity = obj->capacity + obj->step;
    int* new_ptr = (int*) malloc(sizeof(int) * new_capacity);
    int* old_ptr = obj->ptr;

    for (int i = 0; i < obj->capacity; ++i) {
        new_ptr[i] = old_ptr[i];
    }
    free(old_ptr);

    obj->ptr = new_ptr;
    obj->capacity = new_capacity;
}

void append(dynamic_array* obj, int i) {
    if (obj->capacity <= obj->length) {
        reallocate(obj);
    }

    obj->ptr[obj->length++] = i;
}

void print(dynamic_array* obj) {
    for (int i = 0; i < obj->length; ++i) {
        printf((i == 0) ? "{ %d" : " %d", obj->ptr[i]);
    }
    printf(" }\n");
}

void sort(dynamic_array* obj, void (* sort_fn)(int*, int, bool), bool asending = true) {
    sort_fn(obj->ptr, obj->length, asending); // 함수형 포인터 사용
}

// main
int test_vector() {
    /* 변수는 바뀔 수 있는 값 이므로
     * 변수 i는 스캐너를 통해 런타임에 할당될 수도 있음
     * 사전에 배열의 크기를 미리 알 수 없으므로 컴파일이 불가능하고, 스택 메모리 크기를 결정할 수 없음
     * */

    // c-style: 구조체와 동적 할당을 통한 가변 배열 구현
    {
        dynamic_array arr = {};
        init(&arr);

        for (int outter_private = 0; outter_private < 10; ++outter_private) {
            append(&arr, (int) (random() % 100L));
        }

        print(&arr);
        sort(&arr, bubble_sort, false);
        print(&arr);

        release(&arr);
    }

    // cpp-style: 클래스와 템플릿을 활용한 가변 배열 구현
    {
        Vector<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.append(i);
            printf("%d\n", arr[i]);
        }
        arr.sort(bubble_sort, false);
        arr.print();
        arr.sort(bubble_sort, true);
        arr.print();

        Vector<int>::iterator iter;

        for (iter = arr.begin(); iter != arr.end(); ++iter) {
            cout << *iter << endl;
        }

        iter = arr.begin();
        cout << *iter << endl;
        cout << *(++iter) << endl;
        cout << *(iter++) << endl;
        cout << *iter << endl;

        iter = arr.begin();
        ++ ++iter;
        arr.print();
        arr.erase(iter);
        arr.print();
        arr.erase(iter);
        arr.print();
        arr.erase(iter);
        arr.print();

        arr.clear();
        arr.append(1);
        arr.print();

        cout << arr.size() << ", " << arr.capacity() << ", " << arr[0] << endl;
    }

    // STL (Standard Template Library)
    {
        using std::vector;
        using size = std::size_t;

        vector<int> intVector = vector<int>();

        for (int i = 0; i < 4; ++i) {
            intVector.push_back((int) (random() % 100L));
        }

        size capacity = intVector.capacity();
        size length = intVector.size();
        cout << "capacity: " << capacity << ", ";
        cout << "length: " << length << endl;

        vector<int>::iterator iter;
        for (iter = intVector.begin(); iter != intVector.end(); ++iter) {
            cout << "vector: " << *iter << endl;
        }
    }

    return 0;
}

