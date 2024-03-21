#pragma once

/* 함수 템플릿
 * 컴파일 시점에서 함수가 만들어 짐
 * 단, 같은 타입의 함수는 1번만 만들어 짐
 *
 * template 을 활용하는 경우에는 분할 구현이 조금 어려움
 * 함수의 선언을 cpp 에서 다시 명시적으로 해주어야 함 -> ex. int Add(int a, int b);
 * 따라서, 헤더 파일에 구현까지 해야 함
 * */
template <typename T>
T Add(T a, T b) {
    return a + b;
};

int Sub(int a, int b);

int Mul(int a, int b);

int Div(int, int);

int Counter();

int get_random_number();

void bubble_sort(int* ptr, int length, bool ascending);