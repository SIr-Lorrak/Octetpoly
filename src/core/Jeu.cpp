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
	actionObligatoire = true;
	vend = false;
	ad = false;
	porteO = false;
	quitte = false;
	pause = false;
	Vainqueur=0;
	nouvellePartie = false;
	desLancePrison = false;
	choix = "";
	nbVente = 0;
	for (int i = 0; i < 24; ++i)
	{
		vente[i] = "";
	}
	prixAPayer = 0;
	chance = NULL;

	tourOrdi = false;

	nbJoueur = 0;
	nbTour = 0;

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


//-----------------------Méthodes-----------------------

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
	Vainqueur=0;

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

void Jeu::getOrdre(unsigned int tab[4]) const
{
	for(int i =0; i<4 ; i++){ tab[i] = ordre[i];}
}

Case & Jeu::getJCase(const unsigned int i)
{
	return *board.getCase(i);
}

string Jeu::getChoix() const
{
	return choix;
}

unsigned int Jeu::getPrixAPayer(){
	return prixAPayer;
}

string Jeu::getVente(unsigned int indice)
{
	return vente[indice];
}

unsigned int Jeu::getNbVente() 
{
	return nbVente;
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
	else if(type=="vend")
		return vend;
	else if(type=="ad")
		return ad;
	else if(type=="porteO")
		return porteO;
	else if(type=="quitte")
		return quitte;
	else if(type=="pause")
		return pause;
	else if(type=="nouvellePartie")
		return nouvellePartie;
	else if(type=="desLancePrison")
		return desLancePrison;
	else if(type=="apresPorteOuverte")
		return apresPorteOuverte;
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

unsigned int Jeu::getVainqueur() const
{
	return Vainqueur;
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
		if(getPion(i)->getNom().length()>0){
			fichier<<SpaceToUnderscore(getPion(i)->getNom())<<" ";//nom des Joueurs
		}
		else{
			fichier<<"<anonyme> ";
		}
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
	fichier<<board.getcasePub()<<endl;
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
		for(unsigned int i=0;i<nbJoueur;i++){
			tabJ[i]=new Joueur;
			tabJ[i]->setRang(i+1);
		}
		tabO = new Ordi [4-nbJoueur];
		for(unsigned int i=0;i<4-nbJoueur;i++){
			tabO[i].setRang(nbJoueur+i+1);
		}

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
			board.setcasePub(recupint);
		}
		for(unsigned int i = 0;i<32;i++){
			unsigned int prix,loyer,prixdevente,prixM,prixB,proprio;
			int investissement;
			fichier>>prix>>loyer>>prixdevente>>prixM>>prixB>>proprio>>investissement;
			board.setCase(i,prix,loyer,prixdevente,prixM,prixB,proprio,investissement);
		}

		for(unsigned int i=1;i<=4;i++){
			unsigned int nbProp;
			fichier>>nbProp;
			for(unsigned int j=0;j<nbProp;j++){
				fichier>>recupint;
				getPion(i)->don(board.getCase(recupint));
			}
		}
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
			for(unsigned int i = 0;i<4-nbJoueur;i++){
				do{
					tabO[i].nomAleatoire();
				}while(nomExiste(tabO[i].getNom(),tabO,i));//tant que deux Ordi on le même nom on relance la tirage au sort des nom
			}
		}while(!nomExiste("[bot] M. Pronost le meilleur prof de la terre",tabO,4-nbJoueur));
		for(unsigned int i=0;i<4-nbJoueur;i++){
			tabO[i].setRang(nbJoueur+i+1);
			tabO[i].setKarma(rand()%4-2);
		}
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


void Jeu::enleverJoueur(unsigned int n)
{
	if(n==0){//si n==0 c'est que la fonction a été appeler sans paramètre dans ce cas la on supprime le dernier joueur
		n=nbJoueur;
	}
	assert(n<=4);
	delete tabJ[n-1];//on suprimme le joueur souchaité
	for(unsigned int i=n-1;i<nbJoueur;i++){//on décale ensuite le reste des joueurs
		if(i==nbJoueur-1){
			tabJ[i]=NULL;
		}
		else{
			tabJ[i]=tabJ[i+1];
			tabJ[i]->setRang(tabJ[i]->getRang()-1);
		}
	}
	nbJoueur--;
}

void ajouterVente(){
	//Voir plus tard
}

void Jeu::enleverVente(){
	nbVente--;
	vente[nbVente] = "";
}


