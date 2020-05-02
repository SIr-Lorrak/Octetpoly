#include "Jeu.h"

using namespace std;

void Jeu::konamiCode(const string touche)
{
	//TODO
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

		if((touche=="o"|| touche=="O"||touche=="\n") 
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
		remiseZeroEtVente();
		prixAPayer = 0;
		confirmation = false;
		vend = false;	
	}
}

void Jeu::actionPrison(const string touche){
	Pion * p = getPion(joueurCourant);
	if(!desLance&&(touche=="1"||touche=="\n")){
		desLance = true;
		p->lanceDes();
	}
	else if(touche=="2"&&p->getCoin()>(int)prixAPayer&&!desLance){
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
				Case *c = board.getCase(p->getPos());
				if(c->getType() == 'I' || c->getType() == 'P')
				{
					prixKarma();
				}
				if(c->getType() == 'D'){//si c'est la case départ il n'y a rien a faire donc on passe imédiatement à la fin du tour.
					attendreAmplete=false;
					actionObligatoire=false;
				}
				if((c->getType() == 'E'||c->getType()=='B')&&c->getOccupation()==0){
                    actionObligatoire=false;
                    if(getPion(joueurCourant)->getCoin()<(int)c->getPrix()){
                        attendreAmplete=false;
                    }
                }
				avance = true;
			}
		}
		else if(attendreAmplete||actionObligatoire){//tant que les action obligatoire et les amplète non pas été faite sur une case alors on attend
			actionCase(touche);
		}
		else{
			if(p->getDes().D1==p->getDes().D2 && !apresPorteOuverte&&p->getCoin()>=0){
				resetBool();//si le pion a fait un double on reset le tour a zero et il rejoue sans passer au tour suivant
			}
			else{
				if(tourOrdi){//si le tour n'a pas été reset alors on ne fini pas le tour
					tourSuivant();
				}
				
				else{
					if(touche=="\n"&&p->getCoin()>=0){// de même si le tour est pas reset on declenche un mini jeu et on termine le tour
						if(!e.Declenchement(p->getKarma())){
							tourSuivant();
						}
					}
					else{
						tourSuivant();
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
			if(attendreNom){
				enleverJoueur();
				attendreNom=false;
			}
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
						attendreNom=false;
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
	if(touche == "+" && p->getCoin() >= (int)c->getPrixB() && c->getInvestissement() < 5)
	{
		if(c->getInvestissement() < 3 || p->getTourUn())
		{
			p->investit(1,c);//si oui il investit
		}
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (touche == "-" && p->getCoin() >= (int)c->getPrixM() && c->getInvestissement() > -5)
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
				if(getPion(joueurCourant)->getCoin()<(int)c->getPrix()){
					attendreAmplete = false;
				}
			}
			if(c->getType()=='B'){//si c'est une banque acheté alors le joueur ne peut plus faire d'amplètes (pas d'investissement sur les banques)
				attendreAmplete = false;
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
	else if(c->getType()=='B'){
		attendreAmplete=false;
		actionObligatoire=false;
	}
	//La case appartient au JOUEUR	
	//Si c'est une entreprise, il pourra peut-être investir
	else if (c->getType() == 'E' && attendreAmplete)
	{
		actionObligatoire = false;// le joueur n'a pas de loyer a payer
		investirEJoueur(touche);
	}
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
		actionObligatoire=false;
		attendreAmplete=false; 
	}
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
		getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - c->getPrix());
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
		&& (getPion(joueurCourant)->getCoin() >= (int)c->getPrix())
		&& (board.nbCaseFree() > 0)
		&&!(getPion(joueurCourant)->getTicket()))
	{
		getPion(joueurCourant)->setTicket(true);
		getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - c->getPrix());
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
			getPion(joueurCourant)->setPos(stoul(choix));
			getPion(joueurCourant)->setCoin(getPion(joueurCourant)->getCoin() - c->getPrix());
			getPion(joueurCourant)->setTicket(false);	
			attendreAmplete = false;
			choix = "";
			porteO = false;
			confirmation=false;
		}
	}

	else if(touche=="n" || touche=="N" || touche == "\n")
	{
		attendreAmplete = false;
	}
}

void Jeu::actionChance(const string & touche){
	attendreAmplete = false; //le joueur ne fera pas d'amplete sur une carte chance.
	if(chance == NULL){//si une la carte n'a pas encore été tirée.{
		if(touche == "\n")//le joueur pioche une carte avec entrer 
		{
			chance = new Carte;
			chance->randomCarte();
		}
	}
	else{//si la carte est déjà tirée
		if(touche=="\n"){//le joueur appuie a nouveau sur entrer après qu'il est lu ça carte
		carteChance();
		delete chance;
		chance = NULL;
		}
	}
}

void Jeu::impot(const string touche){	

	if(getPion(joueurCourant)->getCoin() >= (int)prixAPayer)
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
		actionObligatoire=false;
		attendreAmplete=false;
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
			actionChance(touche);
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
	if(e.getn() == "lucky"){

		if(!lu.getCartePiocher()){//si les cartes n'ont pas encore été tirées.

			if(touche == "\n")//le joueur pioche deux cartes avec entrer 
			{
				lu.pioche();
			}
		}

		else{//si la carte est déjà tirée

			//1 pour saisir la première carte
			if(touche == "1")
			{
				chance = lu.getCarteUn();
				carteChance();
				e.reset();
				lu.reset();
				chance = NULL;
			}

			//2 pour saisir la seconde carte
			if(touche == "2")
			{
				chance = lu.getCarteDeux();	
				carteChance();
				e.reset();
				lu.reset();
				chance = NULL;
			}

			//3 pour ne choisir aucune des deux cartes
			if(touche == "3")
			{
				e.reset();
				lu.reset();
				chance = NULL;
				tourSuivant();
			}

		}
	}
}

//actionVictoire ne prend pas de touche car il se fait peu importe la touche appuyée
//mais il correspond bien a un appuie de touche.
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

		else if(action[0]=='c'&&action[1]=='a'&&action[2]=='r'){
			getPion(action[3])->setCar(action[4]);
		}
		else if(action[0]=='c'){
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