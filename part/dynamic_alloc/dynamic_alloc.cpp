#include "dynamic_alloc.h"
#include <iostream>



/* 정적 할당
 * 지역 변수: 스택
 * 전역/정적/외부 변수: 데이터
 * 변수 -> 컴파일 및 프로그램 실행 시에 할당 (코드를 통해)
 * */

/* 동적 할당
 * 런타임 중에 대응가능한 메모리 공간 필요 -> Heap
 * 변수 대신에 주소를 통해 접근
 *
 * 할당
 * malloc(): void pointer를 반환하므로, casting 을 통해 원하는 자료형으로 변경해서 사용해야 함
 *
 * 해제
 * */
int dynamic_alloc() {
    int *pInt = nullptr;

    // malloc <-> free
    {
        pInt = (int *) malloc(4); // 4 bytes
        *pInt = 321;
        printf("allocated memory freeing...%p\n", pInt);
        free(pInt);
    }

    // new <-> delete
    {
        pInt = new int;
        *pInt = 123;
        printf("new object deleting...%p\n", pInt);
        delete pInt; // 단일 값 제거시

        pInt = new int[3];
        for (int i = 0; i < 3; ++i) {
            pInt[i] = i;
        }
        printf("new object deleting...%p\n", pInt);
        delete[] pInt; // 묶음 값 제거시
    }


    return 0;
}
