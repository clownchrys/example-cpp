#include "collections.h"
#include <iostream>


int test_array() {
    /*
     * 배열은 연속적인 메모리 구조
     * 따라서, index로 접근하는 도중에 error 없이 다른 메모리 주소의 값을 수정해버릴 수 있음
     * */
    int array[10] = {}; // 모든 원소 0으로 초기화
    array[9] = 10;
    array[11] = -1;
    std::cout << array[0] << std::endl;
    std::cout << array[9] << std::endl;

    return 0;
}
