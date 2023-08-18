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
char * FLAGS_NAME[] = {
        "OVERFLOW",
    "CARRY",
    "BZERO",
    "LZERO",
    "ZERO",//<-- last compare flag
    "INT_DIS"//<-- interrupt disable flag
};
struct Registers{
    //system
    DBYTE pc = 0;//next expected op code!
    DBYTE ip = 0;//instruction pointer
    DBYTE sp = 0;//stack pointer!
    //arithm---
    DBYTE ax = 0;//accumilator, the only
    DBYTE bx = 0;//base
    DBYTE cx = 0;//counter

    DBYTE tReg = 0;// return the string casted to int when string is not a register...
    BYTE FLAGS[uint(FLAGS_NUM::INT_DIS)+1];//<-- setting flag equal to length of largest enum value...
    void clearFlags(){
        for(int x = 0; x< uint(FLAGS_NUM::INT_DIS)+1; x++){
            FLAGS[x] = 0;
        }
    }
    void clearCmpFlags(){
        //anything <= zero flag = cmp flags
        for(int x = 0; x< uint(FLAGS_NUM::ZERO)+1; x++){
            FLAGS[x] = 0;
        }
    }

    DBYTE& operator[](std::string&& str){
        return (*this)[str];
        
    }
    DBYTE& operator[](std::string& str){
        if(str == "pc")return pc;
        if(str =="ip") return ip;
        if(str == "sp") return sp;
        if(str =="ax") return ax;
        if(str=="bx") return bx;
        if (str =="cx") return cx;

        tReg = std::stoi(str);
        return tReg;//treg is for literal values...
        //... AST will switch to different function when declaring memory ... or maybe continue to use this?
        //not sure if it's legal to do" times 10 db pc "or something ...
    }
    void mov(std::string&& reg1, std::string&& reg2){
        this->operator[](reg1);
        DBYTE temp = (*this)[reg1];
        auto& r1 =  (*this)[reg1] ;
        r1= (*this)[reg2];
        auto & r2 = (*this)[reg2];
        r2 = temp;
    }
    
};
std::ostream& operator<<(std::ostream& os, Registers registe){
    os<<"pc:"<<registe.pc<<"\n";
    os<<"ip:"<<registe.ip<<"\n";
    os<<"sp:"<<registe.sp<<"\n";
    os<<"ax:"<<registe.ax<<"\n";
    os<<"bx:"<<registe.bx<<"\n";
    os<<"cx:"<<registe.cx<<"\n";
    for(int x = 0; x< uint(FLAGS_NUM::INT_DIS)+1; x++){
    os<<FLAGS_NAME[x]<<"\n";
    }

}
//overload indexing operator to take in string, this might help out alot for getting registers because strings tokens, once i finish the tokenizer, 
//could be directly passed to this

int main(){
    Registers registers;
    registers.mov("ax", "10");
    std::cout<<registers;
}