void Jeu::ajouterLettre(const unsigned int n, const string lettre)
{
	assert(n<nbJoueur);
	tabJ[n]->ajouterLettre(lettre);
}


void Jeu::ajouterNombre(const string nombre)
{
	choix+=nombre;
}


void Jeu::effacerNombre()
{
	choix = choix.substr(0, choix.size()-1);     
}

void Jeu::ecrire(const string touche){
	if(touche[0]==127||touche[0]==8||touche[0]=='\b')
	{// = pour 'effacer'
		effacerNombre();
	}		
	//On empêche l'utilisateur d'écrire autre chose qu'un chiffre
	else if(choix.length()<2 && (touche[0] >= 48 && touche[0] <= 57))
	{
		ajouterNombre(touche);
	}
}

unsigned int Jeu::totalVente(){
	unsigned int total = 0;
	for (unsigned int i = 0; i < nbVente; ++i)
	{
		total = total + board.getCase(board.getIndice(vente[i]))->getPrixDeVente();
	}
	return total;
}

void Jeu::modeVente(const string touche){
	if(!confirmation)
	{
		if(touche == "-" && nbVente > 0)
		{
			enleverVente();
		}

		else if(touche=="+"
			&& choix != ""
			&& stoul(choix) < getPion(joueurCourant)->getNbPropriete()
			&& stoul(choix) >= 0
			&& !dejaEnVente(stoul(choix)))
		{
			vente[nbVente] = getPion(joueurCourant)->getPropriete(stoul(choix))->getNom(); 
			nbVente++;
			choix = "";
		}

		if((touche=="o"|| touche=="O") 
		&& getPion(joueurCourant)->getCoin() + totalVente() >= prixAPayer)
		{
			confirmation = true;
		}


		else
		{
			ecrire(touche);
		}
	}

	if(confirmation)
	{
		//Deuxième confirmation
			
			remiseZeroEtVente();
			prixAPayer = 0;
			confirmation = false;
			vend = false;
			confirmation=false;
			
	}
}

void Jeu::remiseZeroEtVente(){
	for (unsigned int i = 0; i < nbVente; ++i)
	{
		getPion(joueurCourant)->vend(vente[i]);
		vente[i] = "";
	}
	nbVente = 0;
}

void Jeu::prixKarma(){
	Case * c = board.getCase(getPion(joueurCourant)->getPos());
	prixAPayer = c->getPrix();

	//Avec un karma positif, on paye entre 0% et 90% moins cher 
	if(getPion(joueurCourant)->getKarma() > 0)
	{
		prixAPayer = prixAPayer*(1+ (0.1-1)*(getPion(joueurCourant)->getKarma()-1)/(100-1));
	}
	//Avec un karma negatif, on paye entre 0% et 100% plus cher 
	else
	{
		prixAPayer = prixAPayer*(1+ (2-1)*(getPion(joueurCourant)->getKarma()-1)/(100-1));	
	}
}

void Jeu::victoireMonopole(){
	//Le joueur qui joue le tour
	Pion * p = getPion(joueurCourant);

	//Tableau des groupe de case
	//De 0 à 7 les groupes d'entreprises
	//8 le groupe banque
	unsigned int group[9] = {0,0,0,0,0,0,0,0,0};

	//On compte les monopole que posséde le joueur
	unsigned int nbMonopole = 0;
	unsigned int i = 0;

	//On parcourt les propriétés du joueur
	while(i < p->getNbPropriete())
	{
		if(p->getPropriete(i)->getGroup() == 42)
		{
			group[8]++;
		}
		else
		{
	 		group[p->getPropriete(i)->getGroup() - 1]++;
		}
	 	i++;
	}

	//Groupes composé de trois entreprises
	if(group[0] == 3){nbMonopole++;}	
	if(group[1] == 3){nbMonopole++;}	
	if(group[2] == 3){nbMonopole++;}	
	if(group[5] == 3){nbMonopole++;}	


	//Groupes composé de deux entreprises
	if(group[3] == 2){nbMonopole++;}	
	if(group[4] == 2){nbMonopole++;}	
	if(group[6] == 2){nbMonopole++;}	
	if(group[7] == 2){nbMonopole++;}	

	if(nbMonopole == 3 || group[8] == 4)
	{
		Vainqueur = joueurCourant;
	}
}

