#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Ia.h"

using namespace std;

int Ia::evaluation (Jeu & jeu){
	int res = false;

	Grille grid = jeu.getGrid();

	if (grid.hasWon(1)){
		res = 100;
	}
	else {
		switch(jeu.getWinningCondition()) {
			case 1: 
				res = win1(grid);
				break;
			case 2: 
				res = win2(grid);
				break;
			case 3: 
				res = win3(grid);
				break;
			case 4: 
				res = win4(grid);
				break;
			case 5: 
				res = win5(grid);
				break;
			case 6: 
				res = win6(grid);
				break;
			case 7: 
				res = win7(grid);
				break;
			default: break;
		}
	}

	return res;
}

int Ia::MinMax (Jeu* jeu , int profondeur, bool opposant){
	int valeur;
	if (profondeur == 0 || jeu->getState() == won || jeu->getState() == egalite){
		cout << "Fin de l'arbe" << endl;
		return evaluation(*jeu);
	}
	if (opposant){
		valeur = -9999;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j<4; j++){
				Jeu * jeutmp = new Jeu(*jeu);
				if (jeutmp->poseJeton(i,j)){
					cout<<"on pose un jeton sur copie jeu(j)"<<endl;
					for(int k = 0; k< 16; k++){
						if(jeutmp->selectJeton(k)){
							cout<<"on choisit un jeton aleatoire(ia)"<<endl;
							int actu = -MinMax(jeutmp,profondeur-1,false);
							cout<<"on obtient une valeur"<<endl;	
							if (valeur < actu){
								valeur = actu;
								cout<<"la valeur a été changée (j)"<<endl;
							}
						}
					}
				}
			}
		}
	}
	else{
		valeur = 9999;
		for(int l = 0; l < 4; l++){
			for(int m = 0; m<4; m++){
				Jeu * jeutmp = new Jeu(*jeu);
				cout << "pose jeton" << endl;
				if (jeutmp->poseJeton(l,m)){
					cout<<"on a pose un jeton sur copie jeu(ia)"<<endl;
					for(int c = 0; c< 16; c++){
						if(jeutmp->selectJeton(c)){
							cout<<"on choisi un jeton aleatoire (j)"<<endl;
							int actu = MinMax(jeutmp, profondeur-1, true);
							if (valeur > actu){
								valeur = actu;
								cout<<"la valeur a été changée (ia)"<<endl;
							}
						}
					}
				}
			}
		}
	}
	cout<<"on s'apprête à donner la valeur trouvée"<<endl;
	return valeur;
}


void Ia::jouer(Jeu & jeu) {
	srand (time(NULL));
	Jeu * jeutmp = new Jeu(jeu);
	int profondeur = 2;
	int maximum = -9999;
	int maximumJeton = -9999;
	int maxx,maxy,maxjet,actujet;
	maxx=0;
	maxy=0;
	if (jeu.getJoueur() == 1){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				jeutmp = new Jeu(jeu);
				if (jeutmp->poseJeton(i,j)){
					int actu = MinMax(jeutmp,profondeur-1,false);
					cout<<"minmax effectué"<<endl;
					if (actu > maximum){
						cout<<"on entre dans la condition"<<endl;
						maximum=actu;
						maxx=i;
						maxy=j;
						cout<<"fin de la condition"<<endl;
					}
					
				}
			}
		}
		cout<<"On va poser le jeton sur la grille"<<endl;
		jeu.poseJeton(maxx,maxy);
		cout<<"Jeton posé sur la grille"<<endl;
	}
	else{
		for(int k = 0; k< 16; k++){
			jeutmp = new Jeu(jeu);
			if(jeutmp->selectJeton(k)){
				cout<<"L'ia a sélectionner un jeton random"<<endl;
				actujet = -MinMax(jeutmp,profondeur-1,true);
				cout<<"Minmax effectué"<<endl;
				if (actujet > maximumJeton && jeutmp->selectJeton(actujet)){
					cout<<"On rentre dans la condition"<<endl;
					maxjet = actujet;
					cout<<"Jeton preselectionne changé"<<endl;
				}
			}
		}
		cout << "maxjet " << maxjet << endl;
		jeu.selectJeton(maxjet);
		
		cout<<"Jeton selectionné"<<endl;
	}
}

