#檔案開始

main: main.o graph.o getpart.o dfs.o
	g++ main.o graph.o getpart.o dfs.o -o test
	
main.o: main.cpp
	g++ main.cpp -c
graph.o: graph.cpp graph.h
	g++ graph.cpp graph.h -c
getpart.o: getpart.cpp getpart.h
	g++ getpart.cpp getpart.h -c
dfs.o: dfs.cpp dfs.h
	g++ dfs.cpp dfs.h -c



	
clean: 
	rm -rf main.o graph.o getpart.o dfs.o