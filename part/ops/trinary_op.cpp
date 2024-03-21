#include <iostream>
#include "ops.h"


void trinary_op(int i) {
    std::string str;

    i > 0 ? str = "positive" : str = "negative";

    std::cout << str << std::endl;
}
