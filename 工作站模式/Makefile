#檔案開始




bin/main: main.o graph.o getpart.o dfs.o
	g++ -O2 main.o graph.o getpart.o dfs.o -o bin/test
	
main.o: src/main.cpp
	g++ -O2 src/main.cpp -c 
graph.o: src/graph.cpp src/graph.h
	g++ -O2 src/graph.cpp src/graph.h -c 
getpart.o: src/getpart.cpp src/getpart.h
	g++ -O2 src/getpart.cpp src/getpart.h -c 
dfs.o: src/dfs.cpp src/dfs.h
	g++ -O2 src/dfs.cpp src/dfs.h -c 



	
clean: 
	rm -rf bin/* src/*.gch *.o
