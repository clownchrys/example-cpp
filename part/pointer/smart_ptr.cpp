//
// Created by 임근찬 on 2022/11/13.
//

#include "smart_ptr.h"
#include <memory>
#include <iostream>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::make_unique;
using std::cout;
using std::endl;


// Pseudo Smart Pointer
template<typename T>
class PseudoSmartPtr
{
private:
    T* ptr;

public:
    PseudoSmartPtr(T* ptr) : ptr(ptr) {}
    ~PseudoSmartPtr() { delete this->ptr; }
    T* operator->() { return this->ptr; }
};


int smart_ptr() {
    {
        PseudoSmartPtr smartPtr(new int(3));
    }

    // shared_ptr
    {
        // shared_ptr<int> ptr1(new int(1));
        shared_ptr<int> ptr1 = make_shared<int>(1); // use_count: 1
        auto ptr2 = ptr1; // use_count: 2
        cout << "(referenced to shared_ptr) shared_ptr.use_count() -> " << ptr1.use_count() << endl;
    }

    // weak_ptr
    {
        // shared_ptr<int> ptr1(new int(1));
        shared_ptr<int> ptr1 = make_shared<int>(1); // use_count: 1
        weak_ptr<int> ptr2(ptr1); // use_count: 1
        cout << "(referenced to weak_ptr) shared_ptr.use_count() -> " << ptr1.use_count() << endl;
    }

    // unique_ptr
    {
        unique_ptr<int> ptr1 = make_unique<int>(1);
        *ptr1 = 2;
        //auto ptr2 = ptr1;
        //shared_ptr<int> ptr2 = ptr1;
        //weak_ptr<int> ptr2 = ptr1;
        cout << "value of unique_ptr -> " << *ptr1 << endl;
    }

    return 0;
}
