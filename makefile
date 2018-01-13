CFLAGS = -g -Wall -pedantic -std=c++17

LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))
UNITOBJ = 

all: battleSim.out

remake: clean battleSim.out

batlleSim.out : $(OBJ)
	g++-7 obj/* $(LDFLAGS) -o $@ 

obj/%.o: src/%.cpp
	g++-7 -c $< -Iinclude -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch src/*~ include/*~ *~ -f

clear:clean

push:
	git add .
	git commit
	git push

pull:
	git pull

#unitTest: clean $(UNITOBJ)
#	g++ -obj/
