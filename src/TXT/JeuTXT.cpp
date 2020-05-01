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

//permet l'affichage txt de l'évenement hacking
void JeuTXT::affichageHacking(){

	unsigned int cas = j.geth().getIntAff();//affichage de la fin
	cout<<"progression : [";
	for(unsigned int i=0;i<j.geth().getnbMot();i++){
		if(i<j.geth().getnbSaisie()){
			cout<<"#";
		}
		else{
			cout<<" ";
		}
	}
	cout<<"]";Endl();
	if(j.geth().getFin())
	{
		if(j.gete().getT() == true){
			cout<<"Vous avez GAGNE en "<<j.gete().gettps()<<" seconde";Endl();
			cout<<"les hacker n'on pas eu le temps de vous voler";
		}

		else{
			cout<<"Vous avez PERDU en "<<j.gete().gettps()<<" seconde";Endl();
			cout<<"On vous a volé "<<j.gete().getgain()*-1<<"$ !"<<endl;
		}

	}
	else{
		cout<<"timer : "<<(clock()/CLOCKS_PER_SEC)-(j.gete().gettempsD()/CLOCKS_PER_SEC);
		Endl();
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
		cout<<j.geth().getMot();Endl();
		cout<<">"<<j.geth().getMotSaisie();
		curseur();
		Endl();
	}
}

//permet d'afficher le clicker
void JeuTXT::affichageClicker(){

	jeuClear();
	if (j.getc().getFin()==false){
		cout << "Timer : " << 10-((clock()/CLOCKS_PER_SEC)-(j.gete().gettempsD()/CLOCKS_PER_SEC)) <<" seconde";Endl();
		cout<< "Appuyez à répétion sur espace pour faire de la pub!";Endl();Endl();

		cout<<"nombre de pub réalisé : "<< j.getc().getnbclique()<<". ";Endl();
	}	
	else{

		cout<<"TERMINER! Vous avez réalisé "<<j.getc().getnbclique()<<". ";Endl();
		cout<<"Vous gagner "<<j.gete().getgain()<<" $                                   ";Endl();
		for(int i =0;i<21;i++){
			cout<<"                                                    "<<endl;
		}

	}

}


void JeuTXT::affichageEscape(){
	jeuClear();
	if(j.getes().getFin()==false){
		cout<<"Utilsez les touches Z, Q, S et D pour echapez rapidemant à la police";Endl();
		cout<<"Attention de ne pas quitter la route, sinon vous reculez!";Endl();Endl();
		for(int y=0;y<11;y++){
			for(int x=0;x<11;x++){
			
				
				if((j.getes().getJoueur().y == y)&&(j.getes().getJoueur().x == x)){
					cout<<" J ";
				}
				else if((j.getes().getPolice().y == y)&&(j.getes().getPolice().x == x)){
					cout<<" P ";
				}
				else if(tab_escape[y][x]=="M"){
					cout<<" M ";
				}
				else if(tab_escape[y][x]=="H"){
					cout<<" # ";
				}
				else if(tab_escape[y][x]=="RV"){
					cout<<" | ";
				}
				else if(tab_escape[y][x]=="RH"){
					cout<<" _ ";
				}
				else if(tab_escape[y][x]=="DEPART"){
					cout<<" D ";
				}
				else if(tab_escape[y][x]=="ARRIVE"){
					cout<<" A ";
				}
				else if(tab_escape[y][x]=="T1"){
					cout<<" / ";
				}
				else if(tab_escape[y][x]=="T2"){
					cout<<" / ";
				}
				else if(tab_escape[y][x]=="T3"){
					cout<<" / ";
				}
				else if(tab_escape[y][x]=="T4"){
					cout<<" / ";
				}

				if(x==10){
					Endl();Endl();
				}
				
			}
		}
	}
	if(j.getes().getFin()==true) {
		if(j.getes().getEchec()==true){
			cout<<"Vous n'avez pas reussit à vous echaper!                                  ";Endl();
			cout<< "direction la prison!                                             ";Endl();
		}
		else{
			
			cout<<"Vous avez reussit à vous echaper"                                                  ;Endl();
		}
		for(int i =0;i<30;i++){
			cout<<"                                                    "<<endl;
		}
	}

}


