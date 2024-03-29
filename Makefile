all: createDir PolyQuarto.out deplaceObj

UNAME_S = $(shell uname)

ifeq ($(UNAME_S),Darwin)
	DIR_SDL = -I/usr/local/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_image
endif

ifeq ($(UNAME_S), Linux)
	DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_image
endif


PolyQuarto.out: main_sdl.o sdlJeu.o Jeu.o Jeton.o Grille.o Ia.o
	g++ -g main_sdl.o sdlJeu.o Jeu.o Jeton.o Grille.o Ia.o -o bin/PolyQuarto.out $(LIBS_SDL)


main_sdl.o: src/sdl2/sdlJeu.h src/sdl2/main_sdl.cpp
	g++ -g -Wall -c src/sdl2/main_sdl.cpp $(DIR_SDL)

sdlJeu.o: src/sdl2/sdlJeu.h src/sdl2/sdlJeu.cpp
	g++ -g -Wall -c src/sdl2/sdlJeu.cpp $(DIR_SDL)

Jeu.o: src/core/Jeu.h src/core/Jeu.cpp
	g++ -g -Wall -c src/core/Jeu.cpp

Jeton.o: src/core/Jeton.h src/core/Jeton.cpp
	g++ -g -Wall -c src/core/Jeton.cpp

Grille.o: src/core/Grille.h src/core/Grille.cpp
	g++ -g -Wall -c src/core/Grille.cpp

Ia.o: src/core/Ia.h src/core/Ia.cpp
	g++ -g -Wall -c src/core/Ia.cpp

clean:
	rm obj/*.o

veryclean: clean
	rm bin/*.out

createDir:
	mkdir -p obj
	mkdir -p bin

deplaceObj:
	mv *.o obj

run: all
	./bin/PolyQuarto.out
