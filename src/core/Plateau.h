#ifndef OCTET_PLATEAU_H
#define OCTET_PLATEAU_H

#include "Case.h"
#include "Joueur.h"
#include "Ordi.h"
//#include <SDL_image.h>

class Plateau{
private:

	//Champs liée au plateau
	 	unsigned int nbcase;
	 	Case * tab;

	 	unsigned int nbJoueur;
	 	unsigned int nbOrdi;
	 	/*
	 	Joueur j1;
	 	Joueur j2;
	 	Joueur j3;
	 	Joueur j4;
		*/
		/*
	 	Ordi ordi1;
	 	Ordi ordi2;
	 	Ordi ordi3;
	 	Ordi ordi4;
		*/
		
	 //Champs liée à la SDL
	 	unsigned int dimx, dimy;
	 	/*
		SDL_Window * window;
		SDL_Renderer * renderer;
		SDL_Surface* surface;
		SDL_Texture* texture;
		int x;
		int y;
		int w;
		int h;
		*/
		/**
		@brief affiche l'image et la fenetre en SDL2 
		@param none
		**/
		//void sdlAffichage();
		/**
		@brief initialise la fenetre et l'image
		@param none
		**/
		//void afficherInit();
		/**
		@brief fait la boucle pour les evenement
		@param none
		**/
 		//void afficherBoucle();

 		/**
 		@brief fabrique la texture et la surface
		@param filename : char; renderer : SDL_Renderer
		**/
 		//void afficherCreerImage(const char* filename, SDL_Renderer * renderer);

 		/**
		@brief destructeur SDL
		@param none
		**/
 		//void afficherDestruction();	

public:

	Plateau();

	/**
 	@brief Créer le plateau 
	@param dimx,dimy,nbJoueur : unsigned int
	**/
	Plateau(const unsigned int dimx, const unsigned int dimy, const unsigned int nbJoueur);

	~Plateau();



};

#endif