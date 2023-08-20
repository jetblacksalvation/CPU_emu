LL = Registers/Register.cpp Lexer/Tokenzier.cpp
OP = -w -std=c++20
run:
	g++ main.cpp ${LL} ${OP} 
	./a.out test.asm
clean:
	rm -f a.out