#include "interface.h"
#include <iostream>

// 인터페이스
class ICamera {
public:
    virtual void take() = 0;
};

class People {
public:
    void useCamera(ICamera* c) { c->take(); }
};

class Camera : public ICamera {
public:
    void take() override {
        std::cout << "take picture with Camera" << std::endl;
    }
};

class HDCamera : public ICamera {
public:
    void take() override {
        std::cout << "take picture with HDCamera" << std::endl;
    }
};

void interface() {
    People p = People();
    Camera c1 = Camera();
    HDCamera c2 = HDCamera();

    p.useCamera(&c1);
    p.useCamera(&c2);
}
