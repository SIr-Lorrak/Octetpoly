#include "jeuTXT.h"
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


//constructeur, vide le terminal
jeuTXT::jeuTXT(){
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
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
void jeuTXT::deroulementTXT(){
	int d = 0;
	
	while(d ==0){

		if(j.gete().getn() == "rien"){

			j.sete(1);
		}

		if(j.gete().getn() == "hack"){

			affichageHacking();
		

			update();

			if(j.geth().getnbSaisie() == 4){

				j.sete(2);
				affichageHacking();
				d = 1;
			}
		}

		if(j.gete().getn() == "clicker"){

			affichageClicker();
			update();

			if(j.getc().gettps_actuel()>10){
				
				j.sete(2);
				d =1;
			}
		}
	}
}


//permet d'effacer pour pouvoir ré écrire dessus
void Vide(){

		cout<<"                                                                                                    "<<endl;
		cout<<"                                                                                                    "<<endl;
		cout<<"                                                                                                    "<<endl;
		cout<<"                                                                                                    "<<endl;
		cout<<"                                                                                                    "<<endl;
		cout<<"                                                                                                    "<<endl;
		
}


//permet l'affichage txt de l'évenement hacking
void jeuTXT::affichageHacking(){

	jeuClear();

	unsigned int cas = j.geth().getIntAff();

	switch(cas){
		case 2 : // premier affiche, quand le hack commence
			cout<<"Vous devez tapez la commande suivante pour gagné : "<<j.geth().getMot()<<endl;
			cout<<j.geth().getMotSaisie();
			break;

		case 0: // affiche quand le mot tapé précédement est correcte
			cout<<"commande validé!"<<endl<<"Commande suivante : "<<j.geth().getMot()<<endl;
			cout<<j.geth().getMotSaisie();
			break;

		case 1: // affichage quand le mot tapé précédement est incorrecte
			cout<<"commande non validé!"<<endl<<"re-tapez la commande : "<<j.geth().getMot()<<endl;
			cout<<j.geth().getMotSaisie();
			break;

		case 3: // enleve l'affichage précédent avant l'affichage suivant
			Vide();
			j.seth(1);
			break;

		case 4:	// enleve l'affichage précédent avant l'affichage de la fin
			Vide();
			j.seth(2);
			break;
	}

	//affichage de la fin
	if(j.geth().getnbSaisie()==4)

	{
		if(j.gete().getT() == true){
			cout<<"Vous avez GAGNE en "<<j.gete().gettps()<<" seconde                                           "<<endl;
		}

		else{
			cout<<"Vous avez PERDU en "<<j.gete().gettps()<<" seconde                                           "<<endl;
		}

	}

}


//permet de mettre a jour les objets suite à l'appuie d'une touche
void jeuTXT::update(){

	string touche;

	if((kbhit())&&(rep)){
		rep = false;
		touche = fgetc(stdin);
		j.actionClavier(touche);

	}
	else{rep = true;}
}


//permet d'afficher le clicker
void jeuTXT::affichageClicker(){

	jeuClear();

	cout << "Timer : " << 10 - j.getc().gettps_actuel() <<" seconde"<< endl;
	cout<< "Appuyez à répétion sur espace pour faire de la pub!"<<endl<<endl;

	cout<<"nombre de pub réalisé : "<< j.getc().getnbclique()<<". "<<endl;

	if (j.getc().gettps_actuel() >= 10){

		cout<<"TERMINER!"<<endl;
		cout<<"Vous gagner "<<j.gete().getgain()<<" $"<<endl;

	}
}
	
