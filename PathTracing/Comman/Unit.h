#pragma once

#include <iostream>

void Clear()
{
    std::cout << "\x1B[2J\x1B[H";
}