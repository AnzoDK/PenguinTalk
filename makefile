CXX:=g++
SERVER_FLAGS:= -pthread -std=c++17 -D __linux__
CLIENT_FLAGS:= -pthread -std=c++17 -D __linux__´
SERVER_LINK:= -lpthread
CLIENT_LINK:= -lpthread
SERVER_OUT:=server.out
CLIENT_OUT:=client.out

release:
	make clean
	#make client CLIENT_FLAGS+=-O2
	make server SERVER_FLAGS+=-O2
debug:
	make clean
	#make client CLIENT_FLAGS+=-g3
	make server SERVER_FLAGS+=-g3
client:
	$(CXX) $(CLIENT_FLAGS) ./src/client.cpp -o $(CLIENT_OUT) $(CLIENT_LINK)
server:
	$(CXX) $(SERVER_FLAGS) ./src/server.cpp -o $(SERVER_OUT) $(SERVER_LINK)
clean:
	-rm *.out
