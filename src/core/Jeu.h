#ifndef _JEU_H
#define _JEU_H

#include <vector>
#include "Grille.h"

using namespace std;

enum State {menu, start, playing, won, egalite};

enum Mode {multi, solo};

class Jeu {

private :
	
	vector<Jeton> jetons;
	bool jetonSelected;
	Grille grid;
	int winningCondition;
	State state;
	Mode mode;
	int joueur;
	int countPose;

public :

	Jeu();

	~Jeu();

	Jeton getJeton(int index);

	Grille getGrid();

	bool selectJeton(int index);

	bool poseJeton(int x, int y);

	int getSelected();

	bool getJetonSelected();

	int getWinningCondition();

	void setWinningCondition(int wc);

	State getState();

	void setState(State s);

	Mode getMode();

	void setMode(Mode m);

	int getJoueur();

};


#endif
