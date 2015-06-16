#檔案開始

main: main.o graph.o
	g++ main.o graph.o -o test
	
main.o: main.cpp
	g++ main.cpp -c
graph.o: graph.cpp
	g++ graph.cpp graph.h -c
	
clean: 
	rm -rf main.o graph.o