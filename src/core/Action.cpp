#include "Jeu.h"
#include <string>

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
	attendreNom = false;
	if(nbJoueur<4){
		delete [] tabO;
		tabO = new Ordi [4-nbJoueur];
	
		for(unsigned int i = 0;i<4-nbJoueur;i++){
			do{
				tabO[i].nomAleatoire();
			}while(nomExiste(tabO[i].getNom(),tabO,i));//tant que deux Ordi on le même nom on relance la tirage au sort des nom
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
	tabJ[nbJoueur]->setCar(rand()%16);
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

void Jeu::paye(unsigned int payeur, unsigned int creancier, float montant){
	assert((payeur <= 4 || payeur > 0) && (creancier <= 4 || creancier > 0));

	Pion *p = getPion(payeur);
	Pion *c = getPion(creancier);
	p->setCoin(p->getCoin() - montant);
	c->setCoin(c->getCoin() + montant);
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

void Jeu::carteChance(){
	Pion * joueur = getPion(joueurCourant); 
		int id_Case;
		int gain;
		bool casePlus3;

		id_Case = chance->getid_case();
		gain = chance->getgain();
		casePlus3 = chance->getcasePlus3();
		
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
						attendreAmplete=false;
						actionObligatoire=false;
					}
				}
			}
			else if(id_Case == 0)
			{
				joueur->setPos(0);
				joueur->setTourUn(true);
				joueur->salaire();
			}
			else if(id_Case > 0)
			{
				if((int)joueur->getPos() > id_Case)
				{
					joueur->salaire();
					joueur->setTourUn(true);
				}
				actionObligatoire = true;
				attendreAmplete = true;
				joueur->setPos(id_Case);
			}
			else if(casePlus3)
			{
				joueur->setPos(joueur->getPos() + 3);
				if(joueur->getPos() > 31)
				{
					joueur->setPos(joueur->getPos() - 32);
				}
				if(board.getCase(getPion(joueurCourant)->getPos())->getType() == 'E'	
					|| board.getCase(getPion(joueurCourant)->getPos())->getType() == 'B')
				{
					actionObligatoire = true;
					attendreAmplete = true;
				}
			}
			actionObligatoire = false; //si le joueur a pu payer il a fini ses action obligatoire	
			//delete chance;//puis on delete la carte chance
			//chance = NULL;//<-- très important
}

void Jeu::actionOrdi(){
	Ordi * o = getOrdi(joueurCourant);
	assert(joueurCourant==o->getRang());
	if(vend){//quand l'ordi doit vendre
		if(getPion(joueurCourant)->getCoin() + totalVente() >= prixAPayer){//si l'ordi a assez vendu.
			remiseZeroEtVente();
			prixAPayer = 0;
			vend = false;
		}
		else{
			vente[nbVente] = o->AIvend(vente,nbVente);
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

				case 'A':
					if(attendreAmplete){
						actionClavier("n");//pour l'instant les ordis n'organisent pas de campagne de pub
					}
					else{
						actionClavier("\n");
					}
					break;

				case 'O':
					if(attendreAmplete){
						actionClavier("n");//pour l'instant les ordis ne font pas de porte ouverte
					}
					else{
						actionClavier("\n");
					}
					break;

				default:
					actionClavier("\n");
					break;
			}
		}
	}
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
		if(c.getFin()==true){e.fini(c.getnbclique());}
	}
}
