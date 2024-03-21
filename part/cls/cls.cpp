#include <iostream>
#include "cls.h"

using std::cout;
using std::endl;

/* cpp 클래스 특징
 * 1. 접근 제한 지정자: private, protected(상속), public
 * 2. 멤버 함수 -> 해당 객체의 주소가 this 포인터로 전달
 * 3. 생성자 및 생성자 이니셜라이저
 * 4. 소멸자
 * 5. 연산자 오버로딩
 * */

/* 암시적으로 구현하는 멤버
 * 생성자 (복사 생성자 포함하여, 어떠한 생성자도 구현하지 않은 경우에만)
 * 소멸자
 * 복사 생성자: Vector(const Vector<T>& other);
 * -> Vector<int> arr1(arr2); 또는 Vector<int> arr1 = arr2;
 * 대입 연산자: Vector<T>& operator=(const Vector<T>& _other);
 * -> arr1 = arr2;
 * */

/* inline 키워드
 * 함수는 호출 스택에 하나씩 쌓여가면서 실행됨
 * 반면, header에 구현한 내용은 #include를 통해 컴파일러가 코드를 추가해 버림
 *
 * 1 ~ 2줄짜리 함수는 호출 스택을 사용하는 것이 오히려 비용이 더 큰 경우가 있음
 * 이런 경우에는 header 내용을 include하는 것 처럼 컴파일 시점에서 사용점으로 코드를 추가하는 것이 퍼포먼스가 더 나을 수 있음
 * 이와 같은 경우에 inline 키워드를 통해 컴파일러에게 위 내용을 요청할 수 있음
 *
 * getter, setter 또는 1 ~ 2줄 정도되는 짧은 함수가 적절하며, 템플릿의 경우 header에 구현하므로 inline이 의마가 없음
 * */

// decl -> Outter
class Outter {
// private 멤버
private:
    int outter_private;

// public 멤버
public:
    int outter_public;
    const float const_member = 3.14f;

// 생성자, 소멸자
public:
    // 선언 (외부 구현)
    Outter(int i, float f, int id);
    Outter(const Outter& other); // 복사 생성자

    // 내부 구현
    Outter() = default;
    ~Outter()
    {
        cout << "run deconstruct..." << endl;
    }

// 연산자 오버로딩
public:
    /* const after function
     * 1. 함수 내에서 어떠한 멤버 변수도 변경할 수 없음 (mutable 제외)
     * 2. const 함수만 호출 가능
     * 3. 일반 함수와 구분하여 정의 가능
     * 4. 따라서, 일반적으로 getter 또는 bool 값을 반환하는 경우에 사용
     * */
    bool operator==(const Outter& other); // 동등 비교 (non-const)
    bool operator==(const Outter& other) const; // 동등 비교 (const)
    bool operator!=(const Outter& other);
    bool operator!=(const Outter& other) const;

    Outter& operator++(); // 증감 연산자: 전방
    Outter operator++(int); // 증감 연산자: 후방

    Outter& operator<<(const Outter& other);
    Outter& operator>>(Outter& other);
    Outter& operator=(const Outter& other);

    Outter operator*();
    Outter* operator->();

// 전방 선언: 아래 함수에서 Inner 클래스를 사용하기 위함
public:
    class Inner;

// public 함수
public:
    void public_func(Inner inner) {
        inner.inner_public;
        //inner.inner_private; // Outter 에서는 Inner 접근 불가
    }

// private 함수
private:
    void private_func(Inner inner) {
        inner.inner_public;
        //inner.inner_private; // Outter 에서는 Inner 접근 불가
    }

// 내부 클래스
public:
    // decl -> Outter::Inner
    class Inner {
    public:
        int inner_public;

        void public_func(Outter outter)
        {
            outter.outter_public;
            outter.const_member;
            outter.outter_private; // Inner 에서는 Outter 접근 가능
        }

    private:
        int inner_private;

        void private_func(Outter outter)
        {
            outter.outter_public;
            outter.const_member;
            outter.outter_private; // Inner 에서는 Outter 접근 가능
        }
    };
};

// impl -> Outter
Outter::Outter(int i, float f, int id) : outter_private(id), const_member(f), outter_public(i) {}

Outter::Outter(const Outter& other) :
    outter_private(other.outter_private)
    , const_member(other.const_member)
    , outter_public(other.outter_public)
{
    cout << "copy construnctor" << endl;
}

bool Outter::operator==(const Outter& other)
{
    return outter_public == other.outter_public;
}

bool Outter::operator==(const Outter& other) const
{
    return outter_public == other.outter_public;
}

bool Outter::operator!=(const Outter& other)
{
    return !(this->operator==(other));
}

bool Outter::operator!=(const Outter& other) const
{
    return !(this->operator==(other));
}

Outter& Outter::operator++()
{
    ++this->outter_public;
    return *this;
}

Outter Outter::operator++(int)
{
    const Outter copy = Outter(*this);
    ++(*this);
    return copy;
}

Outter& Outter::operator<<(const Outter& other) {
    outter_private = other.outter_private;
    return *this;
}

Outter& Outter::operator>>(Outter& other)
{
    other.outter_private = outter_private;
    return other;
}

Outter& Outter::operator=(const Outter& other) {
    outter_public = other.outter_public;
    outter_private = other.outter_private;
    return *this;
}

Outter Outter::operator*()
{
    return *(new Outter(*this));
}

Outter* Outter::operator->()
{
    return new Outter(*this);
}




int base_cls() {
    /* Symbol
     * 자료형 * 변수명    (포인터 변수 선언)
     * *포인터변수       (역참조)
     * &변수            (주소값 반환)
     *
     * 자료형 & 변수명    (레퍼런스 변수 선언)
     * */

    {
        int a = 10;

        // 포인터
        int* const p = &a;
        *p = 100;

        // 레퍼런스 변수 (cpp)
        // 포인터와 유사
        // 원본을 참조하고, 참조 변수를 통해서 직접적으로 원본을 수정할 수 있음
        int& iRef = a; // a를 참조하는 레퍼런스 변수 iRef 선언 (const var)
        iRef = 100; // iRef를 수정하는 것 == a를 수정하는 것

        // const ref (const pointer)
        // 참조만 가능하고, 쓰기가 불가능
        const int& iConstRef = a;
        //iConstRef = 200;
    }

    Outter a; // Outter a = Outter();
    Outter b(1, 3.f, 2); // Outter b = Outter(1, 3.f, 2);
    Outter c(a); // Outter c = Outter(a); // copy constructor

    Outter::Inner d;

    a.outter_public;
    a.const_member;
    //a.outter_private;

    a.public_func(d);
    //a.private_func(d);

    if (a == c) {
        cout << "a eqauls c" << endl;
    }
    ++a;
    a++;

    (*a).outter_public;
    a->outter_public;

    return 0;
}