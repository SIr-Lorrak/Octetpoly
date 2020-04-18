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
	tourFini = false;
	/////////////
	vend = false;
	ad = false;
	porteO = false;
	choix = "";
	nbVente = 0;
	for (int i = 0; i < 24; ++i)
	{
		vente[i] = "";
	}
	/////////////
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
	joueurCourant = ordre[3];
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

string Jeu::getChoix() const
{
	return choix;
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

void Jeu::sauver(const string & file) const
{
	ofstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	
	fichier.close();
}


void Jeu::charger(const string & file)
{
	ifstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	
	fichier.close();
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

 void Jeu::remiseZeroEtVente(){
	for (unsigned int i = 0; i < nbVente; ++i)
	{
		getPion(joueurCourant)->vend(vente[i]);
		vente[i] = "";
	}
	nbVente = 0;
}

void Jeu::affichageQuartierDisponible(){
	for (int i = 0; i < 32; ++i)
	{
		if((board.getCase(i)->getType()=='E'||board.getCase(i)->getType()=='B')
			&&board.getCase(i)->getOccupation()==0)
		{
			cout << i << " " << board.getCase(i)->getNom() << endl; 
		}	
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
	attendreAmplete = true;
	tourFini = false;
	actionObligatoire = true;
	//////////////////
	vend = false;
	ad = false;
	porteO = false;
	/////////////////
}

void Jeu::tourSuivant(){
	nbTour++;
	unsigned int i=0;
	while(joueurCourant!=ordre[i]){
		cout<<"lol";
		i++;
	}

	joueurCourant = ordre[(i+1)%4];

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
				tourFini = true;
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
		if(getPion(joueurCourant)->getTicket())
		{
			porteO = true;	
			porteOuverte(touche);
			desLance = true;
			avance = true;
			actionObligatoire = true;
			attendreAmplete = true;
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
				avance = true;
			}
		}
		else if(attendreAmplete||actionObligatoire){//tant que les action obligatoire et les amplète non pas été faite sur une case alors on attend
			actionCase(touche);
		}
		else if(!tourFini){
			if(p->getDes().D1==p->getDes().D2){
				resetBool();//si le pion a fait un double on reset le tour a zero et il rejoue sans passer au tour suivant
			}
			else{
				if(tourOrdi){//si le tour n'a pas été reset alors on ne fini pas le tour
					tourFini = true;
				}
				
				else{
					if(touche=="\n"){// de même si le tour est pas reset on declenche un mini jeu et on termine le tour
						if(!e.Declenchement()){
							tourFini = true;
						}
					}
				}
			}
		}
	}
	if(tourFini){
		tourSuivant();
	}
}


void Jeu::actionMenu(const string & touche)
	{
	if(!attendreNom&&nbJoueur<4){
		if(!confirmation){//si on attend une confirmation pour commencer on n'attend plus d'ajout de joueur
			if(touche == "+"){
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
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();

//Vérifie si la case n'appartient pas au JOUEUR
	if(occupant != joueurCourant)
	{	
		if(occupant != 0 && actionObligatoire){// La case appartient a une autre personne
			if(vend || touche == "\n"){
				payeLoyerJoueur(touche);
			}
		}

		else//La case n'appartient a personne
		{
			actionObligatoire = false;//le joueur na pas de loyer a payer
			//N'appartient à personne,le JOUEUR peut acheter la banque ou l'entreprise
			//Est-ce que le JOUEUR veut acheter
			//Et est-ce qu'il a assez d'argent pour
			if((touche == "o" ||touche == "O") && coinCourant >= c->getPrix())
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

			else if((touche=="o"|| touche=="O") 
				&& coinCourant + totalVente() >= c->getLoyer())
			{
				confirmation = true;
			}

			else
			{
				ecrire(touche);
			}
		}

		else 
		{
			//Deuxième confirmation
			if(touche=="o"|| touche=="O")
			{	
				remiseZeroEtVente();
				vend = false;
			}
			else if(touche=="n"||touche=="N")
			{
				confirmation=false;//si ça n'est pas confirmer on ne commence pas la partie et on reprend la selection des joueurs
			}
		}
	}

	//Le joueurCourant n'as pas assez d'argent pour s'acquitter du loyer
	//il est en faillite (fin du jeu pour lui)
	else 
	{
		paye(joueurCourant,c->getOccupation(),coinCourant);	
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
	Case * c = board.getCase(16);//ATTENTION APPEL FRAUDULEUX
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
		else if(confirmation)
		{
			//Deuxième confirmation
			if(touche=="o"|| touche=="O")
			{
				pub(board.getIndice(getPion(joueurCourant)->getPropriete(stoul(choix))->getNom()));
				getPion(joueurCourant)->setCoin(coinCourant - c->getPrix());
				ad = false;
				attendreAmplete = false;
				choix = "";
			}
			else if(touche=="n"||touche=="N")
			{
				confirmation=false;//si ça n'est pas confirmer on ne commence pas la partie et on reprend la selection des joueurs
			}
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
	Case * c = board.getCase(24);//ATTENTION APPEL FRAUDULEUX
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
		else if(confirmation)
		{
			//Deuxième confirmation
			if(touche=="o"|| touche=="O")
			{
				getPion(joueurCourant)->setPos(stoul(choix));
				getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - c->getPrix());
				getPion(joueurCourant)->setTicket(false);	
				attendreAmplete = false;
				choix = "";
				porteO = false;
			}
			else if(touche=="n"||touche=="N")
			{
				confirmation=false;//si ça n'est pas confirmer on ne commence pas la partie et on reprend la selection des joueurs
			}
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
			campagneDePub(touche);
			break;

		case 'O':
			porteOuverte(touche);
			break;

		case 'I':
			attendreAmplete= false;
			actionObligatoire = false;
			//TODO 
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
				//TODO : faire les gains / pertes avant de passer au tour suivant.
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

void Jeu::actionClavier(const string & touche)
{
	if(nbTour == 0){
		actionMenu(touche);
	}

	else if(e.getn()=="rien"){
		konamiCode(touche);//pour le konami code
		actionPartie(touche);
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


Jeu::~Jeu(){
	if(tabO!=NULL){
		delete [] tabO;
	}
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}
