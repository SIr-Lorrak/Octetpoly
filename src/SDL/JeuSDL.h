#ifndef OCTET_JEUSDL_H
#define OCTET_JEUSDL_H


#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Evenement.h"
#include "../core/Jeu.h"


const unsigned int DEFAULT=0,RED=1,GREEN=2,BLUE=3,INVISIBLE=4;

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
	string action;//stock l'action d'un bouton en attendant que le joueur relache la souris

	Image inputTexte;//image pour le texte

//---image pour le plateau
	Image plateau;
	Image ange;
	Image demon;
	Image DE;

//---different boutons
	Image button;
	Image buttonClicked;
	Image red_button;
	Image red_buttonClicked;
	Image green_button;
	Image green_buttonClicked;
	Image blue_button;
	Image blue_buttonClicked;

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

	Image hack;

	bool act;
	bool animation;
	bool dees;
	//quand animation est a true l'utilisateur ne peut rien faire
	//pour laisser le temps a l'animation de se terminer.

//---methode
	/**
	@brief cette fonction permet de créer un bouton s'affichant sur la fenetre de different type permettant de lancer une action lors du relachement de la souris
	@param un string effet, defini la touche de clavier correspondant au bouton ou alors a une action particulière (si l'effet fait plus de 1 caractère)
	@param quatre entier x,y,w,h respectivement les coordonnées x,y du coin haut-gauche puis la largeur et la hauteur du bouton
	@param un entier non-signer correspondant au type (il faut utiliser les constante DEFAULT RED GREEN BLUE et INVISIBLE) (DEFAULT par défaut en même temps c'est évident)
	@param un string c1, le contenue du bouton sous forme de texte (vide par défaut)
	@param un pointeur sur Image c2, le contenue du bouton sous forme d'une Image (a NULL par défaut)
	@param un entier margin, la largeur en pixel des bord entre le contenu et les bord du bouton (de 5 pixels par dafaut)
	@param un SDL_Color, la couleur du texte contenue dans le bouton (blanc par défaut)
	*/
	void newButton(const string & effet,const int x,const int y,const int w,const int h,const unsigned int type=DEFAULT,const string & c1="",const Image * c2=NULL,const int margin=5,const SDL_Color couleur={255,255,255});

	void dessineTexte(const string & texte,int x,int y,unsigned int taille=14,const SDL_Color couleur = {0,0,0});

	void affichageEscape();
	void affichageMenu();
	void affichageJeu();
	void affichageHacking();
	void affichageClicker();
	void affichage();

	bool update(SDL_Event & events);

	void affichageDees();
	void affichageInteraction();


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