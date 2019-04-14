#include <iostream>
#include "Grille.h"

using namespace std;

Grille::Grille () {
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) {
			grid[i][j] = Jeton();
			gridWin[i][j] = false;
		}

}

Grille::Grille(Grille const & grille) {
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) {
			grid[i][j] = Jeton(grille.getJeton(i,j));
			gridWin[i][j] = grille.getWin(i,j);
		}

	lastPlayedY = grille.getLastPlayedY();
	lastPlayedX = grille.getLastPlayedX();
}

Grille::~Grille() {
}

int Grille::getLastPlayedX() const {
	return lastPlayedX;
}

int Grille::getLastPlayedY() const {
	return lastPlayedY;
}

void Grille::setJeton(int x, int y, Jeton j) {
	grid[x][y] = j;
	lastPlayedX = x;
	lastPlayedY = y;
}

Jeton Grille::getJeton(int x, int y) const {
	return grid[x][y];
}

Jeton* Grille::getRefJeton(int x, int y) {
	return &grid[x][y];
}

bool Grille::getWin(int x, int y) const {
	return gridWin[x][y];
}

bool Grille::hasWon(int winningCondition) {

	bool res = false;

	switch(winningCondition) {
		case 1: 
			res = win1();
			break;
		case 2: 
			res = win2();
			break;
		case 3: 
			res = win3();
			break;
		case 4: 
			res = win4();
			break;
		case 5: 
			res = win5();
			break;
		case 6: 
			res = win6();
			break;
		case 7: 
			res = win7();
			break;
		default: break;
	}

	return res;
}

//  ####
bool Grille::win1() {
	bool res = false;
	int count = 0;
	bool r, c, h, b;
	bool b1 = true, b2 = true, b3 = true, b4 = true;

	// On vérifie la ligne
	for(int i = 0; i < 4; i++) {
		if(grid[i][lastPlayedY].getIsUsed()) {
			count++;
		}
	}
	if(count == 4) {
		r = grid[0][lastPlayedY].getIsRed();
		c = grid[0][lastPlayedY].getIsCircle();
		h = grid[0][lastPlayedY].getIsHoled();
		b = grid[0][lastPlayedY].getIsBig();
		for(int i = 1; i < 4; i++) {
			if(b1 && grid[i][lastPlayedY].getIsRed() != r) {
				b1 = false;
			}
			if(b2 && grid[i][lastPlayedY].getIsCircle() != c) {
				b2 = false;
			}
			if(b3 && grid[i][lastPlayedY].getIsHoled() != h) {
				b3 = false;
			}
			if(b4 && grid[i][lastPlayedY].getIsBig() != b) {
				b4 = false;
			}
		}
		if(b1 || b2 || b3 || b4) {
			res = true;
			for(int i = 0; i < 4; i++) {
				gridWin[i][lastPlayedY] = true;
			}
		}
	}
	if(!res) {
		count = 0;
		b1 = true, b2 = true, b3 = true, b4 = true;
		// On vérifie la colonne
		for(int i = 0; i < 4; i++) {
			if(grid[lastPlayedX][i].getIsUsed()) {
				count++;
			}
		}
		if(count == 4) {
			r = grid[lastPlayedX][0].getIsRed();
			c = grid[lastPlayedX][0].getIsCircle();
			h = grid[lastPlayedX][0].getIsHoled();
			b = grid[lastPlayedX][0].getIsBig();
			for(int i = 1; i < 4; i++) {
				if(b1 && grid[lastPlayedX][i].getIsRed() != r) {
					b1 = false;
				}
				if(b2 && grid[lastPlayedX][i].getIsCircle() != c) {
					b2 = false;
				}
				if(b3 && grid[lastPlayedX][i].getIsHoled() != h) {
					b3 = false;
				}
				if(b4 && grid[lastPlayedX][i].getIsBig() != b) {
					b4 = false;
				}
			}
			if(b1 || b2 || b3 || b4) {
				res = true;
				for(int i = 0; i < 4; i++) {
					gridWin[lastPlayedX][i] = true;
				}
			}
		}
	}

	return res;
}

