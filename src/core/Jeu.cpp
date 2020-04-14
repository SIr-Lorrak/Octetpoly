#include <assert.h>
#include <time.h>
#include <unistd.h>

#include "Jeu.h"

using namespace std;

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};//suite de 10 touches pour activer le konami code

//-------------------------------------Constructeurs--------------------------------------

bool estPasDans(const unsigned int n, const unsigned int tab[],const unsigned int taille = 4){
	if(taille == 0) return true;
	for(unsigned int i=0;i<taille;i++){
		if(tab[i]==n) return false;
	}
	return true;
}

//-------------------------------------Constructeurs---------------------------
Jeu::Jeu(){
	srand(time(NULL));

	konamiCode("");

	attendreNom = false;
	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	vend = false;
	actionObligatoire = true;
	nouvellePartie = false;
	chance = NULL;
	quitte = false;

	pause = false;

	tourOrdi = false;

	nbJoueur = 0;
	nbTour = 0;
	coeffAd = 1.0;

	tabO = NULL;
	unsigned int alea;
	alea = 0;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
	joueurCourant = ordre[0];//au début le joueur courant est le dernier joueur comme ça quand on commence le jeu ça sera au premier joueur de jouer
}

void Jeu::reset()
{
	
	if(tabO!=NULL){
		delete [] tabO;
	}
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
	srand(time(NULL));

	konamiCode("");

	attendreNom = false;
	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	vend = false;
	actionObligatoire = true;
	nouvellePartie = false;
	chance = NULL;
	quitte = false;

	pause = false;

	tourOrdi = false;

	nbJoueur = 0;
	nbTour = 0;
	coeffAd = 1.0;

	tabO = NULL;
	unsigned int alea;
	alea = 0;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
	joueurCourant = ordre[0];
}

//-------------------------------------Méthodes--------------------------------
void Jeu::getOrdre(unsigned int tab[4]) const
{
	for(int i =0; i<4 ; i++){ tab[i] = ordre[i];}
}

Case & Jeu::getJCase(const unsigned int i)
{
	return *board.getCase(i);
}

bool Jeu::getBool(const string & type) const
{
	if(type=="attendreNom")
		return attendreNom;
	else if(type=="avance")
		return avance;
	else if(type=="confirmation")
		return confirmation;
	else if(type=="desLance")
		return desLance;
	else if(type=="tourOrdi")
		return tourOrdi;
	else if(type=="attendreAmplete")
		return attendreAmplete;
	else if(type=="actionObligatoire")
		return actionObligatoire;
	else if(type=="quitte")
		return quitte;
	else if(type=="pause")
		return pause;
	else if(type=="nouvellePartie")
		return nouvellePartie;
	else
		assert(false);
}

Joueur * Jeu::getJoueur(const unsigned int i) const
{
	assert(tabJ[i-1]!=NULL);
	assert(nbJoueur>=i);
	return tabJ[i-1];
}

Ordi * Jeu::getOrdi(const unsigned int i) const
{
	assert(tabO!=NULL);
	assert(nbJoueur<i);
	return &tabO[i-nbJoueur-1];
}

Pion * Jeu::getPion(const unsigned int i) const
{
	assert(i<=4&&i>0);
	if(i<=nbJoueur){
		return getJoueur(i)->getPion();
	}

	else{
		return getOrdi(i)->getPion();
	}
}

unsigned int Jeu::getNbJoueur()const
{
	return nbJoueur;
}

unsigned int Jeu::getNbTour() const
{
	return nbTour;
}

unsigned int Jeu::getJoueurCourant()const
{
	return joueurCourant;
}

Carte * Jeu::getCarte()const
{
	return chance;
}

//transforme une chaine de caractère avec des espaces en remplacent les expaces par des underscores _
string SpaceToUnderscore(const string & nom){
	string nomr = nom;
	unsigned int i= 0;
	while(nom.c_str()[i] != '\0'){
		if(nom[i]==' '){
			nomr[i]='_';
		}
		i++;
	}
	return nomr;
}

//transforme une chaine de caractère sans espace en remplacent les underscores _ par des espaces
string UnderscoreToSpace(const string & nom){
	string nomr = nom;
	unsigned int i= 0;
	while(nom[i] != '\0'){
		if(nom[i]=='_'){
			nomr[i]=' ';
		}
		i++;
	}
	return nomr;
}

