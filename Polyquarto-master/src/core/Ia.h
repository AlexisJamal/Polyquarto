#ifndef _IA_H
#define _IA_H

#include "Jeu.h"

using namespace std;

class Ia {

private :

public :

	static void jouer(Jeu & j);
	static int evaluation (Jeu & jeu);
	static int MinMax (Jeu & jeu , int profondeur, bool opposant);

};


#endif
