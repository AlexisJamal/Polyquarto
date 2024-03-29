#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL.h>
#include <SDL_image.h>

#include "../core/Jeu.h"
#include "../core/Ia.h"


class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
   	Image () ;
	~Image () ;
   	void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
};




class sdlJeu {

private :


	SDL_Window * window;
	SDL_Renderer * renderer;

    Jeu jeu;

	Image im_grille;
    Image im_fond;
    Image im_winSelect;
    Image im_win1;
    Image im_win2;
    Image im_egalite;
    Image im_bar1;
    Image im_bar2;
    Image im_barSolo1;
    Image im_barSolo2;
    Image im_menu;
    Image im_victoire;
    Image im_defaite;

    Image jetons[16];
    Image formes[7];
    Image im_select;

public :

    sdlJeu ();
    ~sdlJeu ();
    int getJetonImgIndex(Jeton* j);
    void mouseToGrid(int mouseX, int mouseY, int &x, int &y);
    void mouseToJetonIndex(int mouseX, int mouseY, int &index);
    void sdlBoucle();
    void sdlAff();
    void drawMenu();
    void drawStart();
    void drawPlaying();
    void drawWon();
    void drawEgalite();
    void eventMenu(int mouseX, int mouseY);
    void eventStart(int mouseX, int mouseY);
    void eventPlaying(int mouseX, int mouseY);
    void eventWon(int mouseX, int mouseY);

};

#endif
