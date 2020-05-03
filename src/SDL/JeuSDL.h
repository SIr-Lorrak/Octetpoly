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


/**
@brief gestion des images SDL (creation/affichage texture)
*/
class Image{

private:

	SDL_Surface * surface;
    SDL_Texture * texture;



public:

	/**
	@brief constructeur de Image
	@param none
	*/
	Image();

	/**
	@brief destructeur de Image
	@param none
	*/
	~Image();

	/**
	@brief fait l'image à partir d'un fichier
	@param nom du fichier, renderer SDl
	*/
	void loadFichier(const char* nom_fichier, SDL_Renderer * renderer);

	/**
	@brief fait une texture à partir d'une surface existante
	@param renderer SDL
	*/
	void loadSurface (SDL_Renderer * renderer);

	/**
	@brief affiche l'image
	@param renderer SDL, coord x, coord y, largeur, hauteur
	*/
	void dessineTexture(SDL_Renderer * renderer,int x, int y, int w, int h) const;

	/**
	@brief retourne la texture
	@param none
	*/
	SDL_Texture * getTexture();

	/**
	@brief fait une surface
	@param surface SDL
	*/
	void setSurface(SDL_Surface * surf);


};


/**
@brief structure coord souris
*/
struct Mouse{
	int x,y;
};

//--------------------------------------------------------------------------------------------------

/**
@brief classe affichage SDL
*/
class JeuSDL{

private:

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
	Image Carte;
	Image Drapeau;
	Image GrosTitre;

//---different boutons
	Image button;
	Image buttonClicked;
	Image red_button;
	Image red_buttonClicked;
	Image green_button;
	Image green_buttonClicked;
	Image blue_button;
	Image blue_buttonClicked;

	Image poubelle;

//---differents pions
	Image pions[16];

//---images pour l'escape
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

//---image pour hacker
	Image hack;


//---images pour cliker
	Image clicker;
	Image pub1;
	Image pub2;
	Image pub3;
	Image pub4;
	Image pub5;
	Image pub6;
	Image pub7;
	Image pub8;
	Image pub9;
	Image pub10;
	Image pub11;
	Image pub12;

	bool act; 
	int a;//pour le clicker; le "a" stock l'id de l'image de pub
	bool clique;//permet de savoir si l'on a cliqué sur une pub
	
	

//---methode
	/**
	@brief cette fonction permet de créer un bouton s'affichant sur la fenêtre de différent type, permettant de lancer une action lors du relachement de la souris
	@param un string effet, defini la touche de clavier correspondant au bouton ou alors à une action particulière (si l'effet fait plus de 1 caractère)
	@param quatre entiers x,y,w,h respectivement les coordonnées x,y du coin haut-gauche puis la largeur et la hauteur du bouton
	@param un entier non-signé correspondant au type (il faut utiliser les constantes DEFAULT RED GREEN BLUE et INVISIBLE) (DEFAULT par défaut en même temps c'est évident)
	@param un string c1, le contenu du bouton sous forme de texte (vide par défaut)
	@param un pointeur sur Image c2, le contenu du bouton sous forme d'une Image (à NULL par défaut)
	@param un entier margin, la largeur en pixel des bords entre le contenu et les bords du bouton (de 5 pixels par défaut)
	@param un SDL_Color, la couleur du texte contenu dans le bouton (blanc par défaut)
	*/
	void newButton(const string & effet,const int x,const int y,const int w,const int h,const unsigned int type=DEFAULT,const string & c1="",const Image * c2=NULL,const int margin=5,const SDL_Color couleur={255,255,255});

	/**
	@brief permet d'affiche du texte 
	@param string texte à afficher; coord x, coord y, une taille (14 par DEFAUT), une couleur (noir par DEFAUT) 
	*/
	void dessineTexte(const string & texte,int x,int y,unsigned int taille=14,const SDL_Color couleur = {0,0,0});

	/**
	@brief permet l'affichage du mini-jeu Escape
	@param none
	*/
	void affichageEscape();

	/**
	@brief permet l'affichage du Menu
	@param none
	*/
	void affichageMenu();

	/**
	@brief permet l'affichage du plateau de jeu
	@param none
	*/
	void affichageJeu();

	/**
	@brief permet l'affichage du mini-jeu Hacking
	@param none
	*/
	void affichageHacking();

	/**
	@brief permet l'affichage du mini-jeu Clicker
	@param none
	*/
	void affichageClicker();

	/**
	@brief permet l'affichage du jeu de base (menu ou minijeu ou plateau ou pause ou victoire)
	@param none
	*/
	void affichage();

	/**
	@brief récupère les touches
	@param évents SDL
	*/
	bool update(SDL_Event & events);

	/**
	@brief permet d'afficher les dés
	@param none
	*/
	void affichageDees();

	/**
	@brief permet d'afficher les interactions quand on se trouve sur une case
	@param none
	*/
	void affichageInteraction();

	/**
	@brief permet d'afficher les propriétés de chaques joueurs
	@param pointeur vers Pion, h une coord de hauteur, jc indique le joueur courant
	*/
	void affichageProrpiete(Pion * p,int h,bool jc);

	/**
	@brief permet d'afficher les cartes chances
	@param H coord de la hauteur de la carte, Titre de la carte, Texte de la carte
	*/
	void affichageCarteChance(int H,string Titre, string Texte);

	/**
	@brief permet d'afficher la campagne de pub
	@param un pointeur vers pion, un pointeur vers case
	*/
	void affichageCampagnePub(Pion *p,Case *c);

	/**
	@brief permet d'afficher la prison
	@param un pointeur vers pion
	*/
	void affichagePrison(Pion *p);

	/**
	@brief permet d'afficher la porte ouverte
	@param un pointeur vers pion, un pointeur vers case
	*/
	void affichagePorteOuverte(Pion *p,Case *c);

	/**
	@brief permet d'afficher le mode vente, si le joueur ne peut plus payer
	@param none
	*/
	void affichageVente();

	/**
	@brief permet d'afficher la Victoire
	@param none
	*/
	void affichageVictoire();

	/**
	@brief permet d'afficher l'écran de pause au centre du plateau.
	@param none
	*/
	void affichagePause();

	/**
	@brief permet l'affichage du mini jeu lucky
	@param none
	*/
	void affichageLucky();

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