all:main main.o
main.o:main.cxx
	g++ -std=c++14 -c main.cxx -o main.o
main:main.o
	g++ main.o -o main -I .
clean:
	rm main main.o
