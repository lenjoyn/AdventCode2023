all:day1 day1.o
day1.o:day1.cxx
	g++ -std=c++14 -c day1.cxx -o day1.o
day1:day1.o
	g++ day1.o -o day1 -I .
clean:
	rm day1 day1.o
