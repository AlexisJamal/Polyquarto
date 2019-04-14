#include <cassert>
#include <time.h>
#include "sdlJeu.h"
#include <stdlib.h>
#include <string>

#include <iostream>
using namespace std;

const int TAILLE_CASE = 100;

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

Image::~Image () {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	has_changed = true;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu () {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

	int dimx = 8 * TAILLE_CASE;
    int dimy = 4 * TAILLE_CASE;

    jeu = Jeu();

    // Creation de la fenetre
    window = SDL_CreateWindow("PolyQuarto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	im_grille.loadFromFile("data/grille.png",renderer);
    im_fond.loadFromFile("data/fond.jpg",renderer);
    im_winSelect.loadFromFile("data/winSelect.jpg",renderer);
    im_win1.loadFromFile("data/win1.png",renderer);
    im_win2.loadFromFile("data/win2.png",renderer);
    im_egalite.loadFromFile("data/egalite.png",renderer);
    im_bar1.loadFromFile("data/bar1.jpg",renderer);
    im_bar2.loadFromFile("data/bar2.jpg",renderer);
    im_barSolo1.loadFromFile("data/barSolo1.jpg",renderer);
    im_barSolo2.loadFromFile("data/barSolo2.jpg",renderer);
    im_select.loadFromFile("data/select.png",renderer);
    im_menu.loadFromFile("data/menu.jpg",renderer);
    im_victoire.loadFromFile("data/victoire.png",renderer);
    im_defaite.loadFromFile("data/defaite.png",renderer);
    formes[0].loadFromFile("data/forme1.png",renderer);
    formes[1].loadFromFile("data/forme2.png",renderer);
    formes[2].loadFromFile("data/forme3.png",renderer);
    formes[3].loadFromFile("data/forme4.png",renderer);
    formes[4].loadFromFile("data/forme5.png",renderer);
    formes[5].loadFromFile("data/forme6.png",renderer);
    formes[6].loadFromFile("data/forme7.png",renderer);
    jetons[0].loadFromFile("data/r1.png",renderer);
    jetons[1].loadFromFile("data/r2.png",renderer);
    jetons[2].loadFromFile("data/r3.png",renderer);
    jetons[3].loadFromFile("data/r4.png",renderer);
    jetons[4].loadFromFile("data/r5.png",renderer);
    jetons[5].loadFromFile("data/r6.png",renderer);
    jetons[6].loadFromFile("data/r7.png",renderer);
    jetons[7].loadFromFile("data/r8.png",renderer);

    jetons[8].loadFromFile("data/b1.png",renderer);
    jetons[9].loadFromFile("data/b2.png",renderer);
    jetons[10].loadFromFile("data/b3.png",renderer);
    jetons[11].loadFromFile("data/b4.png",renderer);
    jetons[12].loadFromFile("data/b5.png",renderer);
    jetons[13].loadFromFile("data/b6.png",renderer);
    jetons[14].loadFromFile("data/b7.png",renderer);
    jetons[15].loadFromFile("data/b8.png",renderer);
}

sdlJeu::~sdlJeu () {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void sdlJeu::sdlAff () {

	SDL_RenderClear(renderer);

    switch (jeu.getState()) {
        case menu:
            drawMenu();
            break;
        case start:
            drawStart();
            break;
        case playing:
            drawPlaying();
            break;
        case won:
            drawWon();
            break;
        case egalite:
            drawEgalite();
            break;
    }

}

void sdlJeu::drawMenu() {
    im_menu.draw(renderer,0,0,800,400);
}

void sdlJeu::drawStart() {
    im_winSelect.draw(renderer,0,0,800,400);
    switch(jeu.getWinningCondition()) {
        case 1:
            im_select.draw(renderer, 80, 140 , 200, 70);
            break;
        case 2:
            im_select.draw(renderer, 280, 110 , 155, 100);
            break;
        case 3:
            im_select.draw(renderer, 435, 110 , 160, 100);
            break;
        case 4:
            im_select.draw(renderer, 595, 110 , 115, 100);
            break;
        case 5:
            im_select.draw(renderer, 160, 210 , 155, 125);
            break;
        case 6:
            im_select.draw(renderer, 315, 210 , 165, 125);
            break;
        case 7:
            im_select.draw(renderer, 480, 210 , 155, 125);
            break;
        default: break;
    }
}

void sdlJeu::drawPlaying() {
    im_fond.draw(renderer,0,0,800,400);
    im_grille.draw(renderer,0,0,400,400);

    Jeton j;
    for(int i = 0; i < 16; i++) {
        j = jeu.getJeton(i);
        if(!j.getIsUsed()) {
            if(j.getIsSelected()) {
                im_select.draw(renderer, 400 + (i%4) * 98, 100 + (i/4) * 73 , 100, 75);
            }
            jetons[getJetonImgIndex(&j)].draw(renderer, 425 + (i%4) * 98, 115 + (i/4) * 73 , 50, 50);
        }
    }
    Grille grid = jeu.getGrid();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid.getJeton(i, j).getIsUsed()) {
                jetons[getJetonImgIndex(grid.getRefJeton(i, j))].draw(renderer, 15 + i * 98, 15 + j * 98 , 70, 70);
            }
        }
    }
    if(jeu.getJoueur() == 1) {
    	if(jeu.getMode() == solo) {
    		im_barSolo1.draw(renderer,400,0,400,100);
    	}
        else im_bar1.draw(renderer,400,0,400,100);
    }
    else {
        if(jeu.getMode() == solo) {
    		im_barSolo2.draw(renderer,400,0,400,100);
    	}
        else im_bar2.draw(renderer,400,0,400,100);
    }
    formes[jeu.getWinningCondition() - 1].draw(renderer,400,0,100,100);
}