int Ia::win1(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	bool r = grid.getJeton(lastPlayedX,lastPlayedY).getIsRed();
	bool c = grid.getJeton(lastPlayedX,lastPlayedY).getIsCircle();
	bool h = grid.getJeton(lastPlayedX,lastPlayedY).getIsHoled();
	bool b = grid.getJeton(lastPlayedX,lastPlayedY).getIsBig();

	for(int i = 1; i < 4; i++) {
		if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsRed() == r) {
			res++;
		}
			if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsCircle() == c) {
			res++;
		}
		if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsHoled() == h) {
			res++;
		}
		if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsBig() == b) {
			res++;
		}
	}

	for(int i = 1; i < 4; i++) {
		if(grid.getJeton(lastPlayedX,i).getIsUsed() && grid.getJeton(lastPlayedX,i).getIsRed() != r) {
			res++;
		}
		if(grid.getJeton(lastPlayedX,i).getIsUsed() && grid.getJeton(lastPlayedX,i).getIsCircle() != c) {
			res++;
		}
		if(grid.getJeton(lastPlayedX,i).getIsUsed() && grid.getJeton(lastPlayedX,i).getIsHoled() != h) {
			res++;
		}
		if(grid.getJeton(lastPlayedX,i).getIsUsed() && grid.getJeton(lastPlayedX,i).getIsBig() != b) {
			res++;
		}
	}

	return res;
}

/* #
   ###  */
int Ia::win2(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, -1, -1, -2, -1);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 2) {
		res += checkForme(grid, 1, 0, 1, -1, 1, -2);
	}
	// bas-droite
	if(lastPlayedX <= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, 1, 1, 2, 1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY <= 1) {
		res += checkForme(grid, -1, 0, -1, 1, -1, 2);
	}

	//Place 2
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, -1, 0, -2, 0);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res += checkForme(grid, -1, 0, 0, -1, 0, -2);
	}
	// bas-droite
	if(lastPlayedX <= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, 1, 0, 2, 0);
	}
	// bas-gauche
	if(lastPlayedX <= 2 && lastPlayedY <= 1) {
		res += checkForme(grid, 1, 0, 0, 1, 0, 2);
	}

	//Place 3
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, 1, 0, 1, 1);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, -1, 0, 1, -1, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, -1, 0, -1, -1);
	}
	// bas-gauche
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, 0, -1, 1, -1);
	}

	//Place 4
	// haut-gauche
	if(lastPlayedX <= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 2, 0, 2, 1);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, 0, 2, -1, 2);
	}
	// bas-droite
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, -2, 0, -2, -1);
	}
	// bas-gauche
	if(lastPlayedX <= 2 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, 0, -2, 1, -2);
	}

	return res;
}

/*   #
   ### */
int Ia::win3(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res += checkForme(grid, -1, 0, -1, -1, -1, -2);
	}
	// haut-droite
	if(lastPlayedX <= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, 1, -1, 2, -1);
	}
	// bas-droite
	if(lastPlayedX <= 2 && lastPlayedY <= 1) {
		res += checkForme(grid, 1, 0, 1, 1, 1, 2);
	}
	// bas-gauche
	if(lastPlayedX >= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, -1, 1, -2, 1);
	}

	//Place 2
	// haut-gauche
	if(lastPlayedX <= 2 && lastPlayedY >= 2) {
		res += checkForme(grid, 1, 0, 0, -1, 0, -2);
	}
	// haut-droite
	if(lastPlayedX <= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, 1, 0, 2, 0);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedY <= 1) {
		res += checkForme(grid, -1, 0, 0, 1, 0, 2);
	}
	// bas-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, -1, 0, -2, 0);
	}

	//Place 3
	// haut-gauche
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, -1, 0, 1, 1, 1);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, -1, 0, -1, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, 0, -1, -1, -1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, 1, 0, 1, -1);
	}

	//Place 4
	// haut-gauche
	if(lastPlayedX <= 2 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, 0, 2, 1, 2);
	}
	// haut-droite
	if(lastPlayedX >= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, -2, 0, -2, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, 0, -2, -1, -2);
	}
	// bas-gauche
	if(lastPlayedX <= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, 2, 0, 2, -1);
	}

	return res;
}

/* ##
   ##  */
int Ia::win4(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, 0, -1, -1, -1);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, 0, -1, 1, -1);
	}
	// bas-droite
	if(lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 0, 1, 1, 1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, 0, 1, -1, 1);
	}

	return res; 
}

