#include <iostream>
#include "pointer.h"

// 함수형 포인터를 위한 함수 선언
void func1() {}

int func2(int a, float b) { return 0; }

int func3(int a, float b) { return 0; }

/* 메모리 주소
 * 주소의 단위: bytes (주소가 1차이 난다면, 1byte 간격을 의미) */

/* 포인터
 * *: 포인터 변수를 의미 (메모리 주소를 저장 하는 변수)
 * &: 해당 변수의 메모리 주소 값을 나타냄
 * nullptr 키워드: 널 포인터 (== 0x0000)
 *
 * 포인터가 타입을 알아야 하는 이유
 * 1. 해당 주소에서 몇 bytes까지 접근할지를 알아야 하기 때문
 * 2. 접근한 bit값 들을 어떻게 해석해야 할지를 알아야 하기 때문
 *
 * 추가: 또한, 증감 단위가 해당 자료형의 bytes, 즉 sizeof(dtype) 단위임 (pointer += 1)
 * */

void set_value(int a, int v) {
    a = v;
}

void set_value(int* pointer, int v) {
    *pointer = v;
}

void read_data(const int* pointer) {
    printf("%d\n", *pointer);
}

void pointer() {
    int i1 = 0;
    int i2 = 0;

    // 기본 사용법
    {
        // 선언과 할당
        int* pInt1; // 선언
        pInt1 = &i1; // 할당 (주소값)
        // pInt = 100; // 불가능 -> 포인터 변수에는 주소값만 할당할 수 있음

        // 선언과 할당 동시에
        int* pInt2 = &i2; // 주소로 접근하는 것과 개념을 혼동하지 말 것! (원래는 위와 같이 선언과 할당을 나눠서 하는 것임)

        // 주소로 접근
        *pInt1 = 100; // *pInt: 포인터 변수가 가지고 있는 메모리 주소에 접근하여 -> = 100: 값을 할당 (O)
        *pInt2 = -100;

        printf("%d\n", i1);
        printf("%d\n", i2);
    }

    /* 배열
     * 배열은 그 자체가 포인터 임
     * 인덱싱 -> 연속적인 메모리 주소를 갖고 있기 때문에 가능
     * */
    {
        // int ( &pArr )[10] = arr; // 배열 포인터
        int arr[10] = {};
        std::cout << arr << std::endl;
        std::cout << &arr[0] << std::endl;

        *(arr + 0) = 10; // arr[0] = 10;
        *(arr + 1) = 10; // arr[1] = 10;
    }

    // 다른 호출 스택에서 값 변경
    {
        int i = 0;
        set_value(i, 500); // 함수 스코프 내에서만 변경
        set_value(&i, 500); // 실제 메모리 주소의 값을 변경
    }

    /* 포인터를 사용한 일반 상수값 변경
     * const: 상수화 (r-value)
     * volatile: 컴파일러가 최적화를 수행하지 않음 / 레지스터에 로드된 값을 사용하지 않고 매번 메모리를 로드함
     * */
    {
        volatile const int cInt1 = 100;
        int* pInt = (int*) &cInt1;
        *pInt = 200;
        printf("%d\n", cInt1);
    }

    // const
    {
        // 1. const pointer (const *)
        // 메모리 주소를 변경 (O) / 주소의 실제 값 변경 (X) -> 포인터를 상수화 (read-only pointer)
        const int* pConstInt = &i1; // ==
        pConstInt = &i2; // 메모리 주소를 변경 가능
        //*pConstInt = 299; // 메모리 주소의 실제 값은 변경할 수 없음

        // 2. const var (* const)
        // 메모리 주소를 변경 (X) / 주소의 실제 값 변경 (O) -> 변수를 상수화
        int* const pIntConst = &i1;
        //pIntConst = &i2; // 메모리 주소를 변경할 수 없음
        *pIntConst = 299; // 메모리 주소의 실제 값은 변경 가능

        // 3. 모두 상수화 하기
        const int* const pConst = &i1;
        //pConst = &i2; // 메모리 주소를 변경할 수 없음
        //*pConst = 299; // 메모리 주소의 실제 값은 변경할 수 없음

        // 4. 기출 변형 (== 1)
        // 따라서, const 위치를 * 기준 앞/뒤로 생각하면 좋음
        int const* pConstInt2 = &i1;
        //*pConstInt = 299; // 메모리 주소의 실제 값은 변경할 수 없음

        // 5. const 포인터의 활용
        read_data(&i1); // 포인터를 넘겨주더라도, 원본 데이터가 훼손당하지 않음

        // 6. const 강제 캐스팅 (어떻게든 바꿀려면 바꿀 수 있다...)
        int* pInt = const_cast<int*>(pConstInt2);
        *pInt = 123;
    }

    /* void pointer
     * 1. 원본 데이터를 해석할 방법을 정하지 않음
     * 2. 모든 데이터 타입을 다 받을 수 있음
     * 3. 역참조 불가능
     * 4. 주소 연산 불가능 (step 을 결정할 수 없음)
     * */
    {
        void* pVoid = nullptr;

        int i = 1;
        float f = 1.f;

        pVoid = &i;
        pVoid = &f;

        //f = *pVoid;
    }

    /* function pointer
     * return_type (*var_name)(args_type) = function;
     * */
    {
        // 함수형 포인터 선언
        void (* ptr1)() = &func1; // 인자가 없다는 의미로 void 라고 써도 됨
        int (* ptr2)(int, float) = func2; // 함수 자체가 주소값이므로, & 없이 사용 가능
        int (* const ptr3)(int, float) = func2; // const var

        ptr2 = func3;
        //ptr3 = func3;
    }
}
