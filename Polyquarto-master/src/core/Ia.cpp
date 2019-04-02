#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Ia.h"

using namespace std;

int Ia::evaluation (Jeu & jeu){
	return 2;
}

int Ia::MinMax (Jeu & jeu , int profondeur, bool opposant){
	int valeur;
	Jeu * jeutmp = new Jeu(jeu);
	if (profondeur == 0 || jeu.getState() == won || jeu.getState() == egalite){
		return evaluation(jeu);
	}
	if (opposant){
		valeur = 99;
		for(int k = 0; k< jeutmp->getJetons().size(); k++){
			jeutmp->selectJeton(k);
			for(int i = 0; i < 4; i++){
				for(int j = 0; j<4; j++){
					jeutmp->poseJeton(i,j);
					valeur = MinMax(*jeutmp, profondeur-1, false);
				}
			}
		}
		return valeur;
	}
	else{
		valeur = -99;
		for(int k = 0; k< jeutmp->getJetons().size(); k++){
			jeutmp->selectJeton(k);
			for(int i = 0; i < 4; i++){
				for(int j = 0; j<4; j++){
					jeutmp->poseJeton(i,j);
					valeur = MinMax(*jeutmp, profondeur-1, true);
				}
			}
		}
		return valeur;
	}
}


void Ia::jouer(Jeu & jeu) {
	srand (time(NULL));
	Jeu * jeutmp = new Jeu(jeu);
	int profondeur = 10;
	int maximum = -999999;
	int actu,maxx,maxy;
	maxx=0;
	maxy=0;
	if ( jeu.getJoueur() == 1){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if (jeutmp->getGrid().getJeton(i,j).getIsUsed() == false){
					jeutmp->poseJeton(i,j);
					actu = MinMax(*jeutmp,profondeur-1,false);
					if (actu > maximum){
						maximum=actu;
						maxx=i;
						maxy=j;
					}
					
				}
			}
		}
		jeu.poseJeton(maxx,maxy);
	}
	else{
		int i = rand() % jeu.getJetons().size();

		while(!jeu.selectJeton(i)) {
			i = rand() % jeu.getJetons().size();
		}
	}
	/*int x, y, i;

	if(jeu.getJoueur() == 1) {
		x = rand() % 4;
		y = rand() % 4;

		while(!jeu.poseJeton(x,y)) {
			x = rand() % 4;
			y = rand() % 4;
		}
	}
	else {
		i = rand() % 16;

		while(!jeu.selectJeton(i)) {
			i = rand() % 16;
		}
	}*/
}
