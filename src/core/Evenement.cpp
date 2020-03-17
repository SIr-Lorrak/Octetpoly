#include "Evenement.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <time.h>
#include <stdlib.h>
using namespace std;



Hacking::Hacking(){
	srand (time(NULL));
	int alea = rand()%2;
	mot = tab_com[alea];
	nbSaisie = 0;
}


void Hacking::saisir(char N){

		motSaisie = motSaisie + N;
}


bool Hacking::valider(){
	if(motSaisie==mot){
		motSuivant();
		return true;
	}
	else
		return false;
}


void Hacking::motSuivant(){
	srand (time(NULL));
	int alea = rand()%2;
	mot = tab_com[alea];
	nbSaisie++;
}


string Hacking::getMot(){
		return mot;
}


string Hacking::getMotSaisie(){
	return motSaisie;
}

unsigned int Hacking::getnbSaisie(){
	return nbSaisie;
}


/*void hacking::hack(){
	string a;
	clock_t tempsD, tempsF;
	tempsD = clock();
	cout<<"hacking, remplit les commande dans le temps impartie"<<endl;
	for(int i = 0;i<3;i++) {

		cout<<tab_com[i]<<endl;
		
		while(entrer_term()!=tab_com[i]){

			cout<<"erreur"<<endl<<tab_com[i]<<endl;

			

		}
		if(i!=2){
			cout<<"commande bonne, suivante:"<<endl;

		}
		
	}
	tempsF = clock();
	tps = (tempsF-tempsD)/60.0;

}

string hacking::entrer_term(){
	string commande;
	getline(cin,commande);
	return commande;
}


string hacking::entrer(){
	string commande;
	string touche;
	touche = fgetc(stdin);
	 
	while(touche!="enter"){
		commande = commande+touche;
		touche = fgetc(stdin);
		

	}
	cout<<commande<<3<<endl;
	return commande;

}

void hacking::gettps(){
	cout<<tps<<endl;
}




void clicker::pub(){
	nbclique = 0;
	string touche = "a";
	for(auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(2);std::chrono::system_clock::now() < runUntil;)
	{
		touche = fgetc(stdin);
		cout<<touche<<2<<touche<<2<<touche<<2;
		if(touche==" "){
			cout<<touche<<1<<touche<<1<<touche<<1;
			nbclique++;
			touche = "a";
		}
	}
	cout<<"fin"<<endl;

}*/