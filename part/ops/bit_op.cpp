#include <iostream>

// define: 매크로
// 컴파일러가 지정한 매크로를 값으로 치환함

/* 각 비트 자리 별로 값 할당 (2의 승수)
 * 1, 2, 4, 8, 16, 32, ...
 * 또한 이러한 상태값은 일반적으로 16진수를 활용함
 * */
#define HUNGRY      0x001
#define THIRSTY     0x002
#define TIRED       0x004
#define FIRE        0x008

#define COLD        0x010
#define POISON      0x020
#define BUFF01      0x040
#define BUFF02      0x080

#define BUFF03      0x100
#define BUFF04      0x200
#define BUFF05      0x400
#define BUFF06      0x800

void bit_op() {
    /* 비트 연산자
     * 시프트: <<, >> (양 끝의 비트는 소실될 수 있음)
     *
     * 비트 곱: & (두 비트 값중 둘다 1 이면 1)
     * 비트 합: | (두 비트 값중 하나만 1 이어도 1)
     * 비트 반전: ~ (해당 비트 값을 반전)
     * XOR: ^ (두 비트 값이 같으면 0, 다르면 1)
     *
     * 대입 연산자와 함께 사용 가능
     * */
    unsigned int byte = 10;
    byte <<= 3; // 모든 비트의 자리 수를 한칸 왼쪽으로 옮김 -> 즉, 8(= 2의 세제곱) 배
    std::cout << byte << std::endl;
    byte >>= 3; // 모든 비트의 자리 수를 한칸 오른쪽으로 옮김 -> 즉, 1/8배한 몫 (단, 나머지는 소실)
    std::cout << byte << std::endl;

    int product = byte & byte;
    int sum = byte | byte;
    int x_or = byte ^ byte; // 자기 자신과의 xor 연산은 당연히 모든 비트 값이 0 이 되므로 연산된 값도 0
    int inversion = ~byte;
    std::cout << product << std::endl;
    std::cout << sum << std::endl;
    std::cout << x_or << std::endl;
    std::cout << inversion << std::endl;

    // 비트 연산자 활용: 상태 부여 (특정 자리 비트 값 부여)
    // 사전에 매크로 값을 각 비트 자리 별로 부여함 (2의 n 제곱)
    int status = 0; // bit: 0 0 ... 0 0 0 0
    status |= HUNGRY; // bit: 0 0 ... 0 0 0 1
    status |= THIRSTY; // bit: 0 0 ... 0 0 1 1
    status |= TIRED; // bit: 0 0 ... 0 1 1 1

    // 비트 연산자 활용: 상태 제거 (특정 자리 비트 제거)
    // status:                  0 0 ... 0 1 1 1
    // THIRSTY:                 0 0 ... 0 0 1 0
    // ~THIRSTY:                1 1 ... 1 1 0 1
    // status & ~THIRSTY:       0 0 ... 0 1 0 1 -> THIRSTY 자리의 비트만 제거
    status &= ~THIRSTY; // bit: 0 0 ... 0 1 0 1

    // 비트 연산자 활용: 상태 체크 (특정 자리 비트 값 체크)
    if (status & HUNGRY) std::cout << "IN STATUS: HUNGRY" << std::endl; // bit: 0 0 ... 0 0 0 1 -> 0 이 아니므로 true
    if (status & THIRSTY) std::cout << "IN STATUS: THIRSTY" << std::endl; // bit: 0 0 ... 0 0 1 0 -> 0 이 아니므로 true
    if (status & TIRED) std::cout << "IN STATUS: TIRED" << std::endl; // bit: 0 0 ... 0 1 0 0 -> 0 이 아니므로 true
}