void JeuTXT::affichageLucky(){
	cout<<"<[-($)-]¯-_-¯-LUCKY-_-¯-_-[-($)-]>"<<endl<<endl;
	if(!j.getlu().getCartePiocher()){
		cout << "Quelle chance vous venez d'apercevoir deux cartes chances sur le sol" << endl;
		cout << "retournez-les" << endl;
	}

	else{
		cout << "Voici les deux cartes :" << endl;
		cout << endl <<   "Carte 1 " << endl << j.getlu().getCarteUn()->getTitre() << endl << j.getlu().getCarteUn()->getTexte() << endl;
		cout << endl <<   "Carte 2 " << endl << j.getlu().getCarteDeux()->getTitre() << endl << j.getlu().getCarteDeux()->getTexte() << endl;

		cout << endl << "Quelle carte voulez-vous garder ?" << endl;
		cout << "1/Carte 1" << endl;
		cout << "2/Carte 2" << endl;
		cout << "3/Aucune des deux" << endl;
	}

}

void affichePion(const Pion & p){
	if(p.getNom()==""){
		cout<<"<anonyme>";
	}
	cout<<p.getNom()<<"  : "<<p.getCoin()<<"k $"<<endl;	
}

void JeuTXT::affichageCase(const Case * c){
	Pion * p = j.getPion(j.getJoueurCourant());
	switch(c->getType()){
		case 'E':
			cout<<"vous ètes sur l'entreprise : "<<c->getNom()<<endl;
			break;
		case 'B':
			cout<<"vous ètes sur la banque : "<<c->getNom()<<endl;
			break;
		case 'D':
			cout<<"CASE DÉPART !"<<endl;
			break;
		case 'P':
			cout<<"bienvenue en Prison !"<<endl;
			if(j.getBool("desLance"))
			{
				cout <<"Appuyez sur entrer"<<endl;
			}
			else if(p->getPrisonnier()){
				cout <<"1. tentez de faire un double"<<endl;
				if(p->getCoin() >= j.getPrixAPayer()){
					cout <<"2. payez la cotion de "<<j.getPrixAPayer() <<" $"<<endl;
				}
			}
			break;
		case 'I':
			cout<<"Faut payer ses impots monsieur !"<<endl;
			if(j.getPrixAPayer() > 0)
			{
				cout << "Vous devez " << j.getPrixAPayer() << " Goldus à l'Etat !" << endl;
			}
			else
			{
				cout << "L'état vous remercie d'avoir payé vos impôt" << endl;	
			}
			break;
		case 'C':
			if(j.getCarte()==NULL){
				cout<<"piochez une carte chance !"<<endl;
			}
			else{
				cout<<"votre carte : "<<endl<<j.getCarte()->getTitre()<<endl<<j.getCarte()->getTexte()<<endl;
			}
			break;
		case 'A':
			cout<<"vous pouvez organiser une campagne de PUB !"<<endl;
			if (p->getNbPropriete() > 0 && p->getCoin() > j.board.getCase(j.board.getIndice("Campagne de pub"))->getPrix())
			{
				cout<<"Souhaitez-vous faire de la pub ? (o/n)"<<endl;
			}
			break;
		case 'O':
			cout<<"journée porte ouverte ! vous pouvez aller où vous voulez"<<endl;
			if (j.board.nbCaseFree() > 0
				 && p->getCoin() > j.board.getCase(j.board.getIndice("Porte Ouverte"))->getPrix()
				 && !p->getTicket())
			{
				cout<<"Souhaitez-vous acheter un ticket ? (o/n)"<<endl;
			}
			if(p->getTicket())
			{
				cout<<"Prêt pour les portes ouverte !"<<endl;
			}
			break;
		default:
			assert(false);
			break;
	}
	if(c->getType()=='E'||c->getType()=='B'){
		cout<<"groupe : " << c->getGroup() << endl;
		cout<<"loyer : "<<c->getLoyer()<<endl;
		cout<<"Prix : "<<c->getPrix()<<endl;
		cout<<"Propriétaire : ";
		if(c->getOccupation()==0){
			cout<<"personne"<<endl;
		}
		else{
			cout<<j.getPion(c->getOccupation())->getNom()<<endl;
			if(c->getType()=='E'){
				cout<<"investissement : "<<c->getInvestissement()<<endl;
			}
		}
		if(j.getBool("actionObligatoire")&&j.getBool("avance")&&c->getOccupation() != 0 && c->getOccupation()!=p->getRang()){//si il viens d'avancer et que la case est a quelqu'un d'autre
			cout<<"vous devez payer le loyer au joueur "<<c->getOccupation()<<" !"<<endl;
		}
		if(j.getBool("attendreAmplete")&&j.getBool("avance")){//si le pion a avance et qu'il na plus d'action obligatoire, il doit faire ces amplète
			if(c->getOccupation() == j.getJoueurCourant()){
				cout<<"+ pour investir dans le légal, - pour investir dans l'illégal."<<endl
				<<"/!\\ si vous avez déjà investit dans le légal, investir dans l'illégal enlèvera vos investissement précédent et inverssement !"<<endl;
			}

			else if(p->getCoin()>=c->getPrix()){
				if(c->getOccupation()==0){
					cout<<"voulez vous acheter cette case (o/n) ?"<<endl;
				}
				else if (!j.getBool("actionObligatoire") && j.board.getCase(p->getPos())->getType() == 'E'){
					cout<<"voulez vous exproprier cette case (o/n) pour " << j.board.getCase(p->getPos())->getPrix() << " Goldus ?" <<endl;
				}
			}
		}
	}
}

