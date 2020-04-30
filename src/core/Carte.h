#ifndef OCTET_CARTE_H
#define OCTET_CARTE_H

#include <iostream>
#include <string>

using namespace std;


/**
@brief classe qui définie les cartes chances
*/
class Carte {

	private:

		int gain; // somme gagner ou perdu indiqué sur la carte
		int id_case; // id de la case où le jouer doit se rendre indiqué sur la carte
		int id_carte; // id de la carte pioché
		bool casePlus3; // indique si le joueur doit reculer de 3 cases
		const string tab_carte[2][25] = {
													//-TITRE
										 {"Allez récupérer votre paye !",
										  "Vous êtes vieux ?",
										  "Violence gratuite !",
										  "Rendez-vous jusqu’à l’entreprise Sanofi",
								/*5*/	  "Vous êtes libéré de prison",
										  "L'alcule cé du jus ! Hic", 
										  "Les intérêts, y’a intérêt !", 
										  "Vos amis seront ravis !",
										  "Made in China", 
								/*10*/	  "Jour de paye !", 
										  "C’est leur de manger !", 
										  "Police Nationale, que faites-vous !",
										  "Soyez présentable !", 
										  "Money money money !", 
								/*15*/	  "Votre banquier vous appelle !", 
										  "Coup de chance ou intérêt commun ?",
										  "Vous êtes le meilleur tradeur", 
										  "Vous avez trop joué avec le feu !", 
										  "Oh mince, mamie vient de mourir…",
								/*20*/	  "Vous voulez investir dans l’or noir !", 
										  "Quitte ou double ?", 
										  "Contribuer pour la société ça paye !",
										  "Meeting entre grosses entreprises !", 
										  "Vous êtes diabolique !", 
								/*25*/	  "C’est l’heure de se faire plaisir !" },


										  			//-DESCRIPTION
										  {"Avancez jusqu’à la case départ.",
										   "Payer vos cotisations de retraite s’élevant à 500$.",
										   "Reculez de trois cases.",
										   "Une bonne santé est importe de nos jour. Si vous passez par la case départ recevez 500$",
								/*5*/	   "Je pense qu'il est impossible d'être chef d'entreprise sans un minimum d'audace, cette carte peut être conservée jusqu’à ce qu'elle soit utilisée.",
										   "Amande pour ivresse, 100$.",
										   "Recevez vos intérêts sur l’emprunt à 7 %, 250$.",
										   "C’est l’anniversaire de votre société, recevez 100$ de la part de chaque joueur.",
										   "Vos investissements à l'étranger vous rapportent 200$.", 
								/*10*/	   "Vous recevez votre revenu annuel de 500$.",
										   "Payez les frais de repas de vos salariés, 150$.",
										   "Arrêtez-vous sur le bas-côté de la route et payez une amande pour excès de vitesse, 100$.",
										   "Vous vous faites refaire le visage, cela vous coute 400$.", 
										   "La banque vous verse un dividende de 350$.",
								/*15*/	   "Rendez-vous à la banque BNB Paribas. Si vous passez par la case départ recevez 500$.",
										   "Erreur de la banque ! Recevez 150$.", 
										   "La vente de vos actions vous rapporte 200$.",
										   "Allez en prison.", 
										   "Vous héritez de 400$.",
								/*20*/	   "Avancez jusqu’à l’entreprise Shell. Si vous passez par la case départ recevez 500$.",
										   "Payez une amande de XXX$ ou piochez une nouvelle carte.", 
										   "L’Etat vous verse 150$ de subventions.",
										   "Rendez-vous chez Google. Si vous passez par la case départ recevez 500$.",
										   "Sabotez les installations électriques de l’entreprise d’une société concurrente.",
								/*25*/	   "Vous volez l’entreprise de l’un de vos concurrents."}};

	public:

		/**
		@brief retourne le gain0
		@param none
		*/
		int getgain() const;

		/**
		@brief retourne l'id de la case
		@param none
		*/
		int getid_case() const;

		/**
		@brief retourne l'id de la carte
		@param none
		*/
		int getid_carte() const;

		/**
		@brief retourne le titre de la case
		@param none
		*/
		string getTitre() const;

		/**
		@brief retourne le Texte de la case
		@param none
		*/
		string getTexte() const;

		/** 
		@brief retourne un bool
		@param none
		*/
		bool getcasePlus3() const;

		/**
		@brief pioche une carte au hasard
		@param none
		*/
		void randomCarte();


};



#endif