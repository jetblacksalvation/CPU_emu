#include "Registers/Register.hpp"
#include "Lexer/Tokenizer.hpp"
//overload indexing operator to take in string, this might help out alot for getting registers because strings tokens, once i finish the tokenizer, 
//could be directly passed to this

std::ostream& operator<<(std::ostream& os, Registers _register);


int main(int argc, char* vargs[]){
    std::fstream fileInput;
    fileInput.open(vargs[1]);
    auto code = getCode(fileInput);
    Registers registers;
    for (DBYTE& ip =registers.ip; ip <code.size(); ip++){
        //add evaluate code here...
        registers.evaluateTokens(code[ip]);
        // for(auto str : code[ip]){//working so far...
        //     std::cout<<str;
        // }
        // std::cout<<'\n';
        //change ip depending on evaluate...
    }


    // std::cout<<registers;
}


std::ostream& operator<<(std::ostream& os, Registers _register){
    os<<"pc:"<<_register.pc<<"\n";
    os<<"ip:"<<_register.ip<<"\n";
    os<<"sp:"<<_register.sp<<"\n";
    os<<"ax:"<<_register.ax<<"\n";
    os<<"bx:"<<_register.bx<<"\n";
    os<<"cx:"<<_register.cx<<"\n";
    for(int x = 0; x< uint(FLAGS_NUM::INT_DIS)+1; x++){
        os<<FLAGS_NAME[x]<<":"<<std::to_string(_register.FLAGS[x])<<"\n";
    }
    return os;
}