void JeuTXT::affichageJeu(){
	cout<<"tour : "<<j.getNbTour()<<endl;
	
	Pion * joueurCourant;
	joueurCourant = j.getPion(j.getJoueurCourant());
	unsigned int pos = joueurCourant->getPos();
	Case * c = j.board.getCase(pos);

	cout<<"case : "<<pos<<endl;

	affichageCase(c);

	if((j.getBool("desLance") || j.getBool("desLancePrison")) && !j.getBool("apresPorteOuverte")){
		affichageDes(joueurCourant->getDes().D1,joueurCourant->getDes().D2);
	}

	else if (!joueurCourant->getTicket() && !j.getBool("apresPorteOuverte")){
		cout<<"Lancez les dés avec \"entrer\"!"<<endl;
	}
	
	if(j.getBool("avance") && !joueurCourant->getTicket() && !j.getBool("apresPorteOuverte")){
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
	if(j.getBool("nouvellePartie")){//si le joueur crée une nouvelle partie
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
		cout<<endl<<"'ESC' pour revenir en arrière.";
	}
	else if(j.getBool("attendreNom")){// si le joueur selectione un fichier de sauvegarde (1,2 ou 3)
		cout<<endl;
		for(unsigned int i = 1;i<=3;i++){
			cout<<i<<". ";
			string fichier = "data/sauvegarde/";
			fichier += char(int('0')+i);
			if(!fichierExiste(fichier+".save")){
				cout<<"<empty file>"<<endl;
			}
			else{
				cout<<fichier+".save"<<endl;
			}
		}
		cout<<endl<<"'ESC' pour revenir en arrière.";
	}
	else{//Menu de départ
		cout<<endl<<"qu'est ce que vous voulez faire ?"<<endl<<
		"1. "<<"Nouvelle Partie"<<endl<<
		"2. "<<"Charger une Partie"<<endl<<
		"3. "<<"QUITTER"<<endl;
	}
}


void JeuTXT::affichagePause() const{

	cout<<"<------------pause------------>"<<endl;
	if(j.getBool("attendreNom")){
		cout<<endl;
		for(unsigned int i = 1;i<=3;i++){
			cout<<i<<". ";
			string fichier = "data/sauvegarde/";
			fichier += char(int('0')+i);
			if(!fichierExiste(fichier+".save")){
				cout<<"<empty file>"<<endl;
			}
			else{
				cout<<fichier+".save"<<endl;
			}
		}
		cout<<endl<<"'ESC' pour revenir en arrière.";
	}
	else{
		cout<<"1. Reprendre le Jeu"<<endl
		    <<"2. Sauvegarder"<<endl
		    <<"3. Revenir au Menu (/!\\ sans sauvegarder)"<<endl
		    <<"4. QUITTER (/!\\ sans sauvegarder)"<<endl;
	}
}


void JeuTXT::affichageCampagneDePub(){
	cout<<"<[-($)-]¯-_-¯-CAMPAGNE DE PUB-_-¯-_-[-($)-]>"<<endl<<endl;
	cout << "Pour quel quartier voulez vous faire de la pub" << endl;
	cout << "Voici votre/vos propriété(s) : " << endl;
	for (unsigned int i = 0; i < j.getPion(j.getJoueurCourant())->getNbPropriete() ; ++i)
	{
		cout << i << " " << (j.getPion(j.getJoueurCourant())->getPropriete(i))->getNom() << endl;
	}
	
	cout <<endl<< "Entrez le numéro du quartier : " << j.getChoix() << endl; 

	if(!j.getBool("confirmation")){
		cout<<"Confirmer (o/n) ";Endl();	
	}
}

void JeuTXT::affichagePorteOuvete(){
	cout<<"<[-($)-]¯-_-¯-PORTE OUVERTE-_-¯-_-[-($)-]>"<<endl<<endl;
	cout << "Vers quel voulez-vous vous rendre ?" << endl;
	cout << "Voici les quartier(s) disponible(s) : " << endl;
	
	for(unsigned int i = 0 ; i < 32 ; i++)
	{
		if(j.board.getCase(i)->getOccupation() == 0
			&& (j.board.getCase(i)->getType() == 'B'
			|| j.board.getCase(i)->getType() == 'E'))
		{
			cout << i << " " << j.board.getCase(i)->getNom() << endl;	
		}
	}
	
	cout <<endl<< "Entrez le numéro du quartier : " << j.getChoix() << endl; 

	if(!j.getBool("confirmation")){
		cout<<"Confirmer (o/n) ";Endl();	
	}
}

void JeuTXT::affichageVente(){
	Pion * p = j.getPion(j.getJoueurCourant());

	cout<<"<[-($)-]¯-_-¯-VENTE-_-¯-_-[-($)-]>"<<endl<<endl;
	cout << "Quel(s) quartier(s) voulez-vous vendre ?" << endl;
	cout << "Voici votre/vos propriété(s) : " << endl;
	for (unsigned int i = 0; i < p->getNbPropriete() ; ++i)
	{
		if(!j.dejaEnVente(i))
		{
		cout << i << " " << p->getPropriete(i)->getNom() << " | Prix de vente : " << p->getPropriete(i)->getPrixDeVente() << " Goldus" << endl;
		}
		else
		{
			cout << i << " " << p->getPropriete(i)->getNom() << " | VENDU" << endl;
		}
	}
	
	cout <<endl<< "Entrez le numéro du quartier : " << j.getChoix() << endl; 

	cout << "Appuyer sur + pour valider le quartier saisi" << endl;
	cout << "Appuyer sur - pour retirer le dernier quartier saisi" << endl;

	cout << "En prenant en compte la vente vous possédé : " 
			<< (p->getCoin() + j.totalVente()) << " Goldus" << endl;

	if(j.getPrixAPayer() - (p->getCoin() + j.totalVente()) > 0)
	{
	cout << "Il vous manque encore " << j.getPrixAPayer() - (p->getCoin() + j.totalVente())   << " Goldus pour vous acquitter de votre dette" << endl;			
	}
	else
	{
		cout << "Vous avez assez pour payer votre dette !" << endl;
	}

	cout << "Vous vendez : " << endl;

	for (unsigned int i = 0; i < j.getNbVente() ; ++i)
	{
		cout << " - " << j.getVente(i) << endl;
	}

	if(!j.getBool("confirmation")){
		cout<<"Confirmer (o/n) ";Endl();	
	}
}

void JeuTXT::affichageVictoire(){
	cout<<j.getPion(j.getVainqueur())->getNom()<<" a gagné gg a lui !"<<endl;
}



void JeuTXT::affichage(){
	/*if(j.gete().getn() == "rien"){

			j.sete(1);//le déclanchement devra se faire autrement (a la fin d'un tour)
		}*/
	jeuClear();// on place le curseur au début du terminal avant de commencer a écrire

	if(j.getNbTour()==0){//la partie n'a pas encore commencer 
		affichageMenu();
	}
	else if(j.getVainqueur()!=0){
		affichageVictoire();
	}
	else if(j.gete().getn() == "hack"){//le mini Jeu Hacking est en court
		affichageHacking();
	}
	else if(j.gete().getn()== "clicker"){
		affichageClicker();
	}
	else if(j.gete().getn()=="escape"){
		affichageEscape();
	}
	else if(j.gete().getn()=="lucky"){
		affichageLucky();
	}
	else if(j.getBool("pause")){
		affichagePause();
	}
	else if(j.getBool("ad")){
		affichageCampagneDePub();
	}
	else if(j.getBool("porteO")){
		affichagePorteOuvete();
	}
	else if(j.getBool("vend"))
	{
		affichageVente();
	}
	else{//aucun mini Jeu en cour et la partie a commencer
		affichageJeu();
	}
}

//permet de mettre a jour les objets suite à l'appuie d'une touche
void JeuTXT::update(){

	string touche;

	j.updateMiniJeu();

	if(kbhit()){
		touche = fgetc(stdin);
		clear();
		if(!j.getBool("tourOrdi")||touche=="\e"||j.getBool("pause")){
			j.actionClavier(touche);
		}
	}

	if(j.getBool("tourOrdi")&&!j.getBool("pause")){
		if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%101<50){
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
}
	

//permet le deroulement de la partie
// ATTENTION CETTE PARTIE EST A CHANGER ET ADAPTER AVEC LE DEROULEMENT DE LA PERTIE !!
void JeuTXT::run(){

	setTerm();//on met le terminal en non canonique, on enlève le curseur et on clear le texte.
	
	while(!j.getBool("quitte")){
		update(); 
		affichage();
	}

	restoreTerm(); //on restore le terminal comme avant et on le clear.
}