#include "JeuTXT.h"
//#include "Evenement.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <assert.h>
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

void setTerm(){
	#ifndef _WIN32
		system("setterm -cursor off");
	#endif
	termios term;
	tcgetattr(0,&term);
	term.c_lflag &= ~ICANON;
	tcsetattr(0,TCSANOW,&term);

}



void clear(){
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

void restoreTerm(){
	#ifndef _WIN32
		system("setterm -cursor on");
	#endif
	termios term;
	tcgetattr(0,&term);
	tcsetattr(0,TCSANOW,&term);
	clear();
}

//constructeur, vide le terminal
JeuTXT::JeuTXT(){
	clear();
	action=true;
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



//permet d'effacer si la ligne précédente était plus grande avant de retourner a là ligne
void Endl(){

		cout<<"     "<<endl;
		
}

//affiche un curseur a la suite du texte
void curseur(){
	
	if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%51<25){
		cout<<"|";
	}
}

//permet l'affichage txt de jolie Dés UwU
void affichageDes(unsigned int a, unsigned int b){
	assert(a>0&&a<=6);assert(b>0&&b<=6);
	unsigned int d[2] = {a,b};
	unsigned int i;
	cout<<"   ___     ___ "<<endl;
	cout<<"  /__ /|  /__ /|"<<endl;
	/*      |o o| | |o  | |	*/ for(i=0;i<2;i++){cout<<" |";if(d[i]!=1) cout<<"o ";else cout<<"  ";if(d[i]>3)cout<<"o";else cout<<" ";cout<<"| |";}cout<<endl;
	/*      | o | | | o | |	*/ for(i=0;i<2;i++){cout<<" |";if(d[i]==6) cout<<"o";else cout<<" ";if(d[i]%2==0)cout<<" ";else cout<<"o";if(d[i]==6) cout<<"o";else cout<<" ";cout<<"| |";}cout<<endl;
	/*      |o o|/  |  o|/	*/ for(i=0;i<2;i++){cout<<" |";if(d[i]>3) cout<<"o ";else cout<<"  ";if(d[i]!=1)cout<<"o";else cout<<" ";cout<<"|/ ";}cout<<endl;	
	cout<<"  ¯¯¯     ¯¯¯   "<<endl;
}


//permet d'afficher le clicker
/*void JeuTXT::affichageClicker(){

	jeuClear();

	cout << "Timer : " << 10 - j.getc().gettps_actuel() <<" seconde"<< endl;
	cout<< "Appuyez à répétion sur espace pour faire de la pub!"<<endl<<endl;

	cout<<"nombre de pub réalisé : "<< j.getc().getnbclique()<<". "<<endl;

	if (j.getc().gettps_actuel() >= 10){

		cout<<"TERMINER!"<<endl;
		cout<<"Vous gagner "<<j.gete().getgain()<<" $"<<endl;

	}
}*/

//permet l'affichage txt de l'évenement hacking
void JeuTXT::affichageHacking(){

	unsigned int cas = j.geth().getIntAff();//affichage de la fin

	if(j.geth().getFin())
	{
		if(j.gete().getT() == true){
			cout<<"Vous avez GAGNE en "<<j.gete().gettps()<<" seconde";Endl();
		}

		else{
			cout<<"Vous avez PERDU en "<<j.gete().gettps()<<" seconde";Endl();
		}

	}
	else{
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
	}
}

void affichePion(const Pion & p){
	cout<<p.getNom()<<"  : "<<p.getCoin()<<"k $"<<endl;	
}

void JeuTXT::affichageJeu(){
	cout<<"tour : "<<j.getNbTour()<<endl;
	Pion joueurCourant;
	joueurCourant = *j.getPion(j.getJoueurCourant());
	unsigned int pos = joueurCourant.getPos();
	cout<<"vous êtes sur la case : "<<pos<<endl;

	if(j.getJCase(pos).getType()=='E'||j.getJCase(pos).getType()=='B'){
		cout<<"loyer : "<<j.getJCase(pos).getLoyer()<<endl;
		cout<<"Prix : "<<j.getJCase(pos).getPrix()<<endl;
	}

	if(j.getBool("desLance")){
		affichageDes(joueurCourant.getDes().D1,joueurCourant.getDes().D2);
	}

	else{
		cout<<"Lancez les dés avec \"entrer\"!"<<endl;
	}

	if(j.getBool("avance")){
		cout<<"vous avez avancé..."<<endl;
	}

	if(j.getBool("tourOrdi")){
		cout<<"[bot]"<<endl;
	}

	cout<<"###-----------liste des Joueurs-----------###"<<endl;

	for(unsigned int i =1;i<=4;i++){
		cout<<i<<"e - " ;
		affichePion(*j.getPion(i));
	}
	unsigned int tab[4];
	j.getOrdre(tab);
	cout<<"Ordre : ";
	for(unsigned int i = 0;i<4;i++){
		if(j.getJoueurCourant()==tab[i]){
			cout<<"("<<tab[i]<<")";
		}

		else{
			cout<<tab[i];
		}

		cout<<">";
	}
	cout<<endl;
}

void JeuTXT::affichageMenu(){
	cout<<"<[-($)-]-_-¯-_-¯-OCTETPOLY-¯-_-¯-_-[-($)-]>"<<endl<<endl;
	unsigned int nbj = j.getNbJoueur();
	if(nbj>0){
		if(j.getBool("attendreNom")){
			cout<<nbj;
			if(nbj==1) cout<<"er";
			else cout<<"e";
			cout<<" joueur : "<<j.getJoueur(nbj)->getNom();curseur();Endl();
		}
		else{
			for(unsigned int i=1;i<=nbj;i++){
				cout<<i;
				if(i==1) cout<<"er";
				else cout<<"e";
				cout<<" joueur : ";
				if(j.getJoueur(i)->getNom()==""){
					cout<<"<anonyme>"<<endl;
				}
				else{
					cout<<j.getJoueur(i)->getNom()<<endl;
				}
			}
		}
	}
	if(j.getNbJoueur()<4){
		cout<<endl<<"apuyez sur \"+\" pour ajouter un joueur entrez un nom et validez avec entrer"<<endl;
	}
	if(j.getBool("confirmation")){
		cout<<"vous etes sur ? (o/n) ";Endl();
	}
	Endl();
}


void JeuTXT::affichage(){
	/*if(j.gete().getn() == "rien"){

			j.sete(1);//le déclanchement devra se faire autrement (a la fin d'un tour)
		}*/
	jeuClear();// on place le curseur au début du terminal avant de commencer a écrire

	if(j.getNbTour()==0){//la partie n'a pas encore commencer 
		affichageMenu();
	}

	else if(j.gete().getn() == "hack"){//le mini Jeu Hacking est en court
		affichageHacking();
	}
	else if(j.gete().getn()== "clicker"){
		//affichageClicker();
	}

	else{//aucun mini Jeu en cour et la partie a commencer
		affichageJeu();
	}
}

//permet de mettre a jour les objets suite à l'appuie d'une touche
bool JeuTXT::update(){

	string touche;

	if(kbhit()){
		touche = fgetc(stdin);
		if(!j.getBool("tourOrdi")){
			clear();

			j.actionClavier(touche);
		}
		
		if(touche=="\e"){
			return true;
		}
	}

	if(j.getBool("tourOrdi")){
		if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%151<75){
			if(action){
				clear();
				action = false;
				j.actionOrdi();// a intervalle régulier genre toutes les 5 secondes
			}
		}

		else{
			action = true;
		}
	}
	return false;
}
	

//permet le deroulement de la partie
// ATTENTION CETTE PARTIE EST A CHANGER ET ADAPTER AVEC LE DEROULEMENT DE LA PERTIE !!
void JeuTXT::run(){

	setTerm();

	int quit = false;
	
	while(!quit){
		affichage();
		quit = update();

		/*if(j.geth().getnbSaisie() == 4){
			j.sete(2);
		}*/
	}

	restoreTerm();
}