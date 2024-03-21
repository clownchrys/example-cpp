#include <iostream>
#include <thread>
#include <string>
#include <fstream>

using std::thread;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

#include "utils/func.h"
#include "part/dtypes/dtypes.h"
#include "part/ops/ops.h"
#include "part/statements/statements.h"
#include "part/collections/collections.h"
#include "part/dynamic_alloc/dynamic_alloc.h"
#include "part/var/var.h"
#include "part/pointer/pointer.h"
#include "part/interface/interface.h"
#include "part/cls/cls.h"
#include "part/exception//exception.h"
#include "part/cast/cast.h"
#include "part/threading/threading.h"
#include "part/pointer/smart_ptr.h"

int extern_var = 100; // var.h

using std::cout;
using std::endl;


int main() {
    setlocale(LC_ALL, "korean");
    std::cout << "c++ version: " << __cplusplus << '\n';

//    // dtypes
//    dtypes(); // 데이터 타입
//
//    // ops
//    arithmetic_op(); // 산술 연산자
//    logical_op(); // 논리 연산자
//    trinary_op(3); // 삼항 연산자
//    bit_op(); // 비트 연산자
//
//    // statement
//    condition(1); // 조건문
//    loop(); // 반복문
//
//    // var
//    variables();
//    variables();
//    printf("%d\n", ++extern_var);
//    variables();
//
//    // pointer
//    pointer();
//    smart_ptr();
//
//    // collections
//    test_array(); // 배열
//    test_struct(); // 구조체
//    test_string(); // 문자열
//
//    // 동적할당
//    dynamic_alloc();
//
//    // collections
//    test_vector(); // 가변 배열
//    test_linked_list(); // 연결 리스트
//    test_tree(); // 트리
//
//    // 클래스
//    base_cls();
//    inherit();
//
//    // try ~ catch
//    exception();
//
//    // cast
//    cast();

    // thread
//    multi_threading();
//    consumer_producer();

//    std::ofstream oFile = std::ofstream("file.txt");
//    oFile.write("sdfsdfsdf", 100);
//    oFile.close();
//
//    char a;
//    std::ifstream iFile = std::ifstream("file.txt");
//    iFile.read(&a, 100);

    return 0;
}