void sdlJeu::drawWon() {
    im_fond.draw(renderer,0,0,800,400);
    im_grille.draw(renderer,0,0,400,400);

    Grille grid = jeu.getGrid();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid.getJeton(i, j).getIsUsed() && grid.getWin(i, j)) {
                jetons[getJetonImgIndex(grid.getRefJeton(i, j))].draw(renderer, 15 + i * 98, 15 + j * 98 , 70, 70);
            }
        }
    }
    if(jeu.getJoueur() == 1) {
    	if(jeu.getMode() == solo) {
    		im_victoire.draw(renderer,400,0,400,400);
    	}
        else im_win1.draw(renderer,400,0,400,400);
    }
    else {
    	if(jeu.getMode() == solo) {
			im_defaite.draw(renderer,400,0,400,400);
    	}
        else im_win2.draw(renderer,400,0,400,400);
    }
}
void sdlJeu::drawEgalite() {
    im_fond.draw(renderer,0,0,800,400);
    im_grille.draw(renderer,0,0,400,400);

    Grille grid = jeu.getGrid();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            jetons[getJetonImgIndex(grid.getRefJeton(i, j))].draw(renderer, 15 + i * 98, 15 + j * 98 , 70, 70);
        }
    }
    im_egalite.draw(renderer,400,0,400,400);
}

int sdlJeu::getJetonImgIndex(Jeton* j) {
    int res = 0;
    bool c, h, b;
    c = j->getIsCircle();
    h = j->getIsHoled();
    b = j->getIsBig();

    if(j->getIsRed()) {
        res = -1;
    }
    else {
        res = 7;
    }

    if(c && h && b) res += 6;

    if(c && h && !b) res += 7;

    if(c && !h && b) res += 5;

    if(c && !h && !b) res += 8;

    if(!c && h && b) res += 1;

    if(!c && h && !b) res += 4;

    if(!c && !h && b) res += 3;

    if(!c && !h && !b) res += 2;

    return res;
}

void sdlJeu::mouseToGrid(int mouseX, int mouseY, int &x, int &y) {
    x = mouseX/100;
    y = mouseY/100;
}

void sdlJeu::mouseToJetonIndex(int mouseX, int mouseY, int &index) {
    int x = (mouseX - 400)/100;
    int y = (mouseY - 100)/75;
    index = 4 * y + x;
}

