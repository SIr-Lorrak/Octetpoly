#include "JeuTXT.h"
//#include "Evenement.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


//permet de detecter l'appuie sur le clavier
bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

void clear(){
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

//constructeur, vide le terminal
jeuTXT::jeuTXT(){
	clear();
	rep = true;
}


//permet de replacer le curseur en heut a gauche
void jeuClear(){
	#ifdef _WIN32
	    // Deplace le curseur en haut a gauche du terminal
	    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	    COORD origine = { (SHORT)x, (SHORT)y };
	    SetConsoleCursorPosition(console, origine);
	#else
	    char t[16];
	    sprintf(t, "\033[%d;%dH", 0, 0);
	    printf("%s",t);
	#endif
}

//permet le deroulement de la partie
// ATTENTION CETTE PARTIE EST A CHANGER ET ADAPTER AVEC LE DEROULEMENT DE LA PERTIE !!
void jeuTXT::run(){
	int d = 0;
	
	while(d ==0){

		if(j.gete().getn() == "rien"){

			j.sete(1);
		}

		if(j.gete().getn() == "hack"){

			affichageHacking();
		}

		update();

		if(j.geth().getnbSaisie() == 4){

			j.sete(2);
			affichageHacking();
			d = 1;
		}
	}
}


//permet d'effacer si la ligne précédente était plus grande 
void Endl(){

		cout<<"                                                                                 "<<endl;
		
}

void curseur(){

	if(clock()%32000<16000){
		cout<<"|";
	}
}

//permet l'affichage txt de l'évenement hacking
void jeuTXT::affichageHacking(){

	jeuClear();

	unsigned int cas = j.geth().getIntAff();

	switch(cas){
		case 2 : // premier affiche, quand le hack commence
			cout<<"Vous devez tapez la commande suivante pour gagné : ";
			break;

		case 0: // affiche quand le mot tapé précédement est correcte
			cout<<"commande validé!";Endl();
			cout<<"Commande suivante : ";
			break;

		case 1: // affichage quand le mot tapé précédement est incorrecte
			cout<<"commande non validé!";Endl();
			cout<<"re-tapez la commande : ";
			break;

		case 3: // enleve l'affichage précédent avant l'affichage suivant
			clear();
			j.seth(1);
			break;

		case 4:	// enleve l'affichage précédent avant l'affichage de la fin
			clear();
			j.seth(2);
			break;
	}
	if(cas <3){
		cout<<j.geth().getMot();Endl();
		cout<<">"<<j.geth().getMotSaisie();
		curseur();
		Endl();
	}

	//affichage de la fin
	if(j.geth().getnbSaisie()==4)

	{
		if(j.gete().getT() == true){
			cout<<"Vous avez GAGNE en "<<j.gete().gettps()<<" seconde";Endl();
		}

		else{
			cout<<"Vous avez PERDU en "<<j.gete().gettps()<<" seconde";Endl();
		}

	}

}


//permet de mettre a jour les objets suite à l'appuie d'une touche
void jeuTXT::update(){

	string touche;

	if(kbhit()&&rep){

		touche = fgetc(stdin);
		j.actionMiniJeu(touche);
		rep = false;

	}
	else{
		rep = true;
	}
}
	
