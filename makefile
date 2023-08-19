LL = Registers/Register.cpp


run:
	g++ main.cpp ${LL}
	./a.out
clean:
	rm -f a.out