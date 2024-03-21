// 전처리기 include 는 해당 파일의 내용을 불러오는 역할을 함
#include "func.h"
#include "../part/var/var.h"
#include <iostream>
#include <random>

int g_count = 0;


//template<typename T>
//T Add(T a, T b)
//{
//    return a + b;
//}

int Sub(int a, int b)
{
    return a - b;
}

int Mul(int a, int b)
{
    return a * b;
}

int Div(int a, int b)
{
    return a / b;
}

int Counter() {
    return ++g_count;
}

// 랜덤 정수값
int get_random_number() {
    std::random_device rd; // 시드값을 얻기 위한 random_device 생성.
    std::mt19937 generator(rd()); // random_device 를 통해 난수 생성 엔진(generator)을 초기화 한다
    std::uniform_int_distribution<int> distribution(0, 99); // 균등 분포 정의

    int number = distribution(generator);
    return number;
}

// 정렬 (소트): 버블, 삽입, 선택, 합병(머지), 쾌속(퀵), 힙
// 버블 소트: 앞/뒤 1개의 쌍을 서로 비교하여 크거나 작은 경우에 두 원소의 위치를 서로 변경 -> 이를 반복하여 정렬
void bubble_sort(int *ptr, int length, bool ascending) {
    if (1 >= length) {
        return;
    }
    bool is_sorted = false;

    // run sort
    for (int i = 0; i < length - 1; ++i) {
        bool should_sort;

        if (ascending) {
            should_sort = ptr[i] > ptr[i + 1];
        } else {
            should_sort = ptr[i] < ptr[i + 1];
        }
        if (should_sort) {
            int tmp = ptr[i];
            ptr[i] = ptr[i + 1];
            ptr[i + 1] = tmp;
            is_sorted = true;
        }
    }

    // recursive: till sort finished
    if (is_sorted) {
        bubble_sort(ptr, length, ascending);
    }
}

