#include "sdlJeu.h"
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv) {
	sdlJeu sj;
    srand(time(NULL));
	sj.sdlBoucle();
	return 0;
}
