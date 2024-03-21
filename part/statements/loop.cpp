#include "statements.h"
#include <iostream>

void loop() {
    // for
    for (int i = 0; i < 3; i++) {
        std::cout << i << std::endl;
    }

    int i;

    // while
    i = 0;
    while (i++ < 3) {
        std::cout << i << std::endl;
    }

    // do-while
    i = 0;
    do {
        std::cout << i << std::endl;
    } while (i++ < 3);
}

