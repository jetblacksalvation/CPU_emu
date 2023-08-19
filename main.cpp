#include "Registers/Register.hpp"
//overload indexing operator to take in string, this might help out alot for getting registers because strings tokens, once i finish the tokenizer, 
//could be directly passed to this
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
int main(){
    Registers registers;
    registers.mov("ax", "1");
    registers.add("ax","225");
    std::cout<<registers;
}

