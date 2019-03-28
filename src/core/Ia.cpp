#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Ia.h"

using namespace std;

void Ia::jouer(Jeu & j) {
	srand (time(NULL));
	int x, y, i;

	if(j.getJoueur() == 1) {
		x = rand() % 4;
		y = rand() % 4;

		while(!j.poseJeton(x,y)) {
			x = rand() % 4;
			y = rand() % 4;
		}
	}
	else {
		i = rand() % 16;

		while(!j.selectJeton(i)) {
			i = rand() % 16;
		}
	}
}