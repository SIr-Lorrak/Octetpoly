#ifndef OCTET_JEUSDL_H
#define OCTET_JEUSDL_H


#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Evenement.h"
#include "../core/Jeu.h"


const unsigned int DEFAULT=0,RED=1,GREEN=2,BLUE=3;

using namespace std;



class Image{

private:

	SDL_Surface * surface;
    SDL_Texture * texture;



public:
	Image();
	~Image();
	void loadFichier(const char* nom_fichier, SDL_Renderer * renderer);
	void loadSurface (SDL_Renderer * renderer);
	void dessineTexture(SDL_Renderer * renderer,int x, int y, int w, int h);
	void dessineTextureCo(SDL_Renderer * renderer,int x,int y,int x2,int y2);
	SDL_Texture * getTexture();
	void setSurface(SDL_Surface * surf);


};

struct Mouse{
	int x,y;
};


class JeuSDL{

private:
	Escape e;
	Evenement ev;

	Jeu j;

	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * Police;
	SDL_Color font_color;

	Mouse m;//coordonnées de la souris

	Image texteExemple;//image pour le texte

//---image pour le plateau
	Image plateau;
	Image ange;
	Image demon;

//---different boutons
	Image button;
	Image red_button;
	Image green_button;
	Image blue_button;

//---image pour l'escape
	Image ARRIVEE;
	Image DEPART;
	Image H;//herbe
	Image POLICE;//voiture de police
	Image RH;//route horizontal
	Image RV;//route vertical
	Image T1;//virage de bas vers la droite
	Image T2;//virage de bas vers la gauche
	Image T3;//virage de haut vers la gauche
	Image T4;//virage de haut vers la droite
	Image M;//mur

	bool animation;
	//quand animation est a true l'utilisateur ne peut rien faire
	//pour laisser le temps a l'animation de se terminer.

//---methode
	void afficheButton(const int x,const int y,const int w,const int h,const unsigned int type=DEFAULT,const string & c1="",const Image * c2=NULL,const SDL_Color couleur={255,255,255});

	void affichageEscape();
	void affichageMenu();
	void affichageJeu();
	void affichageHacking();
	void affichageClicker();
	void affichage();

	void actionSouris();

	bool update(SDL_Event & events);


public:
//---constructeur/destructeur
	JeuSDL();
	~JeuSDL();

//---methode principal
	/**
	@brief boucle principal du jeu 
	@param none
	*/
	void run();
};

#endif