void Jeu::sauver(const string & file) const
{
	ofstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	fichier<<"OCTETPOLY666"<<endl<<nbJoueur<<endl;
	for(unsigned int i = 0;i<4;i++){
		fichier<<ordre[i]<<" ";
	}
	fichier<<endl<<joueurCourant<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<SpaceToUnderscore(getPion(i)->getNom())<<" ";//nom des Joueurs
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getPos()<<" ";//position des Joueurs
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getCoin()<<" ";//argents des Joueurs
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getKarma()<<" ";
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		if(getPion(i)->getPrisonnier()){
			fichier<<"1 ";
		}
		else{
			fichier<<"0 ";
		}
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		if(getPion(i)->getTicket()){
			fichier<<"1 ";
		}
		else{
			fichier<<"0 ";
		}
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getCar()<<" ";
	}
	fichier<<endl;
	fichier<<0<<endl;
	//<<board.getCasePub()<<endl;
	for(unsigned int i = 0;i<32;i++){
		const Case * c = board.getCase(i);
		fichier<<c->getPrix()<<" "<<c->getLoyer()<<" "
		<<c->getPrixDeVente()<<" "<<c->getPrixM()<<" "
		<<c->getPrixB()<<" "<<c->getOccupation()<<" "
		<<c->getInvestissement()<<endl;
	}
	for(unsigned int i = 1;i<=4;i++){
		Pion * p = getPion(i);
		fichier<<p->getNbPropriete()<<endl;
		for(unsigned int j=0;j<p->getNbPropriete();j++){
			fichier<<board.getIndice(p->getPropriete(j)->getNom())<<" ";
		}
		fichier<<endl;
	}
	fichier.close();
}


