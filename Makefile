#檔案開始




bin/main: main.o graph.o getpart.o dfs.o
	g++ main.o graph.o getpart.o dfs.o -o test
	
bin/main.o: main.cpp
	g++ main.cpp -c
bin/graph.o: graph.cpp graph.h
	g++ graph.cpp graph.h -c
bin/getpart.o: getpart.cpp getpart.h
	g++ getpart.cpp getpart.h -c
bin/dfs.o: dfs.cpp dfs.h
	g++ dfs.cpp dfs.h -c



	
clean: 
	rm -rf bin/*