/* #
   ###  */
bool Grille::win2() {
	bool res = false;

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res = checkForme(0, -1, -1, -1, -2, -1);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 2) {
		res = checkForme(1, 0, 1, -1, 1, -2);
	}
	// bas-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY <= 2) {
		res = checkForme(0, 1, 1, 1, 2, 1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 1) {
		res = checkForme(-1, 0, -1, 1, -1, 2);
	}

	//Place 2
	// haut-gauche
	if(!res && lastPlayedX >= 2 && lastPlayedY <= 2) {
		res = checkForme(0, 1, -1, 0, -2, 0);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 2) {
		res = checkForme(-1, 0, 0, -1, 0, -2);
	}
	// bas-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY >= 1) {
		res = checkForme(0, -1, 1, 0, 2, 0);
	}
	// bas-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 1) {
		res = checkForme(1, 0, 0, 1, 0, 2);
	}

	//Place 3
	// haut-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, 1, 0, 1, 1);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, -1, 0, 1, -1, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(1, 0, -1, 0, -1, -1);
	}
	// bas-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, 1, 0, -1, 1, -1);
	}

	//Place 4
	// haut-gauche
	if(!res && lastPlayedX <= 1 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 2, 0, 2, 1);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 1) {
		res = checkForme(0, 1, 0, 2, -1, 2);
	}
	// bas-droite
	if(!res && lastPlayedX >= 2 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, -2, 0, -2, -1);
	}
	// bas-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 2) {
		res = checkForme(0, -1, 0, -2, 1, -2);
	}

	return res;
}

/*   #
   ### */
bool Grille::win3() {
	bool res = false;

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res = checkForme(-1, 0, -1, -1, -1, -2);
	}
	// haut-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY >= 1) {
		res = checkForme(0, -1, 1, -1, 2, -1);
	}
	// bas-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 1) {
		res = checkForme(1, 0, 1, 1, 1, 2);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 2 && lastPlayedY <= 2) {
		res = checkForme(0, 1, -1, 1, -2, 1);
	}

	//Place 2
	// haut-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 2) {
		res = checkForme(1, 0, 0, -1, 0, -2);
	}
	// haut-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY <= 2) {
		res = checkForme(0, 1, 1, 0, 2, 0);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 1) {
		res = checkForme(-1, 0, 0, 1, 0, 2);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 2 && lastPlayedY >= 1) {
		res = checkForme(0, -1, -1, 0, -2, 0);
	}

	//Place 3
	// haut-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, -1, 0, 1, 1, 1);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(1, 0, -1, 0, -1, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, 1, 0, -1, -1, -1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, 1, 0, 1, -1);
	}

	//Place 4
	// haut-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 1) {
		res = checkForme(0, 1, 0, 2, 1, 2);
	}
	// haut-droite
	if(!res && lastPlayedX >= 2 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, -2, 0, -2, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 2) {
		res = checkForme(0, -1, 0, -2, -1, -2);
	}
	// bas-gauche
	if(!res && lastPlayedX <= 1 && lastPlayedY >= 1) {
		res = checkForme(1, 0, 2, 0, 2, -1);
	}

	return res;
}

/* ##
   ##  */
bool Grille::win4() {
	bool res = false;

	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, 0, -1, -1, -1);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(1, 0, 0, -1, 1, -1);
	}
	// bas-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 0, 1, 1, 1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, 0, 1, -1, 1);
	}

	return res; 
}

/*  ##
   ##  */
bool Grille::win5() {
	bool res = false;

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res = checkForme(0, -1, -1, -1, -1, -2);
	}
	// haut-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY >= 1) {
		res = checkForme(1, 0, 1, -1, 2, -1);
	}
	// bas-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 1) {
		res = checkForme(0, 1, 1, 1, 1, 2);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 2 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, -1, 1, -2, 1);
	}

	//Place 2
	// haut-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, 1, -1, 0, -1, -1);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, 0, -1, 1, -1);
	}
	// bas-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, -1, 1, 0, 1, 1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 0, 1, -1, 1);
	}

	return res;
}