/*  ##
   ##  */
int Ia::win5(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, -1, -1, -1, -2);
	}
	// haut-droite
	if(lastPlayedX <= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, 1, -1, 2, -1);
	}
	// bas-droite
	if(lastPlayedX <= 2 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, 1, 1, 1, 2);
	}
	// bas-gauche
	if(lastPlayedX >= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, -1, 1, -2, 1);
	}

	//Place 2
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, -1, 0, -1, -1);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, 0, -1, 1, -1);
	}
	// bas-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, -1, 1, 0, 1, 1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 0, 1, -1, 1);
	}

	return res;
}

/*  #
   ###  */
int Ia::win6(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, -1, 1, 1, 1);
	}
	// haut-droite
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, -1, -1, -1, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, 1, -1, -1, -1);
	}
	// bas-gauche
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 1, 1, 1, -1);
	}

	//Place 2
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 0, -1, -1, 0, 1, 0);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 0, -1, 0, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, 1, 1, 0, -1, 0);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, 0, 1, 0, -1);
	}

	//Place 3
	// haut-gauche
	if(lastPlayedX <= 1 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, 1, -1, 2, 0);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, 1, 1, 0, 2);
	}
	// bas-droite
	if(lastPlayedX >= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, -1, 1, -2, 0);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, -1, -1, 0, -2);
	}

	//Place 4
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, -1, -1, -2, 0);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, 1, -1, 0, -2);
	}
	// bas-droite
	if(lastPlayedX <= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 1, 1, 2, 0);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, -1, 1, 0, -2);
	}

	return res;
}

/* ##
    ##  */
int Ia::win7(Grille grid) {
	int res = 0;

	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	//Place 1
	// haut-gauche
	if(lastPlayedX >= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, -1, 0, -1, -1, -2, -1);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 2) {
		res += checkForme(grid, 0, -1, 1, -1, 1, -2);
	}
	// bas-droite
	if(lastPlayedX <= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 1, 0, 1, 1, 2, 1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY <= 1) {
		res += checkForme(grid, 0, 1, -1, 1, -1, 2);
	}

	//Place 2
	// haut-gauche
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY >= 1) {
		res += checkForme(grid, 1, 0, 0, -1, -1, -1);
	}
	// haut-droite
	if(lastPlayedX <= 2 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, -1, 1, 0, 1, 1);
	}
	// bas-droite
	if(lastPlayedX >= 1 && lastPlayedX <= 2 && lastPlayedY <= 2) {
		res += checkForme(grid, -1, 0, 0, 1, 1, 1);
	}
	// bas-gauche
	if(lastPlayedX >= 1 && lastPlayedY >= 1 && lastPlayedY <= 2) {
		res += checkForme(grid, 0, -1, -1, 0, -1, 1);
	}

	return res;
}

int Ia::checkForme(Grille grid, int x1, int y1, int x2, int y2, int x3, int y3) {
	int res = 0;
	bool quit = false;
	Jeton carre[3];
	int lastPlayedX = grid.getLastPlayedX();
	int lastPlayedY = grid.getLastPlayedY();

	bool r = grid.getJeton(lastPlayedX,lastPlayedY).getIsRed();
	bool c = grid.getJeton(lastPlayedX,lastPlayedY).getIsCircle();
	bool h = grid.getJeton(lastPlayedX,lastPlayedY).getIsHoled();
	bool b = grid.getJeton(lastPlayedX,lastPlayedY).getIsBig();

	carre[0] = grid.getJeton(lastPlayedX+x1,lastPlayedY+y1);
	carre[1] = grid.getJeton(lastPlayedX+x2,lastPlayedY+y2);
	carre[2] = grid.getJeton(lastPlayedX+x3,lastPlayedY+y3);

	for(int i = 0; i < 3 && !quit; i++) {
		if(carre[i].getIsUsed()) {
			if(carre[i].getIsUsed() && carre[i].getIsRed() == r) {
				res++;
			}
			if(carre[i].getIsUsed() && carre[i].getIsCircle() == c) {
				res++;
			}
			if(carre[i].getIsUsed() && carre[i].getIsHoled() == h) {
				res++;
			}
			if(carre[i].getIsUsed() && carre[i].getIsBig() == b) {
				res++;
			}
		}
	}

	return res;
}
