#ifndef _IA_H
#define _IA_H

#include "Jeu.h"

using namespace std;

class Ia {

private :

public :

	static void jouer(Jeu & j);
	static int evaluation (Jeu & jeu);
	static int MinMax (Jeu* jeu , int profondeur, bool opposant);
	static int win1(Grille grid);
	static int win2(Grille grid);
	static int win3(Grille grid);
	static int win4(Grille grid);
	static int win5(Grille grid);
	static int win6(Grille grid);
	static int win7(Grille grid);
	static int checkForme(Grille grid, int x1, int y1, int x2, int y2, int x3, int y3);

};


#endif
