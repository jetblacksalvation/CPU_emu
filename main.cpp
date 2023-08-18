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
char const* FLAGS_NAME[] = {
    "OVERFLOW",
    "CARRY",
    "BZERO",
    "LZERO",
    "ZERO",//<-- last compare flag
    "INT_DIS"//<-- interrupt disable flag
};
struct Registers{
    //system
    Registers(){
        clearFlags();
    }
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
    //to be implemented ...
    DBYTE getBytes(std::string&& reg){
        getBytes(reg);
    }
    DBYTE getBytes(std::string& str){
        DBYTE reg;
        if(str == "pc")return pc;
        if(str =="ip") return ip;
        if(str == "sp") return sp;
        if(str =="ax") return ax;
        if(str=="bx") return bx;
        if (str =="cx") return cx;
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
        //
        return tReg;//treg is for literal values...
        //... AST will switch to different function when declaring memory ... or maybe continue to use this?
        //not sure if it's legal to do" times 10 db pc "or something ...
    }
    void mov(std::string&& reg1, std::string&& reg2){

        mov(reg1,reg2);
        // auto & r2 = (*this)[reg2];
        // r2 = temp;
    }
    void mov(std::string&reg1, std::string&reg2){

        this->operator[](reg1);
        DBYTE temp = (*this)[reg1];
        auto& r1 =  (*this)[reg1] ;
        r1= (*this)[reg2];
        // auto & r2 = (*this)[reg2];
        // r2 = temp;
    }
    void cmp(std::string&& reg1, std::string&& reg2){
        cmp(reg1,reg2);
    };
    void cmp(std::string& reg1, std::string& reg2){
        auto result = (*this)[reg1]-(*this)[reg2];
        clearCmpFlags();
        if(result <0){
            FLAGS[uint(FLAGS_NUM::LZERO)] = 1;
        }
        if(result ==0){
            FLAGS[uint(FLAGS_NUM::ZERO)] = 1;
        }
        if(result >0){
            FLAGS[uint(FLAGS_NUM::BZERO)] = 1;

        }
    };
    void add(std::string&& reg1, std::string&& reg2){
        add(reg1,reg2);
        // r2 = temp;
    }
    void add(std::string& reg1, std::string& reg2){
        clearCmpFlags();
        
        this->operator[](reg1);
        DBYTE temp = (*this)[reg1];
        auto& r1 =  (*this)[reg1] ;

        r1 += (*this)[reg2];
        cmp(reg1,reg2);

        if(std::int64_t(r1)> 32767|| std::int64_t(r1) <-32767){//<--- does not work...
            FLAGS[uint(FLAGS_NUM::OVERFLOW)] = 1;
        }
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
        os<<FLAGS_NAME[x]<<":"<<std::to_string(registe.FLAGS[x])<<"\n";
    }
    return os;
}
//overload indexing operator to take in string, this might help out alot for getting registers because strings tokens, once i finish the tokenizer, 
//could be directly passed to this

int main(){
    Registers registers;
    registers.mov("ax", "1");
    registers.add("ax","225");
    std::cout<<registers;
}
