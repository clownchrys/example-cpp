#include <iostream>
#include <string>
#include "../../utils/func.h"

using namespace std;
//using std::cout;
//using std::endl;
//using std::string;

/* OOP 의 특징
 * 1. 캡슐화
 * 2. 상속
 * 3. 다형성
 * 4. 추상화
 * */

/* 메모리 구조
 * 상속이 발생하는 경우, 메모리는 순차적으로 할당됨
 *
 * Parent -> [ Parent ]
 * Child -> [ Parent | Child ]
 * GrandChild -> [ Parent | Child | GrandChild ]
 * */

/* 생성자 동작 방식
 * 각 클래스의 멤버는 각자의 생성자를 통해 초기화 함 (initialization list)
 * 단, 생성자의 블록에서 부모의 멤버에 값을 할당하는 것은 가능
 *
 * Call Stack(호출 순서) : 자식 -> 부모
 * Execution(실행 순서) : 부모 -> 자식
 * */

class Parent {
private:
    int private_i;
protected:
    int protected_i;
public:
    Parent() : private_i(0), protected_i(0) {}
    Parent(int i) : private_i(i), protected_i(i) {}
    ~Parent() = default;
public:
    int getPrivateInt() { return private_i; }
    void setPrivateInt(int i) { this->private_i = i; }
    void name() { cout << "Parent" << endl; }

    virtual void virtual_name() { cout << "(virtual) Parent" << endl; }
};


class Child : public Parent {
private:
    float f;
public:
    /* 생성자
     * 호출 순서: 자식 -> 부모 (마지막에 적어주더라도 반드시 부모 생성자가 먼저 실행됨)
     * 실생 순서: 부모 -> 자식
     *
     * 부모 생성자 호출을 생략하면 부모 클래스의 기본 생성자를 실행함 (다른 생성자를 사용하고 싶다면 명시적으로 적어주어야 함)
     * */
    Child() : f(3.14f), Parent(100) {} // Parent(100) -> f(3.14f)

    /* 소멸자
     * 호출 순서: 자식 -> 부모
     * 실행 순서: 자식 -> 부모
     * */
    ~Child() = default;

public:
    //void setPrivateInt(int i) { this->private_i = i; } // 상속받았더라도 private 으로 선언되었으므로 i 접근 불가능
    void setProtectedInt(int i) { this->protected_i = i; } // 외부에서는 접근이 불가능하지만, 상속받은 클래스에서는 접근 가능

    // 오버 리이딩
    void name() { cout << "Child" << endl; }
    void virtual_name() override { cout << "(virtual) Child" << endl; }
};

class GrandChild : Child {
private:
    long long private_ll;
};


/* 추상화
 * 실제 객체를 생성할 목적의 클래스가 아닌, 상속을 통해서 구현해야할 내용을 전달하는 상속 목적으로 만들어진 클래스
 * virtual, = 0 (1개 이상의 순수 가상함수를 포함하면 추상클래스가 됨)
 * */

/* 추상 클래스 구현
 * 하나 이상의 순수 가상함수를 가진 클래스
 * */
class AbstractCls {
private:
    virtual int index() = 0; // 순수 가상 함수
public:
    virtual int getInt() { return 1; } // 가상 함수
    static string getName() { return "AbstractCls Class"; } // 일반 메서드
};

class DefiniteCls : public AbstractCls {
    int index() override { return 0; }
};

/* 인터페이스 구현
 * 구현이 없음
 * 즉, 가상 소멸자와 순수 가상함수로만 이루어진 클래스
 * */
class InterfaceCls
{
public:
    virtual ~InterfaceCls() = default;
    virtual void move_x(int x) = 0;
    virtual void move_y(int y) = 0;
    virtual void draw() = 0;
};

class Horse : public InterfaceCls
{
private:
    int horizontal = 0;
    int vertical = 0;
public:
    ~Horse() override { cout << "Horse is dying..." << endl; }
    void move_x(int x) override { horizontal += x; }
    void move_y(int y) override { vertical = 0; }
    void draw() override { cout << "Horse(" << horizontal << ", " << vertical << ")" << endl; }
};

class Bird : public InterfaceCls
{
private:
    int horizontal = 0;
    int vertical = 10;
public:
    ~Bird() override { cout << "Bird is dying..." << endl; };
    void move_x(int x) override { horizontal += x; }
    void move_y(int y) override { vertical += y; }
private:
    // 구현된 함수를 접근제어자를 통해 막는 것이 가능하다는 점 주의할 것!
    void draw() override { cout << "Bird(" << horizontal << ", " << vertical << ")" << endl; }
};


void function_with_obj(Parent obj) {
    cout << obj.getPrivateInt() << endl;
}

void function_with_ptr(Parent* ptr) {
    cout << ptr->getPrivateInt() << endl;
}


// 다중 상속
class Father {
protected:
    int facial_type = 1;
    int toughness = 1;
};

class Mother {
protected:
    int facial_type = 2;
    int beauty = 2;
};

