#include <iostream>

void arithmetic_op() {
    /* 산술 연산자
     * 사칙 연산: +, -, *, /
     * 나머지: % (모듈려스 연산자, 나머지)
     * 위 연산자 모두 대입 연산에 가능
     *
     * 증감 연산: ++, --
     * */
    int i = 0;

    i += 5; std::cout << i << std::endl;
    i %= 2; std::cout << i << std::endl;
    std::cout << 5 / 2 << std::endl; // 정수간 나누기 연산은 정수 반환
    std::cout << 5 / 2. << std::endl; // 정수-실수간 나누기 연산은 실수 반환
    std::cout << 5. / 2. << std::endl; // 실수간 나누기 연산은 실수 반환
}
