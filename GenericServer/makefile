CFLAGS = -g -Wall -pedantic -std=c++17

LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system

all: server.out client.out

remake: clean server.out client.out

server.out : obj/server.o obj/GenericServer.o obj/cmdFormat.o
	g++-7  obj/server.o obj/GenericServer.o obj/cmdFormat.o $(LDFLAGS) -o server.out

client.out : obj/client.o obj/GenericClient.o obj/cmdFormat.o
	g++-7  obj/client.o obj/GenericClient.o obj/cmdFormat.o $(LDFLAGS) -o client.out

obj/client.o: src/client.cpp src/cmdFormat.cpp src/GenericClient.cpp
	g++-7 -c src/client.cpp -Iinclude -o obj/client.o $(CFLAGS)

obj/server.o: src/server.cpp src/cmdFormat.cpp src/GenericServer.cpp
	g++-7 -c src/server.cpp -Iinclude -o obj/server.o $(CFLAGS)

obj/GenericClient.o: src/GenericClient.cpp
	g++-7 -c src/GenericClient.cpp -Iinclude -o obj/GenericClient.o $(CFLAGS)

obj/GenericServer.o: src/GenericServer.cpp
	g++-7 -c src/GenericServer.cpp -Iinclude -o obj/GenericServer.o $(CFLAGS)

obj/cmdFormat.o: src/cmdFormat.cpp
	g++-7 -c src/cmdFormat.cpp -Iinclude -o obj/cmdFormat.o $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch -f

clear:clean

push: clean pull
	git add .
	git commit
	git push

pull:
	git pull

install:
	sudo apt install libsfml_dev lua5.3 liblua5.3-0 liblua5.3-0-dev
