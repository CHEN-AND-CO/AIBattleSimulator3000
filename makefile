CFLAGS = -g -Wall -pedantic -std=c++17

LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -llua -ldl

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))
UNITOBJ = 

all: simulateurPopulation.out

remake: clean simulateurPopulation.out

simulateurPopulation.out : $(OBJ)
	g++-7 obj/* $(LDFLAGS) -o $@ 

obj/%.o: src/%.cpp
	g++-7 -c $< -Iinclude -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch src/*~ include/*~ -f

clear:
	rm obj/*.o *.gch -f

#unitTest: clean $(UNITOBJ)
#	g++ -obj/
