#include <iostream>
#include "Jeu.h"

using namespace std;

Jeu::Jeu () {
	
	winningCondition = 1;

	state = menu;

	Jeton tmp = Jeton();

	for(int r = 0; r < 2; r++)
		for(int c = 0; c < 2; c++)
			for(int h = 0; h < 2; h++)
				for(int b = 0; b < 2; b++) {
					tmp = Jeton(0,0,r,c,h,b);
					jetons.push_back(tmp);
				}

	jetonSelected = false;
	grid = Grille();
	joueur = 1;
	countPose = 0;
	mode = multi;
}

Jeu::~Jeu() {
}

Jeton Jeu::getJeton(int index) {
	return jetons.at(index);
}

Grille Jeu::getGrid() {
	return grid;
}

bool Jeu::selectJeton(int index) {
	if(jetonSelected) {
		jetons[getSelected()].setIsSelected(false);
	}
	bool res = false;
	if(!jetons[index].getIsUsed()) {
		jetons[index].setIsSelected(true);
		jetonSelected = true;
		res = true;
	}
	return res;
}

bool Jeu::poseJeton(int x, int y) {
	int selected = getSelected();

	bool res = false;

	if(!grid.getJeton(x, y).getIsUsed()) {
		jetons[selected].setIsSelected(false);
		jetons[selected].setIsUsed(true);
		jetonSelected = false;
		grid.setJeton(x, y, jetons[selected]);
		res = true;
		joueur = joueur%2 + 1;
		if(grid.hasWon(winningCondition)) {
			state = won;
		}
		countPose++;
		if(countPose == 16) {
			state = egalite;
		}
	}

	return res;
}

int Jeu::getSelected() {
	bool quit = false;
	int res;
	for(int i = 0; i < jetons.size(); i++ && !quit) {
		if(jetons[i].getIsSelected()) {
			res = i;
			quit = true;
		}
	}
	return res;
}

bool Jeu::getJetonSelected() {
	return jetonSelected;
}

int Jeu::getWinningCondition() {
	return winningCondition;
}

void Jeu::setWinningCondition(int wc) {
	winningCondition = wc;
}

State Jeu::getState() {
	return state;
}

void Jeu::setState(State s) {
	state = s;
}

Mode Jeu::getMode() {
	return mode;
}

void Jeu::setMode(Mode m) {
	mode = m;
}

int Jeu::getJoueur() {
	return joueur;
}
