LL = Registers/Register.cpp Lexer/Tokenzier.cpp
OP = -w -std=c++20
build:
	g++ main.cpp ${LL} ${OP} 
run:
	./a.out test.asm
clean:
	rm -f a.out