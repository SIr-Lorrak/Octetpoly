#include "Evenement.h"
#include <iostream>
#include <time.h>
using namespace std;


bool hacking::hack(){
	string a;
	clock_t tempsD, tempsF;
	tempsD = clock();
	cout<<"hacking, remplit les commande dans le temps impartie"<<endl;
	for(int i = 0;i<3;i++) {

		cout<<tab_com[i]<<endl;
		getline(cin,a);

		while(a!=tab_com[i]){

			cout<<"erreur"<<endl<<tab_com[i]<<endl;
			getline(cin,a);

		}
		if(i!=2){
			cout<<"commande bonne, suivante:"<<endl;

		}
		
	}
	tempsF = clock();
	cout<<tempsD<<"   "<<tempsF<<endl;
	float tps = (tempsF-tempsD)/60.0;
	if (tps<8){
		cout<< "vous avez reussi en "<<tps<<" seconds"<<endl;
		return 0; 
	}
	else {
		cout<<"vous avez perdu, vous avez mis "<<tps<<" second"<<endl;
		return 1;
	}




}

