#ifndef OCTET_CASE_H
#define OCTET_CASE_H

#include <string>
#include <assert.h>

using namespace std;

/**
@brief les case du plateau (case départ, entreprise, banque, etc.)
*/
class Case{
private:

	bool ad; //Indique si la case est en publicité
	float coeffAd; //Indique coefficient Ad

	string nom;//Le nom de la case
	unsigned int occupation;//Qui occupe la case
	char type; //Type une entreprise, une banque, un case chance,...
	int investissement; //Permet de savoir l'entreprise a investi dans le légal ou illégal
	unsigned int groupe; //Groupe au quelle appartient la case
	unsigned int karmaCase; //Le karma que rapporte ou retire la case au joueur

	unsigned int loyer; //Prix à payer lorque la case appartient à un autre joueur
	unsigned int loyerInitial;

	unsigned int prix; //Prix d'achat
	unsigned int prixInitial;

	unsigned int prixM; //Prix pour un investissement illégale
	unsigned int prixMInitial;

	unsigned int prixB; //Prix pour un investissement légal
	unsigned int prixBInitial;

	unsigned int prixDeVente; //Prix de revente
	unsigned int prixDeVenteInitial;

	//Les Coefficients de multiplicités qui change selon les niveau
	//investissement sur la case 
	float coeffUn; 
	float coeffDeux;
	float coeffTrois;
	float coeffQuatre;
	float coeffCinq;

	
public:
	//---------------------------------Constructeurs--------------------------------------
	/**
	@brief Crée une case (constructeur par défaut)
	@param none
	*/
	Case();

	/**
	@brief Destructeur de la classe
	@param none
	*/
	~Case();

	/**
	@brief Set les différents attributs Variable de Case
	@param respectivement : son prix, son loyer, son prixdevente, son prix de l'investissement illégal, son prix de l'investissement légal, son niveau d'investissement
	*/
	void set(unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i);


	//----------------------------------Getters------------------------------------------
	/**
	@brief Renvoie le Nom de la Case
	@param none
	@return nom : string
	*/
	string getNom() const;

	/**
	@brief Indique à qui appartient l'entreprise ou la banque
	@param none
	@return occupation : unsigned int | 0 : Innocupé ; 1 : Joueur1 ; 2 : Joueur2 ; etc...
	*/ 
	unsigned int getOccupation() const;

	/**
	@brief Renvoie le Prix de base (celui qui ne varie pas) d'une Case
	@param none
	@return prixDeBase : unsigned int
	*/
	unsigned int getPrixDeBase() const;

	/**
	@brief Renvoie le Loyer d'une Case (ce que les joueurs doivent payer en tombant dussus)
	@param none
	@return loyer : unsigned int
	*/
	unsigned int getLoyer() const;

	/**
	@brief Indique le prix de l'entreprise ou de la banque
	@param none
	@return prix : unsigned int
	*/ 
	unsigned int getPrix() const;

	/**
	@brief Indique le prix d'un investissement illégal (mauvais)
	@param none
	@return prixM : unsigned int
	*/ 
	unsigned int getPrixM() const;

	/**
	@brief Indique le prix d'un investissement légal (bon)
	@param none
	@return prixB : unsigned int
	*/ 
	unsigned int getPrixB() const;

	/**
	@brief Informe sur le prix initial de l'entreprise ou banque
	@param none
	@return prixInitial : unsigned int 
	*/
	unsigned int getPrixInitial() const;

	/**
	@brief Informe sur le prix de vente de l'entreprise ou de la banque
	@param none
	@return prixDeVente : unsigned int 
	*/
	unsigned int getPrixDeVente() const;

	/** 
	@brief Indique l'investissement de l'entreprise
	@param none
	@return investissement : int | <0 si investissement illégal,
	>0 si investissement dans le légal, =0 si aucun investissement
	*/ 
	int getInvestissement() const;

	/**
	@brief Récupére le type de la case
	@param none
	@return type : char | 'D' : Départ ; 'E' : Entreprise ; 'B' : Banque ; 'P' : Prison ;
	'C' : Chance ; 'I' : Impôt ; 'O' : Porte Ouverte ; 'A' : Publicité (Advertising)
	*/ 
	char getType() const;

	/**
	@brief Indique si la Case est en campagne de Pub ou pas
	@param none
	@return ad : bool
	*/
	bool getAd() const;

	/**
	@brief Renvoie le numero du groupe de la Case
	@param none
	@return groupe | 0 : groupe case normal ; 1 à 8 : groupe d'entreprise ;
	42 : groupe banque
	*/
	unsigned int getGroup() const;

	/**
	@brief Renvoie le Karma d'une Case (taux d'impact sur le karma des Pions)
	@param none
	@return karmaCase : unsigned int
	*/
	unsigned int getKarmaCase() const;
	//----------------------------------Setters------------------------------------------

	/**
	@brief Set le propriétaire d'une Case (/!\ uniquement lors du chargement d'une sauvegarde normalement)
	@param le rang du nouveau propriétaire, r
	@return none
	*/
	void setOccupation(unsigned int r);
	//---------------------------------Methodes------------------------------------------
	/**
	@brief Permet l'initialisation d'une case au lancement d'une partie 
	(prix de base,type,nom de la case,etc)
	@param prend en paramètre le groupe au quelle la case appartient, la catégorie de la case, 
	le prix, son nom,son influence sur le karma, le prix de vente, le prix mauvais investissement, 
	le prix bon investissement,le loyer et les cinq coefficient
	@return none
	*/ 
	void initCase(unsigned int group,char categorie,unsigned int p,
				  	string n,unsigned int karma,unsigned int pV,
			   		unsigned int pM,unsigned int pB,unsigned int l,
					float c1,float c2,float c3,float c4,float c5);

	/**
	@brief Initialise les prix initiaux d'une entreprise ou d'une banque
	@param none
	@return none
	*/ 
	void initPrixInitial();

	/**
	@brief Change l'investissement, le prix,le loyer,le prix de vente,le prixB et le prixM
	@param i : int
	@return none
	*/ 
	void investir(int i);

	/**
	@brief Affecte un propriètaire et change les prix
	@param i : unsigned int
	@return none
	*/ 
	void estAcheter(unsigned int i);

	/**
	@brief Indique que l'entreprise fait de la pub (Change les prix)
	@param i : unsigned int
	@return none
	*/ 
	void advertising();


	/**
	@brief Indique que l'entreprise ne fait plus de pub (Change les prix)
	@param i : unsigned int
	@return none
	*/ 
	void endAdvertising();

	/**
	@brief Réinitialisation de la case
	@param none
	@return none
	*/ 
	void reset();

//-------------------------------------TEST REGRESSION-----------------------------------

	/**
	@brief Permet d'afficher toutes les données membre de la classe
	@param none
	*/
	void affichageRegression();

	/**
	@brief Teste toutes les fonctions de la classe
	@param none
	*/
	void testRegressionCase();
};

#endif