bool Jeu::charger(const string & file)
{
	bool valide = true;
	ifstream fichier(file.c_str());
	assert(fichier.is_open());
	string recup;
	int recupint;
	fichier>>recup;
	if(recup == "OCTETPOLY666"){
		fichier>>nbJoueur;
		for(unsigned int i=0;i<4;i++){
			tabJ[i]=new Joueur;
		}
		tabO = new Ordi [4-nbJoueur];

		for(unsigned int i= 0; i<4;i++){
			fichier>>ordre[i];
		}
		fichier>>joueurCourant;
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recup;
			getPion(i)->setNom(UnderscoreToSpace(recup));
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setPos(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setCoin(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setKarma(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			if(recupint==1){
				getPion(i)->setPrisonnier();
			}
		}
		for(unsigned int i=1;i<=4;i++){
			fichier>>recupint;
			if(recupint == 1){
				getPion(i)->donTicket();
			}
		}
		for(unsigned int i=1;i<=4;i++){
			fichier>>recup;
			getPion(i)->setCar(recup[0]);
		}
		fichier>>recupint;
		if(recupint!=0){
			//championat du monde (casePub dans plateau)
		}
		for(unsigned int i = 0;i<32;i++){
			//initCase(prix loyer prixdevente prixM prixB proprio investissement)
			//if(i == board.getCasePub()){

			//}
		}

		for(unsigned int i=1;i<=4;i++){
			unsigned int nbProp;
			fichier>>nbProp;
			for(unsigned int j=0;j<nbProp;j++){
				fichier>>recupint;
				//getPion(i)->don(board.getCase(recupint));
			}
		}
		//TODO
	}
	else{
		valide = false;
	}

	fichier.close();
	commencerPartie();
	return valide;
}

bool fichierExiste(const string & file)
{
	bool retour;
	ifstream fichier(file.c_str());
	retour = fichier.is_open();
	if(retour){
		string format;
		fichier>>format;
		if(format != "OCTETPOLY666"){
			retour = false;
		}
	}
	fichier.close();
	return retour;
}

void Jeu::konamiCode(const string touche)
{
	//TODO
}

bool nomExiste(const string & nom,const Ordi o[],unsigned int n){
	if(n!=0){
		for(unsigned int i=0;i<n;i++){
			if(o[i].getNom()==nom){
				return true;
			}
		}
	}
	return false;
}


void Jeu::commencerPartie()
{	
	
	if(nbJoueur<4){
		delete [] tabO;
		tabO = new Ordi [4-nbJoueur];
	
		do{
			for(unsigned int i = 1;i<4-nbJoueur;i++){
				do{
					tabO[i].nomAleatoire();
				}while(nomExiste(tabO[i].getNom(),tabO,i));//tant que deux Ordi on le même nom on relance la tirage au sort des nom
			}
		}while(!nomExiste("[bot] M. Pronost le meilleur prof de la terre",tabO,4-nbJoueur));
	}
	tourSuivant();
}


void Jeu::ajouterJoueur()
{
	tabJ[nbJoueur] = new Joueur;
	tabJ[nbJoueur]->setRang(nbJoueur+1);
	nbJoueur++;
	attendreNom = true;
}


void Jeu::enleverJoueur()
{
	nbJoueur--;
	delete tabJ[nbJoueur];
}


void Jeu::ajouterLettre(const unsigned int n, const string lettre)
{
	assert(n<nbJoueur);
	tabJ[n]->ajouterLettre(lettre);
}


void Jeu::resetBool()
{
	konamiCode("");

	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	actionObligatoire = true;
	vend = false;
}

void Jeu::tourSuivant(){
	nbTour++;
	unsigned int i=0;
	if(nbTour>1){
		while(joueurCourant!=ordre[i]){
			i++;
		}

		joueurCourant = ordre[(i+1)%4];
	}

	resetBool();
	if(joueurCourant>nbJoueur) tourOrdi = true ;
	else tourOrdi = false ;
}


void Jeu::actionPartie(const string & touche)
{
	Pion *p = getPion(joueurCourant);
	/*if(p->getPrisonnier()){

	}*/
	if(p->getPrisonnier()){
		if(avance||desLance){
			if(touche == "\n"){
				tourSuivant();
			}
		}
		else{
			if(touche == "1"){
				p->lanceDes();
				desLance = true;
			}
		}
	}
	if(!p->getPrisonnier()){
		if(!desLance){
			if(touche == "\n"){
				p->lanceDes();
				desLance = true;
			}
		}
		else if(!avance){
			if(touche == "\n"){
				p->avancer();
				avance = true;
			}
		}
		else if(attendreAmplete||actionObligatoire){//tant que les action obligatoire et les amplète non pas été faite sur une case alors on attend
			if(vend){
				actionVente(touche);
			}
			else{
				actionCase(touche);
			}
		}
		else{
			if(p->getDes().D1==p->getDes().D2){
				resetBool();//si le pion a fait un double on reset le tour a zero et il rejoue sans passer au tour suivant
			}
			else{
				if(tourOrdi){//si le tour n'a pas été reset alors on ne fini pas le tour
					tourSuivant();
				}
				
				else{
					if(touche=="\n"){// de même si le tour est pas reset on declenche un mini jeu et on termine le tour
						if(!e.Declenchement()){
							tourSuivant();
						}
					}
				}
			}
		}
	}
}


void Jeu::actionMenu(const string & touche)
{	if(nouvellePartie){
		if(!attendreNom&&nbJoueur<4){
			if(!confirmation){//si on attend une confirmation pour commencer on n'attend plus d'ajout de joueur
				if(touche == "+"||touche == "="){
					ajouterJoueur();//1 ajoute un joueur quand on appuie sur plus et attend son nom
				}

				if(touche == "-"&&nbJoueur>0){
					enleverJoueur();//enleve le dernier joueur ajouté
				}
			}

			if(touche == "\n"||((touche=="o"||touche=="O")&&confirmation)){
				if(confirmation){
					commencerPartie();//si c'est confirmé on commence la partie
					confirmation=false;
				}

				confirmation = true;//on demande confirmation
			}

			if(touche=="n"||touche=="N"){
				confirmation=false;//si ça n'est pas confirmer on ne commence pas la partie et on reprend la selection des joueurs
			}
		}

		else if(attendreNom){//un joueur ajouter na pas encore de nom
			if(touche == "\n"){// \n c'est pour 'entrer' ou 'retour'
				attendreNom = false;//2 entrer valide le nom du joueur
			}

			else if(touche[0]==127||touche[0]==8||touche[0]=='\b'){// = pour 'effacer'
				tabJ[nbJoueur-1]->effacerLettre();
			}

			else{
				ajouterLettre(nbJoueur-1,touche);//ajoute la lettre rentrer dans le nom du joueur
			}
		}

		if(nbJoueur==4&&!attendreNom){
			if((touche=="o"||touche=="O"||touche=="\n")&&confirmation){
				confirmation = false;
				commencerPartie();
			}

			if(!confirmation) confirmation = true;

			else if(touche=="n"||touche=="N"||touche=="-"){
				confirmation = false;
				enleverJoueur();
			}

		}
		if(touche=="\e"){
			nouvellePartie=false;//passe dans le menu précédent
		}
	}
	else{
		if(!attendreNom){
			if(touche=="1"){//première option : le joueur veut faire une nouvelle partie
				nouvellePartie = true;
			}
			else if(touche=="2"){//deuxième option : le joueur veut charger une partie existante
				attendreNom = true;//on attend le choix du nom de la sauvegarde
			}
			if(touche=="3"||touche=="\e"){
				quitte = true;//echap sur le menu d'origine quitte le jeu.
			}
		}
		else{
			if(touche =="1"||touche == "2"||touche =="3"){
				if(fichierExiste("data/sauvegarde/"+touche+".save")){
					if(charger("data/sauvegarde/"+touche+".save")){
						invalidSave = false;
					}

					else{
						invalidSave = true;//fichier corrompu
					}
				}
			}
			if(touche=="\e"){
				attendreNom = false;//passe dans le menu précédent
			}
		}
	}
}

void Jeu::investirEJoueur(const string touche){
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());
	Pion * p = getPion(joueurCourant);

	//Est-ce que le joueurCourant veux investir
	//Est-ce que le joueurCourant a assez d'argent
	if(touche == "+" && p->getCoin() >= c->getPrixB())
	{
		p->investit(1,c);//si oui il investit
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (touche == "-" && p->getCoin() >= c->getPrixM())
	{
		p->investit(-1,c);//si oui il investit
	}

	else if (touche == "\n"){
		attendreAmplete = false;
	}
}

void Jeu::actionBE(const string touche){

	//La case où se trouve le JOUEUR
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	//A quel joueur appartient la case
	unsigned int occupant = c->getOccupation();

	//L'argent actuel du JOUEUR

//Vérifie si la case n'appartient pas au JOUEUR
	if(occupant != joueurCourant)
	{	
		if(occupant != 0 && actionObligatoire){// La case appartient a une autre personne
			if(touche == "\n"){
				payeLoyerJoueur();
			}
		}

		else//La case n'appartient a personne
		{
			actionObligatoire = false;//le joueur na pas de loyer a payer
			//N'appartient à personne,le JOUEUR peut acheter la banque ou l'entreprise
			//Est-ce que le JOUEUR veut acheter
			//Et est-ce qu'il a assez d'argent pour
			if(getPion(joueurCourant)->getCoin()<c->getPrix()){
				attendreAmplete = false;
			}
			if((touche == "o" ||touche == "O") && attendreAmplete)
			{
				getPion(joueurCourant)->achete(c);
				if(c->getType()=='B'){//si c'est une banque acheté alors le joueur ne peut plus faire d'amplètes (pas d'investissement sur les banques)
					attendreAmplete = false;
				}
						
			}
			else{
				attendreAmplete = false;//si le joueur n'achete pas alors il a fini.
			}
		}
	}

	//La case appartient au JOUEUR	
	//Si c'est une entreprise, il pourra peut-être investir
	else if (c->getType() == 'E'&&attendreAmplete)
	{
		actionObligatoire = false;// le joueur n'a pas de loyer a payer
		investirEJoueur(touche);
	}
}

void Jeu::paye(unsigned int payeur, unsigned int creancier, float montant){
	assert((payeur <= 4 || payeur > 0) && (creancier <= 4 || creancier > 0));
	//Echange entre ordi
	if(payeur > nbJoueur && creancier > nbJoueur)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC+montant);
	}

	//Le payeur est un joueur ; Le creancier est un ordi
	else if(payeur <= nbJoueur && creancier > nbJoueur)
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC+montant);
	}
	
	//Le payeur est un ordi ; Le creancier est un joueur
	else if(payeur > nbJoueur && creancier <= nbJoueur)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC+montant);	
	}
	//Echange entre joueur
	else
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC+montant);
	}
	//pour guillaume => faut vraiment changer cette fonction en utilisant getPion
}


