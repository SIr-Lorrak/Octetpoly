#ifndef OCTET_EVENEMENT_H
#define OCTET_EVENEMENT_H

#include <iostream>
#include <string>
using namespace std;

const string tab_com[3] = {"maison","papa maison", "truc bidule"};

class Evenement{
	private :
		unsigned int ch; //chance en pourcentage du déclenchement de l'événement
		string n; //nom de l'evenement
		bool t; //true si l'evenement et bénéfique et false si il est maléfique

	public :
		

};



class Hacking{
	private :
	string mot;
	unsigned int nbSaisie;
	string motSaisie;

	public :

	Hacking();
	void saisir(char N);
	bool valider();
	void motSuivant();
	string getMot();
	string getMotSaisie();
	unsigned int getnbSaisie();
	void fini(float N); 	
};


class clicker {
	private :
	

	public :
	

};


class Escape {
	private :


	public :
};


class Lucky {
	private : 


	public :
};




#endif