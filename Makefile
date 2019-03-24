all: PolyQuarto.out deplaceObj

#UNAME_S = $(shell uname)

#ifeq ($(UNAME_S),Darwin)
#	DIR_SDL = -I/usr/local/include/SDL2
#	LIBS_SDL = -lSDL2 -lSDL2_image
#endif

#ifeq ($(UNAME_S), Linux)
#	DIR_SDL = -I/usr/include/SDL2
#	LIBS_SDL = -lSDL2 -lSDL2_image
#endif

DIR_SDL = -ISDL2
LIBS_SDL = -lSDL2 -lSDL2_image


PolyQuarto.out: main_sdl.o sdlJeu.o Jeu.o Jeton.o Grille.o
	g++ -g main_sdl.o sdlJeu.o Jeu.o Jeton.o Grille.o -o bin/PolyQuarto.out $(LIBS_SDL)


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

clean:
	rm obj/*.o

veryclean: clean
	rm bin/*.out


deplaceObj:
	mv *.o obj

run: all
	./bin/PolyQuarto.out
