#include "var.h"
#include <iostream>

/* static 키워드
 * 선언된 스코프(파일, 클래스, 함수) 단위 에서만 유일하게 존재함
 * */
int global_var = 1; // 전역 변수: 모든 cpp 파일 내에서 유일해야 함 (그렇지 않으면 링크시 에러)
static int static_global_var = 1; // 정적 변수: 해당 파일 내에서만 유일함 (따라서 복수 파일에 동일한 이름으로 존재 가능)


void variables() {
    int local_var = 0; // 지역 변수: 해당 호출 스택이 제거되면서 메모리 해제
    static int static_local_var = 0; // 정적 변수: Data 영역을 사용하므로, 함수의 종료로 인해서 메모리 해제되지 않음

    printf("local_var: %d\n", ++local_var); // 무조건 1 (지역 변수: 매 호출 마다 0으로 초기화 됨)
    printf("static_local_var: %d\n", ++static_local_var); // 함수 호출 횟수 (정적 변수: 최초 호출 시에만 0으로 초기화 됨)
    printf("extern_var: %d\n", ++extern_var); // declared in var.h -> assign in main.cpp -> used in var.cpp
}
