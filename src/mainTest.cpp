#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include "core/Jeu.h"


using namespace std;

void ecrire(const string & file){
	ofstream fichier (file.c_str());
	assert(fichier.is_open());

	fichier<<0<<" salut"<<" "<<endl<<"zizitos"<<" "<<endl<<" \"test espace\" "<<5<<4<<endl<<0;
	fichier.close();
}

void lire(const string & file){
	ifstream fichier (file.c_str());
	assert(fichier.is_open());
	string a;
	for(int i = 0;i<=4;i++){
		fichier>>a;
		cout<<a<<endl;
	}
	fichier.close();
}

int main(int argc,char ** argv)
{
	Jeu j,g,h;
	unsigned int tab[4];
	j.getOrdre(tab);
	for(int i = 0;i<4;i++){ 
		cout<<tab[i]<<" ";
	}
	cout<<endl;

	cout<<"test\ntest"<<endl;

	cout<<"---------test fichier---------"<<endl<<endl;
	ecrire("data/sauvegarde/titatitutu");
	lire("data/sauvegarde/titatitutu");

	return 0;
}