bool Jeu::dejaEnVente(unsigned int indice){
	bool enVente = false;
	unsigned int i = 0;
	while(!enVente && i < nbVente)
	{
		if(getPion(joueurCourant)->getPropriete(indice)->getNom() == vente[i])
		{
			enVente = true;
		}
		i++;
	}
	return enVente;
}



void Jeu::resetBool()
{
	konamiCode("");

	desLance = false;
	avance = false;
	confirmation = false;
	attendreNom = false;
	//////////////////
	attendreAmplete = true;
	actionObligatoire = true;
	vend = false;
	ad = false;
	porteO = false;
	apresPorteOuverte = false;
	/////////////////
}

void Jeu::tourSuivant(){
	unsigned int nbFaillite,vainqueur;
	nbFaillite = 0;
	victoireMonopole();
	for(unsigned int i=1; i<=4;i++){//on vérifie d'abbord si un joueur a gagné ici on vérifie juste si il y a un seul joueur survivant.
		if(getPion(i)->getCoin()<0){
			nbFaillite++;
		}
		else{
			vainqueur = i;
		}
	}
	if(nbFaillite==3){
		Vainqueur = vainqueur;
	}
	do{//on fait tour suivant tant que le joueur d'après est en faillite.
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
	}while(getPion(joueurCourant)->getCoin()<0);


	prixKarma();
}