void Jeu::payeLoyerJoueur(){
//C'est un joueur qui joue	
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	unsigned int coinCourant = getPion(joueurCourant)->getCoin();

	//Le joueurCourant paye directement si il a assez d'argent 
	if(coinCourant >= c->getLoyer())
	{
		paye(joueurCourant,c->getOccupation(),c->getLoyer());
		actionObligatoire = false;//si le pion paye alors c'est bon il a fait ces actions obligatoires
	}

	//Le joueurCourant doit vendre pour payer le loyer
	else if((coinCourant + getPion(joueurCourant)->patrimoineActif()) >= c->getLoyer())
	{
		//on passe dans l'interface de vente (c'est a dire on passe le booléen vend a true et c'est tout)
		/*while(getPion(joueurCourant)->getCoin() < 0)//pour guillaume => /!\ pas de while ici car code d'execute déjà dans une boucle infinie on fera un if
		{
			//getPion(joueurCourant)->vend(); on passe dans l'interface de vente
		}*/
	}
	else
	{
		//en faillite le pion donne le reste de son argent au pion qu'il doit payer
		//puis on appele une fonction Pion::faitFaillite() qui mettra l'argent du pion a -1
		//tourSuivant(); //si le pion fait faillite on passe au tour d'après
	}
}

void Jeu::pub(unsigned int quelleCase){
	/*if (quelleCase == casePub)
	{
		coeffAd++;
		Case * championnat = board.getCase(casePub);
		championnat->advertising(coeffAd);

	}
	else
	{
		if (casePub == 0)
		{
			Case * exChampionnat = board.getCase(casePub);
			exChampionnat->endAdvertising(coeffAd);

			casePub = quelleCase;
			coeffAd = 2;
			Case * championnat = board.getCase(quelleCase);
			championnat->advertising(coeffAd);
		}
		else
		{	
			casePub = quelleCase;
			coeffAd = 2;
			Case * championnat = board.getCase(quelleCase);
			championnat->advertising(coeffAd);
		}		
	} */
	//pour guillaume => casePub devrait être un booléen dans case les calcules de prix doivent d'ailleur se dérouler dans case (fonction Case::organisePub())
	//je te recommande de regarder la fonction actionBE que j'ai juste un tout petit peu modifié pour qu'elle est le bon comportement.
}

