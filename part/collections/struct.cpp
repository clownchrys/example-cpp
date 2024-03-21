#include "collections.h"
#include <iostream>

/* 구조체
 * 사용자 정의 자료형
 * struct <이름> {...}
 * typedef <TypeA> <Alias> -> TypeA를 Alias로 타입 재정의
 *
 * struct 키워드를 반복적으로 사용하는 것을 피하기 위해 typedef 와 같이 사용함
 * 그러나 CPP 에서는 struct 키워드를 사용하지 않아도 됨
 * 단, C와의 호환을 고려하는 경우에는 typedef 와 함께 쓰는 것이 유리
 * */

// MyData 라는 구조체 정의
struct MyData {
    int i; // 4bytes
    float f; // 4bytes
};

// typedef: Alias 로 타입 재정의
typedef int INT; // int -> INT 로 타입 재정의
typedef struct MyData MyData2; // struct MyData -> MyData2 로 재정의
typedef struct MyData3_ {
    struct MyData d1;
    MyData2 d2;
    INT i = 0; // 초기값 지정
} MyData3; // MyData3_ 라는 구조체를 정의하고, 이를 MyData3 로 재정의


int test_struct() {
    // 구조체 기본 개념
    {
        struct MyData d_c; // c-style
        MyData d_cpp; // cpp-style (struct 키워드 없이 사용 가능)

        // 초기화
        MyData d1; // 알 수 없는 값으로 초기화
        MyData2 d2 {}; // (배열과 같이) 0 으로 초기화
        MyData3 d3 {d1, d2, 123}; // 지정한 값으로 초기화

        printf("MyData %d bytes\n", (int) sizeof(d1));
        printf("MyData2 %lu bytes\n", sizeof(MyData2));
        printf("MyData3 %lu bytes\n", sizeof(d3));
    }

    // 구조체 포인터
    {
        MyData d1 = {0, 0.f};

        // 다음 구조체 포인터는 int outter_private (4bytes) + float f (4bytes) 메모리가 연속적으로 있을 것으로 해석함
        MyData* pMyData;

        // 포인터를 사용해서 멤버 변수에 접근하기
        pMyData = &d1;
        pMyData->i = 10; // (*pMyData).outter_private = 10;
        pMyData->f = 3.14; // (*pMyData).f = 3.14f;
        printf("d1 is { outter_private=%d, f=%f }\n", d1.i, d1.f);

        // 구조체 포인터의 증감 연산: sizeof(MyData) -> 8bytes
        std::cout << pMyData << std::endl;
        pMyData += 1;
        std::cout << pMyData << std::endl;
    }

    return 0;
}

