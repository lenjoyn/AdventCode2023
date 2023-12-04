all:day2 day2.o
day2.o:day2.cxx
	g++ -std=c++14 -c day2.cxx -o day2.o
day2:day2.o
	g++ day2.o -o day2 -I .
clean:
	rm day2 day2.o
