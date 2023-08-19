#pragma once
#include <iostream>
typedef std::int8_t BYTE;
typedef std::int16_t DBYTE;
enum class FLAGS_NUM:BYTE{
    OVERFLOW,
    CARRY,
    BZERO,
    LZERO,
    ZERO,//<-- last compare flag
    INT_DIS//<-- interrupt disable flag
};
static char const* FLAGS_NAME[] = {
    "OVERFLOW",
    "CARRY",
    "BZERO",
    "LZERO",
    "ZERO",//<-- last compare flag
    "INT_DIS"//<-- interrupt disable flag
};
struct Registers{
    DBYTE pc = 0;//next expected op code!
    DBYTE ip = 0;//instruction pointer
    DBYTE sp = 0;//stack pointer!
    //arithm---
    DBYTE ax = 0;//accumilator, the only
    DBYTE bx = 0;//base
    DBYTE cx = 0;//counter

    DBYTE tReg = 0;// return the string casted to int when string is not a register...
    BYTE FLAGS[uint(FLAGS_NUM::INT_DIS)+1];//<-- setting flag equal to length of largest enum value...    
    Registers();
    void clearFlags();
    void clearCmpFlags();
    DBYTE& getBytes(std::string&& reg);
    DBYTE& getBytes(std::string& reg);
    DBYTE& operator[](std::string&& str);
    DBYTE& operator[](std::string& str);
    void mov(std::string&& reg1, std::string&& reg2);
    void mov(std::string&reg1, std::string&reg2);
    void cmp(std::string&& reg1, std::string&& reg2);
    void cmp(std::string& reg1, std::string& reg2);
    void add(std::string&& reg1, std::string&& reg2);
    void add(std::string& reg1, std::string& reg2);
};
