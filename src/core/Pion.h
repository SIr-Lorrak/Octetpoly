#ifndef OCTET_PION_H
#define OCTET_PION_H

const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32; //Max case du plateau
const int INITCOIN = 0; //A changer

class Pion{
	private :	int pos;								//Position du pion
				int karma;								//Karma positif ou négatif du pion
				float bitcoin;							//Argent du pion
				int IndCaseAchetee[MAXCASEHT];			//Indice des cases achetées
				char c ; 								//Caractère du pion

	public :	
				//Constructeur par défaut
				Pion();		

				//Accesseurs	
				int getpos();
				int getkarma();
				float getbitcoin();
				int getIndCaseAchetee();

				//Mutateurs
				void setpos(x1);
				void setkarma();
				void setbitcoin();
				void setIndCaseAchetee();
				void setc();

				//Fonctions
				int Avancer(pos);


				//Destructeur
				~ Pion();

};

#endif