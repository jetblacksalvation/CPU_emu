#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <string>
#include <algorithm>    // std::all_of
#include <string>
#include <fstream>

typedef int8_t BYTE;
typedef int16_t DBYTE;
#ifdef OVERFLOW
#undef OVERFLOW
#endif
#ifndef uint
typedef uint8_t uint;
#endif