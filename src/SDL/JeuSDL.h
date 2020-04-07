#ifndef OCTET_JEUSDL_H
#define OCTET_JEUSDL_H


#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Jeu.h"


using namespace std;



class Image{

private:

	SDL_Surface * surface;
    SDL_Texture * texture;



public:
	Image();
	void loadFichier(const char* nom_fichier, SDL_Renderer * renderer);
	void dessineTexture(SDL_Renderer * renderer,int x, int y, int w, int h);
	SDL_Texture * getTexture();


};




class JeuSDL{

private:
	SDL_Window * window;
	SDL_Renderer * renderer;


	Image plateau;
	Image test;

	bool a;


	

public:
	JeuSDL();
	~JeuSDL();
	void affichageJeu();
	void boucleJeu();


		
		



};

#endif