#include "statements.h"
#include <iostream>


void condition(unsigned char c) {
    int i = c;

    if (i == 0) {
        std::cout << "if statement" << std::endl;
    } else if (i > 0) {
        std::cout << "else if statement" << std::endl;
    } else {
        std::cout << "else statement" << std::endl;
    }

    /*
     * 1. switch 문은 위의 정수형 으로만 사용 가능
     * std::string str = "12345";
     * switch (str) {} // 컴파일 불가
     *
     * 2. cascading 주의할 것
     * */
    switch (c) {
        case 0:
            std::cout << "switch case 0" << std::endl;
            break;
        case 1: {
            std::cout << "switch case 1" << std::endl;
            break;
        }

            // case 2, 3, 4 는 case 4 로 cascading
        case 2:
        case 3:
        case 4:
            std::cout << "switch case 2, 3, 4" << std::endl;
            break;

            // 나머지 경우는 default 로 분기
        default:
            std::cout << "switch default" << std::endl;
            break;
    }
}