/*  #
   ###  */
bool Grille::win6() {
	bool res = false;

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(0, 1, -1, 1, 1, 1);
	}
	// haut-droite
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, -1, -1, -1, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(0, -1, 1, -1, -1, -1);
	}
	// bas-gauche
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 1, 1, 1, -1);
	}

	//Place 2
	// haut-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(0, -1, -1, 0, 1, 0);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 0, -1, 0, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(0, 1, 1, 0, -1, 0);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, 0, 1, 0, -1);
	}

	//Place 3
	// haut-gauche
	if(!res && lastPlayedX <= 1 && lastPlayedY >= 1) {
		res = checkForme(1, 0, 1, -1, 2, 0);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY <= 1) {
		res = checkForme(0, 1, 1, 1, 0, 2);
	}
	// bas-droite
	if(!res && lastPlayedX >= 2 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, -1, 1, -2, 0);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 2) {
		res = checkForme(0, -1, -1, -1, 0, -2);
	}

	//Place 4
	// haut-gauche
	if(!res && lastPlayedX >= 2 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, -1, -1, -2, 0);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 2) {
		res = checkForme(0, -1, 1, -1, 0, -2);
	}
	// bas-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 1, 1, 2, 0);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 1) {
		res = checkForme(0, 1, -1, 1, 0, -2);
	}

	return res;
}

/* ##
    ##  */
bool Grille::win7() {
	bool res = false;

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res = checkForme(-1, 0, -1, -1, -2, -1);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 2) {
		res = checkForme(0, -1, 1, -1, 1, -2);
	}
	// bas-droite
	if(!res && lastPlayedX <= 1 && lastPlayedY <= 2) {
		res = checkForme(1, 0, 1, 1, 2, 1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY <= 1) {
		res = checkForme(0, 1, -1, 1, -1, 2);
	}

	//Place 2
	// haut-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res = checkForme(1, 0, 0, -1, -1, -1);
	}
	// haut-droite
	if(!res && lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, -1, 1, 0, 1, 1);
	}
	// bas-droite
	if(!res && lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res = checkForme(-1, 0, 0, 1, 1, 1);
	}
	// bas-gauche
	if(!res && lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res = checkForme(0, -1, -1, 0, -1, 1);
	}

	return res;
}

bool Grille::checkForme(int x1, int y1, int x2, int y2, int x3, int y3) {
	bool res = false;
	bool quit = false;
	bool r, c, h, b;
	bool b1 = true, b2 = true, b3 = true, b4 = true;
	Jeton carre[3];

	r = grid[lastPlayedX][lastPlayedY].getIsRed();
	c = grid[lastPlayedX][lastPlayedY].getIsCircle();
	h = grid[lastPlayedX][lastPlayedY].getIsHoled();
	b = grid[lastPlayedX][lastPlayedY].getIsBig();

	carre[0] = grid[lastPlayedX+x1][lastPlayedY+y1];
	carre[1] = grid[lastPlayedX+x2][lastPlayedY+y2];
	carre[2] = grid[lastPlayedX+x3][lastPlayedY+y3];

	for(int i = 0; i < 3 && !quit; i++) {
		if(carre[i].getIsUsed()) {
			if(b1 && carre[i].getIsRed() != r) {
				b1 = false;
			}
			if(b2 && carre[i].getIsCircle() != c) {
				b2 = false;
			}
			if(b3 && carre[i].getIsHoled() != h) {
				b3 = false;
			}
			if(b4 && carre[i].getIsBig() != b) {
				b4 = false;
			}
		}
		else {
			b1 = false;
			b2 = false;
			b3 = false;
			b4 = false;
			quit = true;
		}
	}
	if(b1 || b2 || b3 || b4) {
		res = true;
		gridWin[lastPlayedX][lastPlayedY] = true;
		gridWin[lastPlayedX+x1][lastPlayedY+y1] = true;
		gridWin[lastPlayedX+x2][lastPlayedY+y2] = true;
		gridWin[lastPlayedX+x3][lastPlayedY+y3] = true;
	}

	return res;
}


