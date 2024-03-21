#include <iostream>
#include "dtypes.h"

/* 데이터 타입 (byte = 8 bits)
 * 정수형: char(1), short(2), int(4), long(4), long long(8)
 * 실수형: float(4), double(8)
 * 부호 비트 사용: signed (default), unsigned
 *
 * 리터럴 표현: 1l (long), 1ll (long long), 1.f (float)
 * */

void dtypes() {
    unsigned char c = 1;
    int i = 1;
    float f = 10.2415f + (float) 20;
    long l = 1;
    long long ll = 1;

    std::cout << c << std::endl;
    std::cout << i << std::endl;
    std::cout << f << std::endl;
    std::cout << l << std::endl;
    std::cout << ll << std::endl;
}
