#pragma once
#include "Object.h"

class Platform : public df::Object {
private:
    Platform();
public:
    ~Platform();

    int eventHandler(const df::Event* p_e);
};

