#pragma once

#include <iostream>

template <typename T>
class Test {
public:
    virtual bool TEST(T value, T expected) = 0;
};