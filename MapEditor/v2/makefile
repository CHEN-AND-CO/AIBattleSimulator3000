CFLAGS = -Wall -pedantic -std=c++14
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


SRC = $(wildcard *.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addsuffix .o, $(NOM))


all: editmap

remake: clean editmap

editmap : $(OBJ)
	g++ $(OBJ) $(LDFLAGS) -o $@ 

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

clean:
	rm editmap *.o *.gch -f

clear:
	rm *.o *.gch -f

run: editmap
	./editmap