void Jeu::actionPrison(const string touche){
	Pion * p = getPion(joueurCourant);
	if(!desLance&&(touche=="1"||touche=="\n")){
		desLance = true;
		p->lanceDes();
	}
	else if(touche=="2"&&p->getCoin()>prixAPayer&&!desLance){
		p->setCoin(p->getCoin()-prixAPayer);
		p->setPrisonnier();
	}
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
		else
		{
			actionPrison(touche);
		}
	}

	if(!p->getPrisonnier()){
		if(getPion(joueurCourant)->getTicket())
		{
			porteO = true;	
			porteOuverte(touche);
			desLance = true;
			avance = true;
			actionObligatoire = true;
			attendreAmplete = true;
			apresPorteOuverte = true;
		}
		else if(!desLance){
			if(touche == "\n"){
				p->lanceDes();
				desLance = true;
			}
		}
		else if(!avance){
			if(touche == "\n"){
				p->avancer();
				prixKarma();
				Case *c = board.getCase(p->getPos());
				if(c->getType() == 'I' || c->getType() == 'P')
				{
					prixKarma();
				}
				avance = true;
			}
		}
		else if(attendreAmplete||actionObligatoire){//tant que les action obligatoire et les amplète non pas été faite sur une case alors on attend
			actionCase(touche);
		}
		else{
			if(p->getDes().D1==p->getDes().D2 && !apresPorteOuverte){
				resetBool();//si le pion a fait un double on reset le tour a zero et il rejoue sans passer au tour suivant
			}
			else{
				if(tourOrdi){//si le tour n'a pas été reset alors on ne fini pas le tour
					tourSuivant();
				}
				
				else{
					if(touche=="\n"){// de même si le tour est pas reset on declenche un mini jeu et on termine le tour
						if(!e.Declenchement(p->getKarma())){
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
					confirmation=false;
					commencerPartie();//si c'est confirmé on commence la partie
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
						//invalidSave = false;
					}

					else{
						//invalidSave = true;//fichier corrompu
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
	if(touche == "+" && p->getCoin() >= c->getPrixB() && c->getInvestissement() < 5)
	{
		if(c->getInvestissement() < 3 || p->getTourUn())
		{
			p->investit(1,c);//si oui il investit
		}
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (touche == "-" && p->getCoin() >= c->getPrixM() && c->getInvestissement() > -5)
	{
		if(c->getInvestissement() > -3 || p->getTourUn())
		{
			p->investit(-1,c);//si oui il investit
		}
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
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();

//Vérifie si la case n'appartient pas au JOUEUR
	if(occupant != joueurCourant)
	{	
		if(occupant != 0 && actionObligatoire){// La case appartient a une autre personne
			if(touche == "\n"){
				payeLoyerJoueur(touche);
			}
		}

		//Cas de l'expropriation
		else if(occupant != joueurCourant && occupant != 0)
		{
			if((touche == "o" ||touche == "O") && c->getType() == 'E' && coinCourant >= c->getPrix())
			{
			    paye(joueurCourant,occupant,c->getPrix());
			    getPion(c->getOccupation())->estRacheter(c->getNom());
				getPion(joueurCourant)->don(c);	//le joueur a payer 
				victoireMonopole();
			}
			else
			{
				attendreAmplete = false;//si le joueur ne peut pas rachete pas alors il a fini.
			}
		} 
			
		else if(occupant == 0)//La case n'appartient a personne
		{
			actionObligatoire = false;//le joueur na pas de loyer a payer
			//N'appartient à personne,le JOUEUR peut acheter la banque ou l'entreprise
			//Est-ce que le JOUEUR veut acheter
			//Et est-ce qu'il a assez d'argent pour
			if((touche == "o" ||touche == "O") && coinCourant >= c->getPrix())
			{
				getPion(joueurCourant)->achete(c);
				victoireMonopole();

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
	else if (c->getType() == 'E' && attendreAmplete)
	{
		actionObligatoire = false;// le joueur n'a pas de loyer a payer
		investirEJoueur(touche);
	}
}

void Jeu::paye(unsigned int payeur, unsigned int creancier, float montant){
	assert((payeur <= 4 || payeur > 0) && (creancier <= 4 || creancier > 0));

	Pion *p = getPion(payeur);
	Pion *c = getPion(creancier);
	p->setCoin(p->getCoin() - montant);
	c->setCoin(c->getCoin() + montant);
}


void Jeu::payeLoyerJoueur(const string touche){
//C'est un joueur qui joue	
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	unsigned int coinCourant = getPion(joueurCourant)->getCoin();
	//Le joueurCourant paye directement si il a assez d'argent 
	if(coinCourant >= c->getLoyer() && !vend)
	{
		paye(joueurCourant,c->getOccupation(),c->getLoyer());
		actionObligatoire = false;//si le pion paye alors c'est bon il a fait ces actions obligatoires
	}

	//Le joueurCourant doit vendre pour payer le loyer
	else if((coinCourant + getPion(joueurCourant)->patrimoineActif()) >= c->getLoyer())
	{
		//on passe dans l'interface de vente (c'est-a-dire on passe le booléen vend a true)
		vend = true;
		prixAPayer = c->getLoyer();
	}

	//Le joueurCourant n'as pas assez d'argent pour s'acquitter du loyer
	//il est en faillite (fin du jeu pour lui)
	else 
	{
		paye(joueurCourant,c->getOccupation(),coinCourant + getPion(joueurCourant)->patrimoineActif());	
		getPion(joueurCourant)->EstEnFaillite();
		tourSuivant(); 
	}
}

void Jeu::pub(unsigned int quelleCase){
	//Case qui aura le championnat (la case choisit par le joueur)
	Case * championnat = board.getCase(quelleCase);
	if (championnat->getAd())
	{
		board.setcasePub(quelleCase);
		championnat->advertising();
	}
	else
	{
		if (board.getcasePub() > 0)
		{
			Case * exChampionnat = board.getCase(board.getcasePub());
			exChampionnat->endAdvertising();

			board.setcasePub(quelleCase);
			championnat->advertising();
		}
		else
		{
			board.setcasePub(quelleCase);
			championnat->advertising();
		}		
	}
	attendreAmplete = false; 
}

void Jeu::campagneDePub(const string touche){
	Case * c = board.getCase(board.getIndice("Campagne de pub"));
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();
	actionObligatoire = false;//La campagne de Pub n'est pas une action obligatoire
	if((touche == "o" ||touche == "O") 
		&& (coinCourant >= c->getPrix())
		&& (!ad)
		&& ((getPion(joueurCourant)->getNbPropriete()>0)))
	{
		ad = true;
	}

	else if(ad)
	{	
		//Première confirmation
		if((touche=="o"|| touche=="O") && !confirmation && choix != "")
		{
			confirmation = true;
				
			if(stoul(choix) > getPion(joueurCourant)->getNbPropriete()-1
				|| stoul(choix) < 0) //On vérifie si l'utilisateur n'a pas écrit n'importe quoi
			{
				confirmation = false;
			}
		}

		else if(!confirmation)
		{
			ecrire(touche);
		}
		if(confirmation)
		{
			
				pub(board.getIndice(getPion(joueurCourant)->getPropriete(stoul(choix))->getNom()));
				getPion(joueurCourant)->setCoin(coinCourant - c->getPrix());
				ad = false;
				confirmation = false;
				attendreAmplete = false;
				choix = "";
				confirmation=false;
			
		}
	}

	else if(touche=="n"||touche=="N" || touche == "\n")
	{
		attendreAmplete = false;
	}
	// puis après ouvrir un menu qui lui montre ses propriété pour qu'il choisisse où la mettre
	//ça doit donc ce dérouler en deux temps (utilise le booléen choix)
}

void Jeu::porteOuverte(const string & touche){
	Case * c = board.getCase(board.getIndice("Porte Ouverte"));//ATTENTION APPEL FRAUDULEUX
	actionObligatoire = false;

	if((touche == "o" ||touche == "O")
		&& (getPion(joueurCourant)->getCoin() >= c->getPrix())
		&& (board.nbCaseFree() > 0)
		&&!(getPion(joueurCourant)->getTicket()))
	{
		getPion(joueurCourant)->setTicket(true);
		attendreAmplete = false;
		tourSuivant();
	}

	else if(getPion(joueurCourant)->getTicket())
	{	
		//Première confirmation
		if((touche=="o"|| touche=="O") 
			&& !confirmation 
			&& choix != ""
			&& board.caseValide(stoul(choix),joueurCourant))
		{
			confirmation = true;
		}

		else if(!confirmation)
		{
			ecrire(touche);
		}
		if(confirmation)
		{
			//Deuxième confirmation
	
				getPion(joueurCourant)->setPos(stoul(choix));
				getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - c->getPrix());
				getPion(joueurCourant)->setTicket(false);	
				attendreAmplete = false;
				choix = "";
				porteO = false;
				confirmation=false;
				confirmation=false;
			
		}
	}

	else if(touche=="n" || touche=="N" || touche == "\n")
	{
		attendreAmplete = false;
	}
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
			if(gain != 0)
			{
				joueur->setCoin(joueur->getCoin() + gain);//le gain peut aussi être une perte.
				if(joueur->getCoin() < 0)
				{
					 if((joueur->getCoin() + getPion(joueurCourant)->patrimoineActif()) >= 0)
					{
						//on passe dans l'interface de vente (c'est-a-dire on passe le booléen vend a true)
						vend = true;
						prixAPayer = -gain;
					}

					//Le joueurCourant n'as pas assez d'argent pour s'acquitter du loyer
					//il est en faillite (fin du jeu pour lui)
					else 
					{
						getPion(joueurCourant)->EstEnFaillite();
						tourSuivant(); 
					}
				}
			}
			else if(id_Case == 0)
			{
				joueur->setPos(0);
				joueur->setTourUn(true);
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
			
			actionObligatoire = false; //si le joueur a pu payer il a fini ses action obligatoire	
			delete chance;//puis on delete la carte chance
			chance = NULL;//<-- très important
		}
	}
}

void Jeu::impot(const string touche){	

	if(getPion(joueurCourant)->getCoin() >= prixAPayer)
	{
		getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - prixAPayer);
		actionObligatoire = false;
	}

	else if((getPion(joueurCourant)->getCoin() + getPion(joueurCourant)->patrimoineActif()) >= prixAPayer)
	{
		//on passe dans l'interface de vente
		vend = true;
	}

	//Le joueurCourant n'as pas assez d'argent pour s'acquitter des impôt
	//il est en faillite (fin du jeu pour lui)
	else 
	{
		getPion(joueurCourant)->EstEnFaillite();
		tourSuivant(); 
	}
	prixAPayer = 0;
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
			campagneDePub(touche);
			break;

		case 'O':
			porteOuverte(touche);
			break;

		case 'I':
			attendreAmplete= false;
			impot(touche);
			break;
		default :
			attendreAmplete = false;
			actionObligatoire = false;
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
				getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin()+e.getgain());
				e.reset();
				h.resetHack();
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
			c.ajoutClique();
		}
		if((c.getFin()==true)&&(touche == "\n")){
			
			getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin()+e.getgain());
			e.reset();
			c.resetClicker();
			tourSuivant();
		}
	}
	if(e.getn() == "escape"){

		
		if((es.getFin()==true)&&(touche=="\n")){
			if(es.getEchec()==true){
				getPion(joueurCourant)->setPos(8);
				getPion(joueurCourant)->setPrisonnier();
			}
			e.reset();
			es.resetEscape();
			tourSuivant();
		}
		else{
			es.avancerJoueur(touche);
		}
		
	}
}

void Jeu::actionVictoire(){
	assert(Vainqueur<=4&&Vainqueur>0);
	reset();
}

void Jeu::actionClavier(const string & touche)
{
	if(nbTour == 0){
		actionMenu(touche);
	}
	else if(Vainqueur!=0){
		actionVictoire();
	}
	else if(pause){
		actionPause(touche);
	}
	else if(vend)
	{
		modeVente(touche);
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

void Jeu::action(const string & action){
	if(action.length()==1){
		actionClavier(action);

	}
	else{
		//ici rajouté des actions personalisée
		if(action[0]=='-'){
			enleverJoueur(action[1]);
			confirmation=false;
		}
		if(action[0]=='c'){
			if(action.length()==3){
				string act="  ";
				act[0]=action[1];
				act[1]=action[2];
				choix=act;
			}
			else{
				string act=" ";
				act[0]=action[1];
				choix=act;
			}
		}
	}
}

void Jeu::actionPause(const string & touche){
	if(!attendreNom){
		if(touche=="\e"||touche=="1"){
			pause=false;
		}
		else if(touche=="2"){
			attendreNom = true;
			//choix d'un fichier de sauvegarde
		}
		else if(touche=="3"){
			reset();
		}
		else if(touche=="4"){
			quitte= true;
		}
	}
	else{//le joueur a précédement choisi de sauvegarder la partie
		if(touche =="1"||touche == "2"||touche =="3"){
			sauver("data/sauvegarde/"+touche+".save");
		}
		if(touche=="\e"){
			attendreNom = false;//passe dans le menu précédent
		}
	}
}

void Jeu::actionOrdi(){
	Ordi * o = getOrdi(joueurCourant);
	assert(joueurCourant==o->getRang());
	if(vend){//quand l'ordi doit vendre
		if(getPion(joueurCourant)->getCoin() + totalVente() >= prixAPayer){//si l'ordi a assez vendu.
			actionClavier("o");
		}
		else{
			//vente[nbvente] = faire une fonction qui donne un choix.;
			nbVente++;
		}
	}
	else{
		if(!avance){//tant que l'ordi n'a pas avancé
			actionClavier("\n");
		}
		else{
			Case * c = board.getCase(o->getPos());
			switch(c->getType()){
				case 'E':
					if(c->getOccupation()==0){//si elle est a personne
						if(o->AIacheteEntreprise(c)){
							actionClavier("o");
						}
						else{
							actionClavier("n");
						}
					}
					else if(c->getOccupation()==joueurCourant){//si elle est a l'ordi
						int inv = o->AIinvesti(c);
						if(inv==0){//si l'ordi ne veut pas investir il confirme.
							actionClavier("\n");
						}
						else if(inv < 0){
							actionClavier("-");
						}
						else if(inv > 0){
							actionClavier("+");
						}
					}
					else{//la case appartient a quelqu'un d'autre
						if(actionObligatoire){//si doit payer le loyer
							actionClavier("\n");
						}
						else{
							if(o->AIacheteEntreprise(c)){
								actionClavier("o");
							}
							else{
								actionClavier("n");
							}
						}
					}
					break;

				case 'B':
					if(c->getOccupation()==0){//si elle est a personne
						if(o->AIacheteEntreprise(c)){
							actionClavier("o");
						}
						else{
							actionClavier("n");
						}
					}
					else if(c->getOccupation()==joueurCourant){//si elle est a l'ordi
						actionClavier("\n");//rien a faire sur une banque
					}
					else{//la case appartient a quelqu'un d'autre
						actionClavier("\n");
					}
					break;

				case 'C':
					actionClavier("\n");
					break;

				case 'A':
					actionClavier("n");//pour l'instant les ordis n'organisent pas de campagne de pub
					break;

				case 'O':
					actionClavier("n");//pour l'instant les ordis ne font pas de porte ouverte
					break;

				case 'I':
					actionClavier("\n");
					break;
			}
		}
	}
}



//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement(getPion(joueurCourant)->getKarma());
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

Escape Jeu::getes(){
	return es;
}

//seteur permettant de mettre à jour clicker c
void Jeu::setc(){

	c.resetClicker();

}


bool Jeu::accepteClavier() const{
	return true;//ajouter les condition pour lesquels on veut que l'utilisateur puisse utiliser le clavier (par exemple pendant le clicker on ne veut pas utiliser le clavier en SDL)
}


void Jeu::updateMiniJeu(){

	if(e.getn() == "escape"){

		es.deplacePolice(gete().gettempsD());
		es.victoireDefaite();
	}
	if(e.getn() == "clicker"){
		c.gestionTps(gete().gettempsD());
		if(c.getFin()==true){e.fini();}
	}
	
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
