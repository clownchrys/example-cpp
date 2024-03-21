#include <iostream>
#include <string>
using namespace std;

class Base
{
    virtual void dummy() {}
};

class Derived : public Base
{
    int a;
};

int cast()
{
    /* 캐스팅의 종류
     * 다운캐스트: ptr_base -> ptr_derived
     * 업캐스트: ptr_derived -> ptr_base
     * */

    // cast 기본 문법
    {
        int i = 45;
        float a = float (i); // functional cast
        float b = (float) i; // c-style cast
    }
    /* dynamic_cast
     * 객체를 다운캐스트 또는 업캐스트 함
     * 클래스에 대해 포인터와 포인터간, 레퍼런스와 레퍼런스 간의 변환만을 허용 (int, float 등 기본 자료형 변환 불가)
     *
     * 실행시간 타입 정보(Runtime Type Information, RTTI)가 필요
     * */
    {
        Base* p_base_from_derived = new Derived;
        Base* p_base_from_base = new Base;
        Derived* p_derived;

        // cast ok
        p_derived = dynamic_cast<Derived*>(p_base_from_derived); // not nullptr
        cout << "(1) dynamic_cast(base -> derived): " << p_derived << endl;

        // cannot cast (incomplete cast, then returns nullptr)
        p_derived = dynamic_cast<Derived*>(p_base_from_base); // nullptr
        cout << "(2) dynamic_cast(base -> derived): " << p_derived << endl;

        // cannot cast (not a class)
        int i = 45;
        //float* f = dynamic_cast<float*>(&i);
        //cout << "dynamic_cast(int -> float): " << f << endl;

        // clean-up
        delete p_base_from_base;
        delete p_base_from_derived;
    }
    /* static_cast
     * 논리적으로 변경 가능하기만 하면 변경을 허용 -> 불완전 캐스팅을 지원 (그러므로 가급적이면 dynamic_cast 사용할 것)
     * 이로 인해 dynamic_cast의 safe-type-check에 대한 오버헤드가 발생하지 않음
     * */
    {
        Base* p_base_from_derived = new Derived;
        Base* p_base_from_base = new Base;
        Derived* p_derived;

        // cast ok
        p_derived = static_cast<Derived*>(p_base_from_derived); // not nullptr
        cout << "(1) static_cast(base -> derived): " << p_derived << endl;

        // cast ok (incomplete cast, but not returns nullptr)
        p_derived = static_cast<Derived*>(p_base_from_base); // not nullptr
        cout << "(2) static_cast(base -> derived): " << p_derived << endl;

        // cast ok
        int i = 45;
        float f = static_cast<float>(i);
        cout << "(3) static_cast(int -> float): " << f << endl;

        // clean-up
        delete p_base_from_base;
        delete p_base_from_derived;
    }
    /* reinterpret_cast
     * 한 포인터의 값을 다른 포인터로 단순 바이너리 복사
     * 관련 없는 클래스라도 다른 포인터 유형으로 변환 가능 (모든 포인터 변환이 허용)
     * 확실하게 변환이 가능한 상황에만 한정적으로 사용해야 함 (매우 위험한 변환)
     * */
    {
        float f = 3.14;
        int* i = reinterpret_cast<int*>(&f);
        cout << "(1) reinterpret_cast(float -> int): " << i << endl; // 단순 바이너리 복사이므로, 단순히 포인터가 가리키는 byte값 복사와 다르지 않음
    }
    /* const_cast
     * 상수 속성만 변경할 때 사용 -> 따라서, 당연히 되는 형태의 형변환도 불가능 (int -> double)
     * volatile이나 __unaligned의 속성을 처리할 때도 사용 가능
     * */
    {
        const char* a = "sample text";
        char* b = const_cast<char*>(a);
        const char* c = const_cast<const char*>(b);
    }

    return 0;
}