void Jeu::campagneDePub(const string touche){
	Case * c = board.getCase(16);//ATTENTION APPEL FRAUDULEUX
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();
	if(coinCourant >= c->getPrix())
	{
		unsigned int Case = 1;//TODO
		pub(Case);
		getPion(joueurCourant)->setCoin(coinCourant - c->getPrix());	
	}
	//pour guillaume ne pas oublier que le joueur doit appuyer sur une touche d'abord pour dire si'il veut mettre une pub SI IL PEUT
	//puis après ouvrir un menu qui lui montre ses propriété pour qu'il choisisse où la mettre
	//ça doit donc ce dérouler en deux temps (utilise le booléen choix)
}

void Jeu::carteChance(const string & touche){
	Pion * joueur = getPion(joueurCourant); 
	int id_Case;
	int gain;
	bool casePlus3;
	attendreAmplete = false; //le joueur ne fera pas d'amplete sur une carte chance.
	if(chance == NULL){//si une la carte n'a pas encore été tirée.{
		if(touche == "\n")//le joueur pioche une carte avec entrer 
		{
			chance = new Carte;
			chance->randomCarte();
		}
	}
	else{//si la carte est déjà tirée

		id_Case = chance->getid_case();
		gain = chance->getgain();
		casePlus3 = chance->getcasePlus3();
		if(touche=="\n"){//le joueur appuie a nouveau sur entrer après qu'il est lu ça carte
			joueur->setCoin(joueur->getCoin() + gain);//le gain peut aussi être une perte.
			if(id_Case == 0)
			{
				joueur->setPos(0);
				joueur->salaire();
			}
			else if(casePlus3)
			{
				joueur->setPos(joueur->getPos() + 3);
				if(joueur->getPos() > 31)
				{
					joueur->setPos(joueur->getPos() - 32);
				}
			}
			//n'oublie pas que si le joueur n'a pas l'argent pour payer il doit vendre donc passer dans l'interface de vente (je m'occuperais de l'interface de vente)
			actionObligatoire = false; //si le joueur a pu payer il a fini ses action obligatoire	
			delete chance;//puis on delete la carte chance
			chance = NULL;//<-- très important
		}
	}
}

