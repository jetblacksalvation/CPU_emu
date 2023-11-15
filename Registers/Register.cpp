#include "Register.hpp"


//system
void Registers::evaluateTokens(std::vector<std::string> tokens){
    if(tokens[0] == "mov"){
        //expect tokens[0] = 'mov'  nxt 'regsiter' nxt == ',' nxt 'value' or 'register'
        if(tokens[2] == ","){
            mov(tokens[1], tokens[3]);
        }
    }
    if(tokens[0] == "cmp"){
        if(tokens[2] == ","){
            cmp(tokens[1], tokens[3]);
        }    
    }
    if(tokens[0] == "preg"){
        //print register
        std::cout<<(char)(*this)[tokens[1]];
    }
    if(tokens[0] == "print"){
        std::cout<<"pc:"<<pc<<"\n";
        std::cout<<"ip:"<<ip<<"\n";
        std::cout<<"sp:"<<sp<<"\n";
        std::cout<<"ax:"<<ax<<"\n";
        std::cout<<"bx:"<<bx<<"\n";
        std::cout<<"cx:"<<cx<<"\n";
        for(int x = 0; x< uint(FLAGS_NUM::INT_DIS)+1; x++){
            std::cout<<FLAGS_NAME[x]<<":"<<std::to_string(FLAGS[x])<<"\n";
        }
    }
    if(tokens[1] == ":" && tokens.size() ==2){
        labelHash.insert_or_assign(tokens[0], ip);
        //lable creation...
        //make lable hash table...
    }
    if(tokens[0] == "jmp" && tokens.size() ==2){
        if (labelHash.find(tokens[1]) != labelHash.end()){
            ip = (*labelHash.find(tokens[1])).second;
        }

    }
    if(tokens[0] == "jz"&& tokens.size() ==2){

        if (labelHash.find(tokens[1]) != labelHash.end()&& FLAGS[uint(FLAGS_NUM::ZERO)]){
            ip = (*labelHash.find(tokens[1])).second;
        }
    }
};

Registers::Registers(){
    clearFlags();
}

void Registers::clearFlags(){
    for(int x = 0; x< uint(FLAGS_NUM::INT_DIS)+1; x++){
        FLAGS[x] = 0;
    }
}
void Registers::clearCmpFlags(){
    //anything <= zero flag = cmp flags
    for(int x = 0; x< uint(FLAGS_NUM::ZERO)+1; x++){
        FLAGS[x] = 0;
    }
}
//to be implemented ...
DBYTE& Registers::getBytes(std::string&& reg){
    return getBytes(reg);
}
DBYTE& Registers::getBytes(std::string& str){
    DBYTE reg;
    if(str == "pc")return pc;
    if(str =="ip") return ip;
    if(str == "sp") return sp;
    if(str =="ax") return ax;
    if(str=="bx") return bx;
    if (str =="cx") return cx;

    return reg;
}
DBYTE& Registers::operator[](std::string&& str){
    return (*this)[str];
    
}
DBYTE& Registers::operator[](std::string& str){
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
void Registers::mov(std::string&& reg1, std::string&& reg2){

    mov(reg1,reg2);
    // auto & r2 = (*this)[reg2];
    // r2 = temp;
}
void Registers::mov(std::string&reg1, std::string&reg2){

    this->operator[](reg1);
    DBYTE temp = (*this)[reg1];
    auto& r1 =  (*this)[reg1] ;
    r1= (*this)[reg2];
    // auto & r2 = (*this)[reg2];
    // r2 = temp;
}
void Registers::cmp(std::string&& reg1, std::string&& reg2){
    cmp(reg1,reg2);
};
void Registers::cmp(std::string& reg1, std::string& reg2){
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
void Registers::add(std::string&& reg1, std::string&& reg2){
    add(reg1,reg2);
    // r2 = temp;
}
void Registers::add(std::string& reg1, std::string& reg2){
    clearCmpFlags();
    
    this->operator[](reg1);
    DBYTE temp = (*this)[reg1];
    auto& r1 =  (*this)[reg1] ;

    r1 += (*this)[reg2];
    cmp(reg1,reg2);

    if(int64_t(r1)> 32767|| int64_t(r1) <-32767){//<--- does not work...
        FLAGS[uint(FLAGS_NUM::OVERFLOW)] = 1;
    }
}
