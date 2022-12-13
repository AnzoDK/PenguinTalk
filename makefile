CXX:=g++
CXX_COMMON_FLAGS:= -I./include -I./include/Common
SERVER_FLAGS:= -pthread -std=c++17 -D __linux__ -I./StoopidDB $(CXX_COMMON_FLAGS)
CLIENT_FLAGS:= -pthread -std=c++17 -D __linux__ $(CXX_COMMON_FLAGS)
SERVER_LINK:= -lpthread -lssl -lcrypto
CLIENT_LINK:= -lpthread -lssl -lcrypto
SERVER_OUT:=server.out
CLIENT_OUT:=client.out
ARCH_INSTALL:=0
release:
	make clean
	make get_DB_optimized
	make client CLIENT_FLAGS+=-O2
	make server SERVER_FLAGS+=-O2
debug:
	make clean
	make get_DB_debug
	make client CLIENT_FLAGS+=-g3
	make server SERVER_FLAGS+=-g3
client:
	$(CXX) $(CLIENT_FLAGS) ./src/client.cpp -o $(CLIENT_OUT) $(CLIENT_LINK)
server:
	$(CXX) $(SERVER_FLAGS) ./src/server.cpp -o $(SERVER_OUT) $(SERVER_LINK)
clean:
	make removeStoopidDB
	-rm *.out
	-rm *.sdb
	-rm *.pem
removeStoopidDB:
	-rm -rf ./StoopidDB
get_DB_debug:
	./getDB.sh --debug --install $(ARCH_INSTALL)
get_DB_optimized:
	./getDB.sh --optimize --install $(ARCH_INSTALL)
