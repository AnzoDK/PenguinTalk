CXX:=g++
CXX_COMMON_FLAGS:= -I./include -I./include/Common
SERVER_FLAGS:= -pthread -std=c++17 -D __linux__ -I./StoopidDB $(CXX_COMMON_FLAGS)
CLIENT_FLAGS:= -pthread -std=c++17 -D __linux__ $(CXX_COMMON_FLAGS)
SERVER_LINK:= -lpthread -lssl -lcrypto
CLIENT_LINK:= -lpthread -lssl -lcrypto
SERVER_OUT:=server.out
CLIENT_OUT:=client.out
ARCH_INSTALL:=0
CLIENT_DIR:=./src/ClientTS
release:
	make clean
	make get_DB_optimized
	make common COMMON_FLAGS+=-O2
	make client CLIENT_FLAGS+=-O2
	make server SERVER_FLAGS+=-O2
debug:
	make clean
	make get_DB_debug
	make common COMMON_FLAGS+=-g3
	make client CLIENT_FLAGS+=-g3
	make server SERVER_FLAGS+=-g3
client:
	# $(CXX) $(CLIENT_FLAGS) ./src/client.cpp -o $(CLIENT_OUT) $(CLIENT_LINK)
	cd $(CLIENT_DIR)/ && ng build

common:
	$(CXX) -c $(COMMON_FLAGS_FLAGS) ./src/Common/EncryptionManager/encryptionmanager.cpp -o encryptionmanager.cpp.o
	$(CXX) -c $(COMMON_FLAGS) ./src/Common/EncryptionManager/RSA.cpp -o RSA.cpp.o

server:
# Compiling the server source file
	$(CXX) -c $(SERVER_FLAGS) ./src/Server/server_main.cpp -o server_main.cpp.o

# Linking all the object files to create the server executable
	$(CXX) $(SERVER_FLAGS) encryptionmanager.cpp.o RSA.cpp.o server_main.cpp.o -o $(SERVER_OUT) $(SERVER_LINK)

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
