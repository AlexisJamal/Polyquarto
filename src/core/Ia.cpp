#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Ia.h"

using namespace std;

int Ia::evaluation (Jeu & jeu){
	int points;
	Grille grid = jeu.getGrid();
	int lastPlayedX = jeu.getGrid().getLastPlayedX();
	int lastPlayedY = jeu.getGrid().getLastPlayedY();
	switch (jeu.getWinningCondition()){
		case 1: 
		{
			bool r = grid.getJeton(lastPlayedX,lastPlayedY).getIsRed();
			bool c = grid.getJeton(lastPlayedX,lastPlayedY).getIsCircle();
			bool h = grid.getJeton(lastPlayedX,lastPlayedY).getIsHoled();
			bool b = grid.getJeton(lastPlayedX,lastPlayedY).getIsBig();
			if (grid.hasWon(1)){
				points = 100;
			}
			else{
				for(int i = 1; i < 4; i++) {
					if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsRed() == r) {
						points++;
					}
						if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsCircle() == c) {
						points++;
					}
					if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsHoled() == h) {
						points++;
					}
					if(grid.getJeton(i,lastPlayedY).getIsUsed() && grid.getJeton(i,lastPlayedY).getIsBig() == b) {
						points++;
					}
				}
			// On vérifie la colonne
				for(int j = 1; j < 4; j++) {
					if(grid.getJeton(lastPlayedX,j).getIsUsed() && grid.getJeton(lastPlayedX,j).getIsRed() != r) {
					points++;
					}
					if(grid.getJeton(lastPlayedX,j).getIsUsed() && grid.getJeton(lastPlayedX,j).getIsCircle() != c) {
						points++;
					}
					if(grid.getJeton(lastPlayedX,j).getIsUsed() && grid.getJeton(lastPlayedX,j).getIsHoled() != h) {
						points++;
					}
					if(grid.getJeton(lastPlayedX,j).getIsUsed() && grid.getJeton(lastPlayedX,j).getIsBig() != b) {
						points++;
					}
				}
			}
			break;
		}
		default:
		{
			points = 2;
			break;
		}
		}
	return points;
}

int Ia::MinMax (Jeu & jeu , int profondeur, bool opposant){
	int valeur;
	Jeu * jeutmp = new Jeu(jeu);
	if (profondeur == 0 || jeu.getState() == won || jeu.getState() == egalite){
		return evaluation(jeu);
	}
	if (opposant){
		valeur = 9999;
		int actu;
		for(int k = 0; k< 16; k++){
			if(jeutmp->selectJeton(k)){
				std::cout<<"on choisit un jeton aleatoire(ia)"<<std::endl;
				for(int i = 0; i < 4; i++){
					for(int j = 0; j<4; j++){
						if (jeutmp->getGrid().getJeton(i,j).getIsUsed() == false){
							jeutmp->poseJeton(i,j);
							std::cout<<"on pose un jeton sur copie jeu(j)"<<std::endl;
							for(int m = 0; m< 16; m++){
								if(jeutmp->selectJeton(m)){
									std::cout<<"on choisit un jeton aleatoire(j)"<<std::endl;
									actu = -MinMax(*jeutmp, profondeur-1, false);
									std::cout<<"le minmax passe"<<std::endl;
									if (valeur < actu){
										valeur = actu;
										std::cout<<"la valeur a été changée (j)"<<std::endl;
									}
								}
							}
						}
					}
				}
			}
		}
		return valeur;
	}
	else{
		valeur = -9999;
		int actu;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j<4; j++){
				if (jeutmp->getGrid().getJeton(i,j).getIsUsed() == false){
					jeutmp->poseJeton(i,j);
					std::cout<<"on pose un jeton sur copie jeu(ia)"<<std::endl;
					actu = MinMax(*jeutmp, profondeur-1, true);
					if (valeur < actu){
						valeur = actu;
						std::cout<<"la valeur a été changée (ia)"<<std::endl;
					}
				}
			}
		}
		
		return valeur;
	}
}


void Ia::jouer(Jeu & jeu) {
	srand (time(NULL));
	Jeu * jeutmp = new Jeu(jeu);
	int profondeur = 3;
	int maximum = -9999;
	int maximumJeton = -9999;
	int actu,maxx,maxy,maxjet,actujet;
	maxx=0;
	maxy=0;
	if ( jeu.getJoueur() == 1){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if (jeutmp->getGrid().getJeton(i,j).getIsUsed() == false){
					jeutmp->poseJeton(i,j);
					std::cout<<"pose premier jeton"<<std::endl;
					actu = MinMax(*jeutmp,profondeur-1,true);
					std::cout<<"premier minmax effectué"<<std::endl;
					if (actu > maximum){
						maximum=actu;
						maxx=i;
						maxy=j;
					}
					
				}
			}
		}
		jeu.poseJeton(maxx,maxy);
		std::cout<<"Jeton posé sur la grille"<<std::endl;
	}
	else{
		for(int k = 0; k< 16; k++){
			if(jeutmp->selectJeton(k)){
				actujet = MinMax(*jeutmp,profondeur-1,false);
				if (actujet > maximumJeton){
					maxjet = actujet;
				}
			}
		}
		jeu.selectJeton(maxjet);
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