void Jeu::actionCase(const string & touche){

	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	switch(c->getType()){
		case 'E':
			actionBE(touche);
			break;

		case 'B':
			actionBE(touche);
			break;

		case 'C':
			carteChance(touche);
			break;

		case 'A':
			attendreAmplete= false;
			actionObligatoire = false;
			//campagneDePub(touche);
			break;

		case 'O':
			attendreAmplete= false;
			actionObligatoire = false;
			//porteOuverte();
			break;

		case 'I':
			attendreAmplete= false;
			actionObligatoire = false;
			//TODO 
			break;

		case 'P':
			//prison(); la prison est gèré differement car elle est là seul case qui agit avant le début du tour 
			break;
	}
}

//permet d'effectuer une action selon la touche appuyer
void Jeu::actionMiniJeu(const string touche){

	//si nous sommes dans l'évenement hacking
	if (e.getn() =="hack"){
		if(!h.getFin()){
			if (touche == "\n"){
				h.valider();
			}
			else if(touche[0]==127||touche[0]==8||touche[0]=='\b'){
				h.effacerLettre();
			}
			else{
				h.saisir(touche);
			}
		}
		else{

			if (touche == "\n"){
				e.reset();
				h.resetHack();
				//TODO : faire les gains / pertes avant de passer au tour suivant /si le joueur.
				tourSuivant();
			}
		}
		if(h.getFin()){
			if(e.getTempsF()==0){
				e.fini();
			}
		}
	}
	if(e.getn() == "clicker"){
		if(touche == " "){
			c.ajoutClique(gete().gettempsD());
		}
	}
}

void Jeu::actionPause(const string & touche){
	if(touche=="\e"||touche=="1"){
		pause=false;
	}
	else if(touche=="2"){
		//choix d'un fichier de sauvegarde
	}
	else if(touche=="3"){
		reset();
	}
	else if(touche=="4"){
		quitte= true;
	}
}

void Jeu::actionVente(const string & touche){
	return;
}

void Jeu::actionClavier(const string & touche)
{
	if(nbTour == 0){
		actionMenu(touche);
	}
	else if(pause){
		actionPause(touche);
	}
	else if(e.getn()=="rien"){
		if(touche=="\e"){
			pause = true;
		}
		else{
			konamiCode(touche);//pour le konami code
			actionPartie(touche);
		}
	}
	else{
		actionMiniJeu(touche);
	}
}

void Jeu::actionOrdi(){
	if(!desLance&&getPion(joueurCourant)->getPrisonnier()){
		actionClavier("1");
	}
	actionClavier("\n");
	//Ordi o = *getOrdi(joueurCourant);
	/*if(avance){
		if(o.AIacheteEntreprise(*board.getCase(o.getPos()))){
			actionCase("o");
		}
	}*/
}



//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement();
			break;

		case 2:
			e.fini();
			break;

	}
}


//seteur permetant de mettre à jour hacking h
void Jeu::seth(unsigned int n){
	assert(n==1||n==2);
	h.intAff = n-1;
}


// permet de retourner l'évenement e
Evenement Jeu::gete(){

	return e;

}


//permet de retourner hacking h
Hacking Jeu::geth(){

	return h;

}

//retourne clicker c
Clicker Jeu::getc(){

	return c;

}


//seteur permettant de mettre à jour clicker c
void Jeu::setc(){

	c.resetClicker();

}

void Jeu::testRegression(){
	Jeu j;
	j.commencerPartie();
	j.sauver("data/sauvegarde/test.save");
	Jeu y;
	y.charger("data/sauvegarde/test.save");
	y.tourSuivant();
	y.tourSuivant();
	y.sauver("data/sauvegarde/toast.save");
}


Jeu::~Jeu(){
	if(tabO!=NULL){
		delete [] tabO;
	}
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}