class Son : public Father, Mother {
    // 모호하지 않은 변수는 단일 상속과 동일하게 접근 가능
    int derived_nature() {
        return toughness + beauty;
    }

    // 다중 상속으로 인해, 멤버 변수의 의미가 모호해진 경우에는 클래스명을 통해 멤버에 접근해야 함
    int derived_facial_type() {
        if (get_random_number() > 50) {
            return Father::facial_type;
        }
        else {
            return Mother::facial_type;
        }
    }
};


// 가상 상속 (이중 상속으로 인해 발생하는 문제점 해결)
class Base
{
public:
    Base() { cout << "Base Constructor" << endl; }
    void simpleFunc() { cout << "Base" << endl; }
};

class MiddleDerivedOne: virtual public Base // Base 클래스를 가상상속
{
public:
    MiddleDerivedOne(): Base()
    {
        cout << "MiddleDerivedOne Constructor" << endl;
    }
    void middleFuncOne()
    {
        simpleFunc();
        cout << "MiddleDerivedOne" << endl;
    }
};

class MiddleDerivedTwo: virtual public Base // Base 클래스를 가상상속
{
public:
    MiddleDerivedTwo(): Base() { cout << "MiddleDerivedTwo Constructor" << endl; }
    void middleFuncTwo()
    {
        simpleFunc();
        cout << "MiddleDerivedTwo" << endl;
    }
};

class LastDerived: public MiddleDerivedOne, public MiddleDerivedTwo
{
public:
    LastDerived(): MiddleDerivedOne(), MiddleDerivedTwo() { cout << "LastDerived Constructor" << endl; }
    void complexFunc()
    {
        middleFuncOne();
        middleFuncTwo();

        /* Base 클래스를 가상 상속을 하지 않았다면?
         * - LastDerived 클래스에 Base 멤버가 2번 포함됨 (실제로 Base의 초기화 역시 2번 수행됨)
         * - simpleFunc() 가 어떤 멤버를 지칭하는지 모호해짐
         *
         * 따라서,
         * MiddleDerivedOne::simpleFunc();
         * MiddleDerivedTwo::simpleFunc();
         * 처럼 호출할 수 밖에 없음
         *
         * 그러나 논리적으로 최종 상속받은 클래스에 Base 멤버가 이중으로 존재하는 것은 맞지 않음
         * */

        /* 그러면 Base 클래스를 가상 상속한 경우에는?
         * - Base 멤버가 1번만 포함됨 (Base의 초기화는 1번만 수행됨)
         * = 최종적으로 상속받은 클래스에 Base 멤버가 이중으로 존재하지 않음!
         * */

        simpleFunc();
    }
};


int inherit()
{
    Parent parent;
    Child child;
    GrandChild grandChild;

    parent.setPrivateInt(10);
    parent.name();

    child.setPrivateInt(10);
    child.setProtectedInt(10);
    child.name();
    child.Parent::name(); // 부모 클래스의 함수 사용

    // 다형성과 포인터
    Parent* parent_ptr;
    Child* child_ptr;
    {
        parent_ptr = &parent;
        child_ptr = &child;

        parent_ptr = &child; // 메모리 구조상 포인터가 Parent로 해석 가능
        //child_ptr = &parent; // Child 객체가 있을 것으로 예상되는 주소가 침범당함 -> Child로 해석 불가능 (컴파일 오류)
    }
    {
        function_with_obj(parent);
        function_with_obj(child); // just warning

        function_with_ptr(&parent);
        function_with_ptr(&child); // even no warning (syntax ok)
    }

    // 포인터 다형성의 한계
    {
        parent_ptr = &parent;
        parent_ptr->name(); // Parent

        parent_ptr = &child;
        parent_ptr->name(); // Parent (not Child)
    }

    // 해결: 가상 함수
    // 각 클래스가 가진 고유한 가상 함수 테이블에 실제 객체에 대한 정보를 가지고 있음
    {
        parent_ptr = &parent;
        parent_ptr->virtual_name(); // Parent

        parent_ptr = &child;
        parent_ptr->virtual_name(); // Child
    }

    // 다운 캐스팅 (Runtime)
    // Temporarily cast to Child* for using child-only-members
    // dynamic_cast 로 안전하게 cast 할 수 있음 -> casting 실패 시 nullptr 반환
    {
        parent_ptr = &child;
        Child* tmp_ptr = dynamic_cast<Child*>(parent_ptr);
        if (tmp_ptr) {
            tmp_ptr->setProtectedInt(10); // child-only-function
        }
    }

    // 추상 클래스와 인터페이스 (다중 상속이 가능해 실질적인 차이는 없음)
    {
        //AbstractCls abstract_class;
        DefiniteCls definite_class;

        //Interface interface_cls;
        Horse horse;
        Bird bird;
        horse.draw(); // public
        //bird.draw(); // private (접근제어자를 통해 접근을 막음)
    }

    return 0;
}
