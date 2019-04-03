#ifndef _GRILLE_H
#define _GRILLE_H

#include "Jeton.h"

using namespace std;

class Grille {

private :
	
	Jeton grid[4][4];
	int lastPlayedX;
	int lastPlayedY;
	bool gridWin[4][4];

public :
	
	Grille();
	Grille(Grille const & grille);
	~Grille();
	int getLastPlayedX() const;
	int getLastPlayedY() const;
	void setJeton(int x, int y, Jeton j);
	Jeton getJeton(int x, int y) const;
	Jeton* getRefJeton(int x, int y);
	bool getWin(int x, int y) const;
	bool hasWon(int winningCondition);
	bool win1();
	bool win2();
	bool win3();
	bool win4();
	bool win5();
	bool win6();
	bool win7();
	bool checkForme(int x1, int y1, int x2, int y2, int x3, int y3);

};


#endif
