#以下部分為湯智帆所做
bin/main: main.o graph.o getpart.o
	g++ -g -O2 main.o graph.o getpart.o -o bin/final
	
main.o: src/main.cpp
	g++ -g -O2 src/main.cpp -c 
graph.o: src/graph.cpp src/graph.h
	g++ -g -O2 src/graph.cpp -c 
getpart.o: src/getpart.cpp src/getpart.h
	g++ -g -O2 src/getpart.cpp -c 



	
clean: 
	rm -rf bin/* src/*.gch *.o
