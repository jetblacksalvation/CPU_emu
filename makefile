LL = Registers/Register.cpp Lexer/Tokenzier.cpp
run:
	g++ main.cpp ${LL}
	./a.out
clean:
	rm -f a.out