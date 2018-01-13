CFLAGS = -g -Wall -pedantic -std=c++17

LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -llua -ldl

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))
UNITOBJ = 

all: battleSimS.out

remake: clean battleSimS.out

battleSimS.out : $(OBJ)
	g++-7 obj/* $(LDFLAGS) -o $@ 

obj/%.o: src/%.cpp
	g++-7 -c $< -Iinclude -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch src/*~ include/*~ *~  *# -f

clear:clean

push: clean pull
	git add .
	git commit
	git push

pull:
	git pull

install:
	sudo apt install libsfml_dev lua5.3 liblua5.3-0 liblua5.3-0-dev