void sdlJeu:: sdlBoucle () {
    SDL_Event events;
	
	bool quit = true;
    int mouseX, mouseY;
    sdlAff();
    SDL_RenderPresent(renderer);
	while (quit) {
		while (SDL_PollEvent(&events)) {
			switch (events.type) {
				case SDL_QUIT:
					quit = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    switch (jeu.getState()) {
                        case menu:
                            eventMenu(mouseX, mouseY);
                            break;
                        case start:
                            eventStart(mouseX, mouseY);
                            break;
                        case playing:
                            eventPlaying(mouseX, mouseY);
                            break;
                        case won:
                            eventWon(mouseX, mouseY);
                            break;
                        case egalite:
                            eventWon(mouseX, mouseY);
                            break;
                    }
					break;
			}
		}
	}
}

void sdlJeu::eventMenu(int mouseX, int mouseY) {
    if(mouseX >= 310 && mouseX <= 480 && mouseY >= 170 && mouseY <= 210) {
        jeu.setMode(multi);
        jeu.setState(start);
        sdlAff();
        SDL_RenderPresent(renderer);
    }
    else if(mouseX >= 310 && mouseX <= 480 && mouseY >= 240 && mouseY <= 280) {
        jeu.setMode(solo);
        jeu.setState(start);
        sdlAff();
        SDL_RenderPresent(renderer);
    }
}

void sdlJeu::eventStart(int mouseX, int mouseY) {
    if(mouseY >= 110 && mouseY <= 210) {
        if(mouseX >= 80 && mouseX <= 280) {
            jeu.setWinningCondition(1);
        }
        if(mouseX > 280 && mouseX <= 435) {
            jeu.setWinningCondition(2);
        }
        if(mouseX > 435 && mouseX <= 595) {
            jeu.setWinningCondition(3);
        }
        if(mouseX > 595 && mouseX <= 710) {
            jeu.setWinningCondition(4);
        }
    }
    else if(mouseY > 210 && mouseY <= 335) {
        if(mouseX >= 160 && mouseX <= 315) {
            jeu.setWinningCondition(5);
        }
        if(mouseX > 315 && mouseX <= 480) {
            jeu.setWinningCondition(6);
        }
        if(mouseX > 480 && mouseX <= 635) {
            jeu.setWinningCondition(7);
        }
    }
    else if(mouseX >= 340 && mouseX <= 490 && mouseY >= 350 && mouseY <= 385) {
        jeu.setState(playing);
    }
    sdlAff();
    SDL_RenderPresent(renderer);
}

void sdlJeu::eventPlaying(int mouseX, int mouseY) {
    int x, y, index;
    if(jeu.getMode() == solo) {
    	if(jeu.getJoueur() == 1) {
    		if(mouseX >= 400 && mouseY >= 100) {
		        mouseToJetonIndex(mouseX, mouseY, index);
		        if(jeu.selectJeton(index)) {
		            sdlAff();
		            SDL_RenderPresent(renderer);
		            Ia::jouer(jeu);
		            sdlAff();
		            SDL_RenderPresent(renderer);
		            if(jeu.getState() == playing) Ia::jouer(jeu);
		            sdlAff();
		            SDL_RenderPresent(renderer);
		        }
		    }
    	}
    	else {
    		if(jeu.getJetonSelected() && mouseX <= 400) {
		        mouseToGrid(mouseX, mouseY, x, y);
		        if(jeu.poseJeton(x, y)) {
		            sdlAff();
		            SDL_RenderPresent(renderer);
		        }
		    }
    	}
   	}
   	else {
   		if(jeu.getJetonSelected() && mouseX <= 400) {
	        mouseToGrid(mouseX, mouseY, x, y);
	        if(jeu.poseJeton(x, y)) {
	            sdlAff();
	            SDL_RenderPresent(renderer);
	        }
	    }
	    else if(mouseX >= 400 && mouseY >= 100) {
	        mouseToJetonIndex(mouseX, mouseY, index);
	        if(jeu.selectJeton(index)) {
	            sdlAff();
	            SDL_RenderPresent(renderer);
	        }
	    }
   	}
    
    if(mouseX >= 690 && mouseX <= 775 && mouseY >= 35 && mouseY <= 70) {
        jeu = Jeu();
        sdlAff();
        SDL_RenderPresent(renderer);
    }
}

void sdlJeu::eventWon(int mouseX, int mouseY) {
    if(mouseX >= 535 && mouseX <= 655 && mouseY >= 345 && mouseY <= 380) {
        jeu = Jeu();
        sdlAff();
        SDL_RenderPresent(renderer);
    }
}
